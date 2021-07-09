import random


ret = []

ret2 = []

iv = []

diff = [0, 158, 22, 175]
diff2 = [0, 136, 22, 149]

for i in range(4):
	for j in range(4):	
		a = random.randint(0,0xff)
		if (i % 2) == 0:
			ret.append(a)
			ret2.append(a ^ diff[j % 4])
		else:
			ret.append(a)
			ret2.append(a ^ diff2[j % 4])

for i in range(16):
	a = random.randint(0,0xff)
	iv.append(a)


print((ret))
print((ret2))

for i in range(len(ret)):
	if i % 4 == 0 :
		print("-----------------------------------")
	print(ret[i] ^ ret2[i])
print(iv)


