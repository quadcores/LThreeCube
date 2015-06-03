from pymongo import MongoClient

def cleardbase():
  client = MongoClient()
  db = client.log
  collection = db.http

  collection.remove({})
