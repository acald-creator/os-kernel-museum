import binascii
import re
import sys

with open('hex.he') as f, open('hex-new', 'wb') as out:
    for line in f:
        line = line.strip()
        accum = []
        for c in line:
            if c == "#":
                break
            elif c == ' ' or c == ' ':
                continue
            else:
                accum.append(c)
            
            if len(accum) == 2:
                byte = ''.join(accum)
                out.write(binascii.unhexlify(byte))
                accum = []