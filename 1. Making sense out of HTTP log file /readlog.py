import time
import re
import httpmongo
import pygeo
import cleardata
import sys

def main(argv):
  cleardb()
  readinput(sys.argv)

def cleardb():
  #used for initially clearing the database
  cleardata.cleardbase()

def readinput(listargs):
  #reading input from the weblog file line by line
  fp = open(listargs[1], 'r')

  for line in fp:
    matchLine = re.match( r'(.*)\n(.*)', line)
    if matchLine:

      matchObj = re.match( r'(.*) (.*) (.*) \[((.*)/(.*)/(.*):(.*):(.*):(.*) (.*))\] "(.*) (.*) (.*)" (.*) (.*) "(.*)" "((M|C|S)\S*)\s(.*)"', matchLine.group(1))
      if(matchObj):
        ip = matchObj.group(1)
        #print "(5) Date: \t\t\t", matchObj.group(5)
        date = matchObj.group(5)
        #print "(6) Month: \t\t\t", matchObj.group(6)
        month = matchObj.group(6)
        #print "(7) Year: \t\t\t", matchObj.group(7)
        year = matchObj.group(7)
        #print "(8) HH: \t\t\t", matchObj.group(8)
        hours = matchObj.group(8)
        #print "(9) MM: \t\t\t", matchObj.group(9)
        minutes = matchObj.group(9)
        #print "(10) SS: \t\t\t", matchObj.group(10)
        seconds = matchObj.group(10)
        #print "(11) Time Zone: \t\t", matchObj.group(11)
        timezone = matchObj.group(11)
        #print "(12) Request Method: \t\t", matchObj.group(12)
        reqmeth = matchObj.group(12)
        #print "(13) Request_URL: \t\t", matchObj.group(13)
        requri = matchObj.group(13)
        #print "(14) HTTP_version: \t\t", matchObj.group(14)
        httpver = matchObj.group(14)
        #print "(15) Response Status Code: \t", matchObj.group(15)
        resstat = matchObj.group(15)
        #print "(16) Port No.: \t\t\t", matchObj.group(16)
        pnc = matchObj.group(16)
        #print "(17) Site Name: \t\t", matchObj.group(17)
        sitename = matchObj.group(17)
        #print "(18) Browser: \t\t\t", matchObj.group(18)
        brows = matchObj.group(18)
        #print "(19) Other Info: \t\t", matchObj.group(20)
        otherinf = matchObj.group(20)

      else:

        matchObj = re.match( r'(.*) (.*) (.*) \[((.*)/(.*)/(.*):(.*):(.*):(.*) (.*))\] "(.*) (.*) (.*)" (.*) (.*) "(.*)" "(.*)"', matchLine.group(1))
        if(matchObj):
          #print "\n(1) IP : \t\t\t", matchObj.group(1)
          ip = matchObj.group(1)
          #print "(5) Date: \t\t\t", matchObj.group(5)
          date = matchObj.group(5)
          #print "(6) Month: \t\t\t", matchObj.group(6)
          month = matchObj.group(6)
          #print "(7) Year: \t\t\t", matchObj.group(7)
          year = matchObj.group(7)
          #print "(8) HH: \t\t\t", matchObj.group(8)
          hours = matchObj.group(8)
          #print "(9) MM: \t\t\t", matchObj.group(9)
          minutes = matchObj.group(9)
          #print "(10) SS: \t\t\t", matchObj.group(10)
          seconds = matchObj.group(10)
          #print "(11) Time Zone: \t\t", matchObj.group(11)
          timezone = matchObj.group(11)
          #print "(12) Request Method: \t\t", matchObj.group(12)
          reqmeth = matchObj.group(12)
          #print "(13) Request_URL: \t\t", matchObj.group(13)
          requri = matchObj.group(13)
          #print "(14) HTTP_version: \t\t", matchObj.group(14)
          httpver = matchObj.group(14)
          #print "(15) Response Status Code: \t", matchObj.group(15)
          resstat = matchObj.group(15)
          #print "(16) Port No.: \t\t\t", matchObj.group(16)
          pnc = matchObj.group(16)
          #print "(17) Site Name: \t\t", matchObj.group(17)
          sitename = matchObj.group(17)
          #print "(18) Browser: \t\t\t-\n",
          brows = "-"
          #print "(19) Other Info: \t\t", matchObj.group(18)
          otherinf = matchObj.group(18)

      monthnum = httpmongo.getmonthnum(month)
      country = pygeo.country_by_ip(ip)

      httpmongo.connection(ip,int(date),monthnum,int(year),int(hours),int(minutes),int(seconds),timezone,reqmeth,requri,httpver,resstat,pnc,sitename,brows,otherinf,country)

  fp = matchLine.group(2)

#def getcounbyip():
#  pygeo.country_by_ip()

if __name__ == '__main__':
  main(sys.argv[1:])	
 # getcounbyip()
