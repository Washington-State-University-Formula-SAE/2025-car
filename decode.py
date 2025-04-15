import sys
import struct

a = open(sys.argv[1], "rb").read()

for row in struct.iter_unpack(("I"*6) + ("i"*41), a):
    print(",".join(map(str, row)))
