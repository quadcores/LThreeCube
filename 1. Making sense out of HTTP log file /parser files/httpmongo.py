def getmonthnum(month):
  #this function is used to find out the month number
  #input : month name
  #output : month number
  #ptions[month]()
    global mon

    def jan():
      global mon
      mon = 1
    def feb():
      global mon
      mon = 2
    def mar():
      global mon
      mon = 3
    def apr():
      global mon
      mon = 4
    def may():
      global mon
      mon = 5
    def june():
      global mon
      mon = 6
    def july():
      global mon
      mon = 7
    def aug():
      global mon
      mon = 8
    def sep():
      global mon
      mon = 9
    def octo():
      global mon
      mon = 10
    def nov():
      global mon
      mon = 11
    def dec():
      global mon
      mon = 12

    options = {'January':jan,
            'February':feb,
            'March':mar,
            'April':apr,
            'May':may,
            'June':june,
            'July':july,
            'August':aug,
            'September':sep,
            'October':octo,
            'November':nov,
            'December':dec,
    }
    options[month]()
    return mon

def connection(ip,date,month,year,hour,minutes,seconds,timezone,reqmeth,requri,httpver,resstat,pnc,sname,brows,otherinf,country):
  #this function is used to insert entries into the database for each record
  #input : all the parameters to be put into the database
  #output : all entries into the database
    from pymongo import MongoClient
    import datetime
    client = MongoClient()
    db = client.log
    collection = db.http
    post = {"IP_addr_Client" : ip,
            "Timestamp" : datetime.datetime(year,month,date,hour,minutes,seconds),
            "Request_Method" : reqmeth,
            "Timezone" : timezone,
            "Request_URI" : requri,
            "Http_version" : httpver,
            "Response_Status_code" : resstat,
            "Port_Number_Client" : pnc,
            "Site_name" : sname,
            "Browser" : brows,
            "Other_info" : otherinf,
            "Country" : country,}
    posts = db.http
    post_id = posts.insert_one(post).inserted_id

