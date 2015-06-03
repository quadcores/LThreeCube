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
  f = open('http_data_output.txt', 'w')
  i=0
  for line in fp:
    matchLine = re.match( r'(.*)\n(.*)', line)
    if matchLine:

      matchObj = re.match( r'(.*) (.*) (.*) \[((.*)/(.*)/(.*):(.*):(.*):(.*) (.*))\] "(.*) (.*) (.*)" (.*) (.*) "(.*)" "((M|C|S)\S*)\s(.*)"', matchLine.group(1))
      if(matchObj):

        i=i+1
        s = '================================================================================================================================\n'
        s += 'Packet Number :: '
        n = str(i)
        s += n
        s += '\n'
        f.write(s)

        s = 'IP: '
        n = str(matchObj.group(1))
        s+=n
        s+='\n'
        f.write(s)
        ip = matchObj.group(1)

        s = 'Date: '
        n = str(matchObj.group(5))
        s+=n
        s+='\n'
        f.write(s)
        date = matchObj.group(5)

        s = 'Month: '
        n = str(matchObj.group(6))
        s+=n
        s+='\n'
        f.write(s)        
        month = matchObj.group(6)

        s = 'Year: '
        n = str(matchObj.group(7))
        s+=n
        s+='\n'
        f.write(s)
        year = matchObj.group(7)

        s = 'Time : '
        #s = 'HH: '
        n = str(matchObj.group(8))
        s += n
        s += ':'
        #f.write(s)
        hours = matchObj.group(8)

        #s = 'MM: '
        n = str(matchObj.group(9))
        s += n
        s +=':'
        #f.write(s)
        minutes = matchObj.group(9)

       	#s = 'SS: '
        n = str(matchObj.group(10))
        s += n
        s += '\n'
        f.write(s)
        seconds = matchObj.group(10)

        s = 'Time Zone: '
        n = str(matchObj.group(11))
        s+=n
        s+='\n'
        f.write(s)
        timezone = matchObj.group(11)

        s = 'Request Method: '
        n = str(matchObj.group(12))
        s+=n
        s+='\n'
        f.write(s)
        reqmeth = matchObj.group(12)

        s = 'Request_URL: '
        n = str(matchObj.group(13))
        s+=n
        s+='\n'
        f.write(s)
        requri = matchObj.group(13)

        s = 'HTTP_version: '
        n = str(matchObj.group(14))
        s+=n
        s+='\n'
        f.write(s)
        httpver = matchObj.group(14)

        s = 'Response Status Code: '
        n = str(matchObj.group(15))
        s+=n
        s+='\n'
        f.write(s)        
        resstat = matchObj.group(15)

        s = 'Port No.: '
        n = str(matchObj.group(16))
        s+=n
        s+='\n'
        f.write(s)
        pnc = matchObj.group(16)

        s = 'Site Name: '
        n = str(matchObj.group(17))
        s+=n
        s+='\n'
        f.write(s)
        sitename = matchObj.group(17)

        s = 'Browser: '
        n = str(matchObj.group(18))
        s+=n
        s+='\n'
        f.write(s)
        brows = matchObj.group(18)

        s = 'Other Info: '
        n = str(matchObj.group(20))
        s+=n
        s+='\n'
        f.write(s)
        otherinf = matchObj.group(20)

        s = '================================================================================================================================\n\n'
        f.write(s)

      else:

        matchObj = re.match( r'(.*) (.*) (.*) \[((.*)/(.*)/(.*):(.*):(.*):(.*) (.*))\] "(.*) (.*) (.*)" (.*) (.*) "(.*)" "(.*)"', matchLine.group(1))
        if(matchObj):

          i=i+1
          s = '================================================================================================================================\n'
          s += 'Packet Number :: '
          n = str(i)
          s += n
          s += '\n'
          f.write(s)

          s = 'IP : '
          n = str(matchObj.group(1))
          s+=n
          s+='\n'
          f.write(s)
          ip = matchObj.group(1)

          s = 'Date: '
          n = str(matchObj.group(5))
          s+=n
          s+='\n'
          f.write(s)
          date = matchObj.group(5)

          s = 'Month: '
          n = str(matchObj.group(6))
          s+=n
          s+='\n'
          f.write(s)
          month = matchObj.group(6)

          s = 'Year: '
          n = str(matchObj.group(7))
          s+=n
          s+='\n'
          f.write(s)
          year = matchObj.group(7)

          s = 'Time: '
          #s = 'HH: '
          n = str(matchObj.group(8))
          s += n
          #s += '\n'
          s += ':'
          hours = matchObj.group(8)
          
          #s = 'MM: '
          n = str(matchObj.group(9))
          s += n
          #s+='\n'
          s += ':'
          minutes = matchObj.group(9)
          
          #s = 'SS: '
          n = str(matchObj.group(10))
          s += n
          s += '\n'
          f.write(s)
          seconds = matchObj.group(10)

          s = 'Time Zone: '
          n = str(matchObj.group(11))
          s+=n
          s+='\n'
          f.write(s)
          timezone = matchObj.group(11)

          s = 'Request Method '
          n = str(matchObj.group(12))
          s+=n
          s+='\n'
          f.write(s)
          reqmeth = matchObj.group(12)

          s = 'Request_URL: '
          n = str(matchObj.group(13))
          s+=n
          s+='\n'
          f.write(s)
          requri = matchObj.group(13)

          s = 'HTTP_version: '
          n = str(matchObj.group(14))
          s+=n
          s+='\n'
          f.write(s)
          httpver = matchObj.group(14)

          s = 'Response Status Code: '
          n = str(matchObj.group(15))
          s+=n
          s+='\n'
          f.write(s)
          resstat = matchObj.group(15)

          s = 'Port No.: '
          n = str(matchObj.group(16))
          s+=n
          s+='\n'
          f.write(s)
          pnc = matchObj.group(16)

          s = 'Site Name: '
          n = str(matchObj.group(17))
          s+=n
          s+='\n'
          f.write(s)
          sitename = matchObj.group(17)

          n = 'Browser: - \n'
          f.write(n)
          brows = "-"

          s = 'Other Info: '
          n = str(matchObj.group(18))
          s+=n
          s+='\n'
          f.write(s)
          otherinf = matchObj.group(18)

          s = '================================================================================================================================\n\n'
          f.write(s)

      monthnum = httpmongo.getmonthnum(month)
      country = pygeo.country_by_ip(ip)

      httpmongo.connection(ip,int(date),monthnum,int(year),int(hours),int(minutes),int(seconds),timezone,reqmeth,requri,httpver,resstat,pnc,sitename,brows,otherinf,country)

  fp = matchLine.group(2)

#def getcounbyip():
#  pygeo.country_by_ip()

if __name__ == '__main__':
  main(sys.argv[1:])	
 # getcounbyip()
