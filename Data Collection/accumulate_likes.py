from os import listdir
from os.path import isfile, join

files = [ join("Likes_of_Friends", f) for f in listdir("Likes_of_Friends") ]

allpages = {}

for curfile in files:
	with open(curfile, 'r') as f:
		count = 0
		name = ""
		for line in f:
			count += 1
			if not (count % 2 == 0):
				name = line.strip()
			else:
				allpages[name] = line.strip()
	f.close()

with open('unique_likes.txt', 'w') as f:
	for key in allpages:
		f.write(allpages[key] + ":" + key + "\n")

f.close()
