import sys

adj = {}

if len(sys.argv) <= 1:
	print("Please specify file.")
	exit()

with open(sys.argv[1], 'r') as f:
	for line in f:
		line = line.strip().split()
		for i in range(2, len(line), 6):
			if not (line[0] in adj):
				adj[line[0]] = []
			adj[line[0]].append([line[i], line[i+1], line[i+2], line[i+4], line[i+5]])

f.close()
print('graph\n[\n')
for key in adj:
	print('\tnode\n\t[\n\t\t', end="")
	print('id ' + key + '\n\t]')

for key in adj:
	for [end, prod, weight, prod2, weight2] in adj[key]:
		print('\tedge\n\t[\n\t\t', end="")
		print('source ' + key + '\n\t\t', end="")
		print('target ' + end + '\n\t\t', end="")
		print('weight ' + str(1 - float(weight)) + '\n\t\t', end="")
		print('label "' + weight + '"\n\t]')

print(']')
