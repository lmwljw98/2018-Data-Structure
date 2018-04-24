f = open("Lab0-1.dat", 'w')
data = "90,40,60,10,50,80,20,70,15,25"
f.write(data)
f.close()

file = open("Lab0-1.dat", 'r')
num_list = file.readline().split(',')

for i in range(len(num_list)):
    num_list[i] = int(num_list[i])


# print(num_list)

def findMin(num_list, n):
    min = num_list[0]
    index = 0
    for i in range(1, n):
        if num_list[i] < min:
            min = num_list[i]
            index = i
    return min, index


def findMax(num_list, n):
    max = num_list[0]
    index = 0
    for i in range(1, n):
        if num_list[i] > max:
            max = num_list[i]
            index = i
    return max, index


min_num = findMin(num_list, 10)
max_num = findMax(num_list, 10)
print("Minimum number is " + str(min_num[0]) + " at position " + str(min_num[1] + 1))
print("Maximum number is " + str(max_num[0]) + " at position " + str(max_num[1] + 1))
