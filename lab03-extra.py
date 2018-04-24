from math import pi

f = open("lab2-2.txt", "r")
array = []
data = f.readlines()


def calc(data):
    for i in range(len(data)):
        data[i].rstrip('\n')
        # print(data)
        if data[i].split()[0] == 'circle':
            radius = float(data[i].split()[1])
            circle = pi * (radius ** 2)
            array.append([data[i].split()[0], radius, circle])

        elif data[i].split()[0] == 'triangle':
            base = float(data[i].split()[1])
            height = float(data[i].split()[2])
            triangle = (base * height / 2)
            array.append([data[i].split()[0], base, height, triangle])

        elif data[i].split()[0] == 'rectangle':
            side1 = float(data[i].split()[1])
            side2 = float(data[i].split()[2])
            rectangle = side1 * side2
            array.append([data[i].split()[0], side1, side2, rectangle])


calc(data)
for j in range(len(array)):
    print(array[j])
