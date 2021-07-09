iv = [234, 116, 234, 213, 159, 135, 211, 35, 229, 42, 55, 239, 204, 240, 198, 222]

iv = iv[::-1]

ret = 0x00000000000000000000000000000000

for i in range(len(iv)):
	ret = (ret  << (8 )) | iv[i]


def ret_def(m1, m2):
	dif_m = m1 ^ m2
	k1 = m1 ^ ret
	k2 = m2 ^ ret
	dif_k = k1 ^ k2
	print("differential plain:", dif_m)
	print("dufferential key  :", dif_k)



m1 = 0x4ee2f02f
m2 = 0x4e7ce680

ret_def(m1, m2)


m1 = 0xeb66ba52
m2 = 0xebf8acfd
ret_def(m1, m2)

m1 = 0x963ac11b
m2 = 0x96b2d78e
ret_def(m1, m2)

m1 = 0xbcba9c00
m2 = 0xbc328a95
ret_def(m1, m2)

m1 = 0x8c889af7
m2 = 0x8c168c58
ret_def(m1, m2)






