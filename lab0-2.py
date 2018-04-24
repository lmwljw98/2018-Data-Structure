"""
f = open("Lab0-2.dat", 'w')

data = "A program that translates a high level language to a machine language\nis called a compiler. A compiler is thus a somewhat peculiar sort\nof program and its output is yet another program. To avoid confusion,\nthe input program is usually called the source program or\nsource code, and the translated version produced by the compiler is called"

f.write(data)
f.close()
"""

file = open("Lab0-2.dat", 'r')
context = file.readlines()


def wordcount(line):
    state = False
    wc = 0

    for i in range(0, len(line)):
        if line[i].isalpha():
            if not state:
                wc += 1
                state = True
        elif line[i] == ' ':
            state = False
    return wc


total_count = 0

for m in range(len(context)):
    print(context[m])
    count = wordcount(context[m])
    print("The number of words: " + str(count))
    total_count += count

print("Total Number of Words: " + str(total_count))
