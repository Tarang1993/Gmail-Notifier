import urllib,pyttsx
import urllib2
import sys, feedparser
import serial
import time

username="username@gmail.com"
password="password"
proto="https://"
server="mail.google.com"
path="/gmail/feed/atom"

SERIALPORT = "/dev/ttyUSB0" 

engine = pyttsx.init()
rate = engine.getProperty('rate')
engine.setProperty('rate', rate-50)
volume = engine.getProperty('volume')
engine.setProperty('volume', volume+1.25)

try:
	ser = serial.Serial(SERIALPORT, 9600)
except serial.SerialException:
    	sys.exit() 


while(True):
	time.sleep(120)
	newmails = int(feedparser.parse(
    	proto + username + ":" + password + "@" + server + path
	)['feed']['fullcount'])

	xml = feedparser.parse(
        proto + username + ":" + password + "@" + server + path
        )
	
	print "You have "+newmails+" unread emails"	
	if newmails > 0:
		gmail_latest = xml.entries[0]
		title = gmail_latest.title
		author = gmail_latest.author
		print "You have got a new mail from "+author
		print "The subject of the mail is "+title
		engine.say('You have got a new mail from'+author)	
		engine.say("The subject of the mail is "+title)
		ser.write(" ")
		ser.write(author)
		ser.write(" ")
		ser.write(title)
		ser.write(" ")
		ser.flushOutput()
		engine.runAndWait()
	
	if newmails == 0:
		ser.write('n')
