import requests
import json

TOKEN = '<Enter Facebook Graph API v1.0 Access Token here>'

def get_posts():
	query = "select name, uid from user where uid in (select uid2 from friend where uid1 = me())"
	payload = {'q': query, 'access_token': TOKEN}
	r = requests.get('https://graph.facebook.com/fql', params=payload)
	result = json.loads(r.text)
	return result['data']

def get_likes(u):
	final = []
	query=str(u)+"/likes?fields=name,id"
	payload = {'access_token': TOKEN}
	r = requests.get('https://graph.facebook.com/v1.0/' + query, params=payload)
	result = json.loads(r.text)
	final.extend(result['data'])
	while True:
		if not ('paging' in result):
			break
		result = result['paging']
		if not ('next' in result):
			break
		query = result['next']
		r = requests.get(query, params=payload)
		result = json.loads(r.text)
		if not ('data' in result):
			continue
		final.extend(result['data'])
	return final

userlist = []

for userdict in get_posts():
	userlist.append([userdict['name'], userdict['uid']])

print(str(len(userlist)) + " friends.")

with open('my_friends.txt', 'w') as userfile:
	for [user, userid] in userlist:
		userfile.write(user + " " + str(userid) + "\n")

userfile.close()
count = 0

# If retrieval fails, use this to resume
startpoint = 0

for [user, userid] in userlist:
	if count < startpoint:
		count += 1
		continue
	curuserfile = open("Likes_of_Friends/" + user + '.txt', 'w')
	for pagedict in get_likes(userid):
		curuserfile.write(pagedict['name'] + "\n")
		curuserfile.write(str(pagedict['id']) + "\n")
	curuserfile.close()
	count += 1
	print(str(count) + " users done with " + user)
