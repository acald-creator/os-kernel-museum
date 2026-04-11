sed 's/#.*//' hex.he | xxd -r -ps > hex_

nasm hex.asm -f bin -l hex.lst
chmod +x hex
od -Ax -tx1 hex > hex-output

strace ./hex_ < hex2.he > hex2a && chmod +x hex2a
