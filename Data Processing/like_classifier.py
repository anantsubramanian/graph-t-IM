import re

product_list = {}

with open('Products.txt', 'r') as products:
	for line in products:
		line = line.strip().split(':')
		product_list[line[0]] = [ keyword for keyword in line[1].strip().split() if len(keyword) > 0 ]
		
products.close()

count = {}
for val in product_list:
	count[val] = 0

with open('like_data.txt', 'r') as likesfile:
	with open('classified_likes.txt', 'w') as classfile:
		for line in likesfile:
			pageid = line.strip().split(':')[0]
			line = line.lower()
			if len(line) == 0:
				continue
			maxim = 0
			bestprod = ""
			for product in product_list:
				tofind = ""
				for word in product_list[product]:
					tofind += word + "|"
				tofind = tofind[:-1]
				prodcount = len(re.findall(tofind, line))
				if prodcount > maxim:
					maxim = prodcount
					bestprod = product
			if maxim > 0:
				count[bestprod] += 1
				classfile.write(pageid + " " + bestprod + "\n")

classfile.close()
likesfile.close()
print(count)
