import pygeoip
from pymongo import MongoClient

def country_by_ip(ip):
	#create connection with mongodb
	client = MongoClient()
	db = client.log
	collection = db.http

	#for doc in collection.find():
	#ip = doc['IP_addr_Client']
	path = './GeoIP.dat'
	gi = pygeoip.GeoIP(path)
	return gi.country_name_by_addr(ip)

