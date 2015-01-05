import requests
import json
import re

TOKEN = '<Enter Facebook Graph API v1.0 Token Here>'

def getPageData(u):
	query = str(u) + "?fields=about,bio,description,name,category"
	payload = {'access_token': TOKEN}
	r = requests.get('https://graph.facebook.com/v1.0/' + query, params=payload)
	result = json.loads(r.text)
	answer = ""
	if 'about' in result:
		answer += result['about'] + " "
	if 'bio' in result:
		answer += result['bio'] + " "
	if 'description' in result:
		answer += result['description'] + " "
	if 'category' in result:
		answer += result['category'] + " "
	if 'name' in result:
		answer += result['name']
	if 'error' in result:
		if not (result['error']['code'] == 100 or result['error']['code'] == 21):
			exit(1)
	return answer

pages = []

with open('unique_likes.txt', 'r') as likes:
	for line in likes:
		line = line.split(':')
		pages.append(line[0])

likes.close()
print(str(len(pages)) + " pages.")

count = 0

# Enter start and end points here. Can be used to split and retrieve in parallel
startpoint = 0
endpoint = 10000

with open('like_data.txt', 'a') as likefile:
	for page in pages:
		if count < startpoint:
			count += 1
			continue
		if count >= endpoint:
			break
		if not page.isdigit():
			count += 1
			continue
		result = getPageData(page)
		result = re.sub('\s', ' ', result)
		likefile.write(page + ": " + result)
		likefile.write('\n')
		count += 1
		print("Done " + str(count) + " pages.")

likefile.close()
