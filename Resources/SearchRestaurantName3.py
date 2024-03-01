import pyodbc
import sys
import datetime
from datetime import date

#conn = pyodbc.connect('DRIVER=ODBC Driver 17 for SQL Server; SERVER=192.168.0.25;UID=AzarakhshServiceSystem;PWD=AzarakhshServiceSystem@13579;database=AzarakhshServiceSystem')
#print('DRIVER=FreeTDS; SERVER='+sys.argv[3]+';UID='+sys.argv[4]+';PWD='+sys.argv[5]+';database='+sys.argv[6])
conn = pyodbc.connect('DRIVER=FreeTDS;SERVER='+sys.argv[3]+';UID='+sys.argv[4]+';PWD='+sys.argv[5]+';database='+sys.argv[6]+';TDS_Version=7.2')
#conn = pyodbc.connect('DRIVER=FreeTDS;SERVER=192.168.0.78\\SQL2017R2;UID=sa;PWD=Azarakhsh@Ws;database=Web_Hr;TDS_Version=7.2')
#print('DRIVER=FreeTDS; SERVER='+sys.argv[3]+';UID='+sys.argv[4]+';PWD='+sys.argv[5]+';database='+sys.argv[6]+';TDS_Version=7.2')
#conn = pyodbc.connect('DRIVER=FreeTDS;trusted_connection=tcon;port=1433; SERVER=192.168.0.25;UID=AzarakhshServiceSystem;PWD=AzarakhshServiceSystem@13579;database=AzarakhshServiceSystem;TDS_Version=7.2')



cursor = conn.cursor()

returnListtemp=list()
returnlist=list()

msg_101='No_Device'
msg_102='No_Member_In_Restaurant'
msg_103='No_Meal_In_Restaurant'
msg_104='No_Reserve_Food_In_Token'
msg_105='Food_Received'
msg_106='No_Calendar_In_FoodCalendar'

current_time1 = datetime.datetime.now().time()
current_Datetime=datetime.datetime.now()
current_Date=date.today()
current_time2=datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
currentDT = datetime.datetime.now().strftime("%H:%M")




def AutoReserver(number):
   return number*20


def UpdateTokenPrint(tokenReseveDateparam,tokenMemberOfRestaurantIdparam,tokenFoodCalenderIdparam,cursorparam,current_timeparam) :     
     updateQuery=('update food.token set Printed=1,Delivered=1,PrintedDate = '+ '\'' + current_timeparam + '\'' + ' where \
        ReserveDate = ' + '\'' + tokenReseveDateparam + '\'' + 'and \
        MembersOfRestaurantId = ' + '\'' + str( tokenMemberOfRestaurantIdparam) + '\'' + ' and \
        FoodCalenderId = ' + '\'' + str(tokenFoodCalenderIdparam) + '\'' )
     cursorparam.execute(updateQuery)
     conn.commit()


def TokenLisFunc(mealIdparam,MemberOfRestaurantIdparam,current_Dateparam,printedparam,cursorparam) :
   queryTokenList=('select count(t.FoodCalenderId), t.FoodCalenderId ,t.ReserveDate,t.DayName,cast(t.Price as bigint),\
     t.MembersOfRestaurantId,fc.MealId,fc.FoodId,f.FoodName,f.FoodType,dbo.sdatetosolar(t.ReserveDate) from food.token t inner join food.FoodCalendar fc on \
     t.FoodCalenderId = fc.FoodCalendarId inner join food.Food f on f.FoodId = fc.FoodId \
     where t.Payment=1 and fc.MealId = ' + str(mealIdparam) + ' and t.MembersOfRestaurantId = ' + str(MemberOfRestaurantIdparam) + 'and \
     fc.CalendarDate = ' + '\'' + str(current_Dateparam) + '\'' + 'and t.Printed = ' + '\'' + str(printedparam) +  '\'' + ' group by t.FoodCalenderId,\
     t.ReserveDate,t.DayName,t.Price,t.MembersOfRestaurantId,fc.MealId,fc.FoodId,f.FoodName,f.FoodType' )
   cursor.execute(queryTokenList)
   if cursor.rowcount == 0 :
      return 0
   elif  cursor.rowcount == -1 :
      if printedparam == 0 :
         returnListtemp.insert(0,'msg_true')
         tokenListReturn = cursor.fetchall()
         return tokenListReturn
      elif printedparam == 1 :
         returnListtemp.insert(0,msg_105)
         tokenListReturn=cursor.fetchall()
         return tokenListReturn



def FillreturnListtemp(tokenListparam) :
    for tokenRow in tokenListparam :
        token=tokenRow
        tokenReseveDate=str(token[2])
        tokenFoodCalenderId= token[1]
        tokenMemberOfRestaurantId=token[5]
        returnListtemp.append(str(token[10])) # append reservedate to list
        returnListtemp.append(token[3]) # append day name to list
        returnListtemp.append(str(token[4])) # append Food Price to list
        returnListtemp.append(token[8]) # append Food  Name to list
        returnListtemp.append(str(token[0])) # append count of food
        returnListtemp.append(currentDT) # append HH:MM to list
        returnListtemp.append('@')
        current_Datetime=datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        UpdateTokenPrint(tokenReseveDate,tokenMemberOfRestaurantId,tokenFoodCalenderId,cursor,current_Datetime)
               

query=('select * from Food.Machine m inner join Food.MachinesOfRestaurant mor on m.machineid=mor.machineid  inner join food.Restaurants r on mor.RestaurantsId=r.RestaurantsId where m.IpAdress = ' + '\'' + sys.argv[2] + '\'')
 
cursor.execute(query)

if cursor.rowcount==0 : # no record in machineOfRestaurant

   returnListtemp.insert(0,msg_101) # 'No_Device'
   returnlist=returnListtemp 
elif  cursor.rowcount==-1 :
  
   machineOfRestaurantList = cursor.fetchall()
   machineOfRestaurant=machineOfRestaurantList[0]
   _currentRestaurantName=machineOfRestaurant[17]
   returnListtemp.append(machineOfRestaurant[17]) # append restaurant name to List

   cursor.execute('SELECT * FROM Food.MembersOfRestaurant where CardNo='+sys.argv[1] +'and RestaurantsId ='+'\''+str(machineOfRestaurant[14])+'\'') #[Id],[ResturantsId],[NationalNo],[Accept],[Reject],[MemberTypeId],[ReceiptNumber],[DateOfPayment],[CardNumber]
   if cursor.rowcount==0 : 
      returnListtemp.insert(0,msg_102) #'msg_102 => No_Member_In_Restaurant'
      returnlist=returnListtemp 
   elif  cursor.rowcount==-1 :   
      MemberOfRestaurantList=cursor.fetchall()
      MemberOfRestaurant=MemberOfRestaurantList[0]
      _memberOfRestaurantId=MemberOfRestaurant[0]
      _memberOfRestaurantName=MemberOfRestaurant[2]
      returnListtemp.append(MemberOfRestaurant[2]) #connectToDataBase append Member name to List
      _menberOfRestaurantCardNo=MemberOfRestaurant[5]
      returnListtemp.append(MemberOfRestaurant[5]) # append Member CardNo to List
     
      current_time = datetime.datetime.now().time()
      timeSpan=((current_time.hour*60)+(current_time.minute))

      stringTimespan=str(timeSpan)
      queryMealList=('select * from Food.Meal m where m.RestaurantsId ='+'\''+ str(machineOfRestaurant[14]) +'\''  + 'and (m.FromTime <=' +'\''+ stringTimespan +'\''+ 'and '+'\''+stringTimespan+'\''+'<= m.EndTime)')

      cursor.execute(queryMealList)
      if cursor.rowcount==0 :
         returnListtemp.insert(0,msg_103)
         returnlist=returnListtemp 
      elif  cursor.rowcount==-1 :           
         mealList=cursor.fetchall()
        
         returnlistFull=list()
         returnlistinit = [_currentRestaurantName,_memberOfRestaurantName,_menberOfRestaurantCardNo]
         #returnlist = list((_currentRestaurantName, _memberOfRestaurantName, _menberOfRestaurantCardNo))
         #returnCurrentlist= [, ]
         #returnlist=returnListtemp.copy()
         for meal in mealList :  
             
             returnListtemp.clear()
             returnListtemp=returnlistinit.copy()
             mealId=meal[0]
             returnListtemp.append(str(meal[2])) # append Meal Type Code to List : 1 => breakfast   2 => lunch  3 => dinner
             queryFoodCalendar=('select * from food.FoodCalendar fc inner join food.Meal m on m.MealId=fc.MealId where fc.CalendarDate=' + '\'' + str(current_Date) + '\'' + 'and m.RestaurantsId='+'\''+ str(machineOfRestaurant[14]) +'\''  + 'and m.MealId=' + '\'' + str(mealId) + '\'')           
             cursor.execute(queryFoodCalendar)
             if cursor.rowcount==0 :
              returnListtemp.insert(0,msg_106)
             elif cursor.rowcount==-1 :  
              tokenList=TokenLisFunc(mealId,_memberOfRestaurantId,current_Date,0,cursor )
 
              if tokenList == 0 :
             
                 tokenListRecived=TokenLisFunc(mealId,_memberOfRestaurantId,current_Date,1,cursor )
 
                 if tokenListRecived==0 :
 
                    returnListtemp.insert(0,msg_104)
 
                 else :
 
                    FillreturnListtemp(tokenListRecived)
 
              else :
 
                    FillreturnListtemp(tokenList)
 
              returnlistFull.extend(returnListtemp)
              #returnlistFull.append(';') 
 
# -- check fo r  read_returislist 
 
 
 
             if len(returnlist) < 7  :
                returnlist=returnListtemp.copy()
             elif len(returnListtemp) > 5 :
                returnlist.extend(returnListtemp)
             
             returnlist.append(';')  
         if len(returnlist) == 0 :      
            returnlist=returnListtemp.copy() 
         #returnListtemp.clear()
     

x = "#".join(returnlist)
 

print(x)
