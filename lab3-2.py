f = open('lab3-2.txt', 'r')


def push(val):
    global top
    top += 1
    stack[top] = val


def pop():
    global top
    fin = top
    top -= 1
    return stack[fin]


def isEmpty():
    global top
    return top == -1


def isFull():
    global top
    return top == len(stack)


if __name__ == "__main__":
    a = f.read()
    top = -1
    stack = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    print("check stack full: " + str(isFull()))
    print("check stack empty: " + str(isEmpty()))
    print()
    for i in range(len(a.split())):
        data = a.split()[i]
        j = 0
        if (len(data) % 2 == 0):
            while j < (len(data) // 2):
                push(data[j])
                j += 1
        else:
            while j < (len(data) // 2):
                push(data[j])
                j += 1
            j += 1
        while j < len(data):
            if (pop() == data[j]):
                j += 1
            else:
                print(data + " Error")
                break
        if j == len(data):
            print(data + " PALINDROME")
