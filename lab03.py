f = open("lab2-1.txt", 'r')

array = []
output = []


def transpose(a, b):
    b[0][0] = a[0][1]
    b[0][1] = a[0][0]
    b[0][2] = a[0][2]

    if a[0][2] > 0:
        currentb = 1
        for i in range(0, a[0][1]):
            for j in range(1, a[0][2] + 1):
                if a[j][1] == i:
                    b[currentb][0] = a[j][1]
                    b[currentb][1] = a[j][0]
                    b[currentb][2] = a[j][2]
                    currentb += 1


data = f.readline()
array.append([int(data.split()[0]), int(data.split()[1]), int(data.split()[2])])
while data.endswith('\n'):
    data = f.readline()
    array.append([int(data.split()[0]), int(data.split()[1]), int(data.split()[2])])

for m in range(len(array)):
    output.append([0, 0, 0])

print("Array A:", array)
transpose(array, output)
print("Array B:", output)