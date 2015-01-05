import requests
import json

TOKEN = '<Enter your Facebook Graph API v1.0 Access Token here>'

ouruids = [1234, 2345, 3456, 4567] # Four example IDs of people in the network whose friends were retrieved

def getFriends(u):
	final = []
	query = "select uid2 from friend where uid1 = " + str(u) + " and (" \
				  + "( uid2 in ( select uid2 from friend where uid1 = " + str(ouruids[0]) + ") ) or " \
					+ "( uid2 in ( select uid2 from friend where uid1 = " + str(ouruids[1]) + ") ) or " \
					+ "( uid2 in ( select uid2 from friend where uid1 = " + str(ouruids[2]) + ") ) or " \
					+ "( uid2 in ( select uid2 from friend where uid1 = " + str(ouruids[3]) + ") ) )"
	payload = {'q' : query, 'access_token': TOKEN}
	r = requests.get('https://graph.facebook.com/fql', params=payload)
	result = json.loads(r.text)
	return result['data']

userlist = []

with open('my_friends.txt', 'r') as allusers:
	for line in allusers:
		line = line.split(':')
		userlist.append([line[0], line[1]])

allusers.close()
print(str(len(userlist)) + " friends.")

count = 0

# Change start point if retrieval fails in the middle
startpoint = 0

with open('adjacency_final.txt', 'a') as adjlist:
	for [user, uid] in userlist:
		if count < startpoint:
			count += 1
			continue
		results = getFriends(uid)
		adjlist.write(str(uid) + " " + str(len(results)) + " ")
		for eachdict in results:
			adjlist.write(str(eachdict['uid2']) + " ")
		adjlist.write('\n')
		count += 1
		print("Done with " + str(count) + " users after " + user)

adjlist.close()
