users = []

with open('my_friends.txt', 'r') as userfile:
	for line in userfile:
		line = line.strip()
		if len(line) == 0:
			continue
		line = line.split(':')
		users.append([line[0], line[1]])

userfile.close()
print(str(len(users)) + " users.")

with open('userlikes.txt', 'w') as outputfile:
	for [uid, user] in users:
		f = open('Likes_of_Friends/' + user + '.txt', 'r')
		count = 0
		likes = []
		for line in f:
			line = line.strip()
			if line.isdigit():
				likes.append(line.strip())
		outputfile.write(uid + " " + str(len(likes)))
		for like in likes:
			outputfile.write(' ' + like)
		outputfile.write('\n')

outputfile.close()
