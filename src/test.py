import sys

print("HELLO FCKING WORLD!!!!!!")
for line in sys.stdin:
    if 'Exit' == line.rstrip():
        break
    f = open("demofile2.txt", "a")
    f.write(line)
    f.close()
    print(f'Processing Message from sys.stdin *****{line}*****')
print("Done")
