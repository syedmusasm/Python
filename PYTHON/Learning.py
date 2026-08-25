# print("Hello, SM")

# a = input("Enter a number: ")
# print(f"Multiplicationtable of {a} is: ")

# try:
#     for i in range(1, 11):
#         print(f"{int(a)} x {i} = {int(a)*i}")
# except: 
#     print("Invlid input")


# def func1():
#     try: 
#         list = [1,2,3,4,5]
#         i = int(input("Enter the index: "))
#         print(list[i])
#         return 1
#     except:
#         print("Invalid input")
#         return 0

#     finally:
#         print("you always know my name")

# x = func1()
# print(x)


# a = input("Enter quit: ")
# if(a != "quit"):
#     raise ValueError("Enter only quit")

# x = "Pizza"
# print(x.replace("z", 's'))

# a = 2
# b = 330
# print("A") if a > b else print("B")

# a = 3304
# b = 3303
# print("A") if a > b else print("=") if a == b else print("B")

# c = 9 if a > b else 0
# print(c)

# marks = [1,2,3,4,5,6]

# for index,mark in enumerate(marks):
#     print(mark)
#     if(index == 5):
#         print("SM, Awesome")
# import Math_Tables

# Math_Tables.Tables()

# local vs Global Variable

# x = 4
# print(x)

# def n():
#     x = 5
#     print(x)

# print(f"The Local x is {x}")
# print(f"The Global x is {x}")

# File Handling

# f = open("PYTHON/Musa_Intro.txt", 'r')
# print(f.read())
# f.close()

# f = open("PYTHON/Musa_Intro.txt", 'w')
# f.write("Hello Firends!")
# f.close()

# Directly close the File

# with open("PYTHON/Musa_Intro.txt", "a") as f:
#      f.write("\n Hello Guys!")
#      f.write("My name is Muhammad Musa SM")

# f = open("PYTHON/Musa_Intro.txt", 'r')
# i = 0
# while True:
#      i = i +1 
#      line = f.readline()
#      if line == "":
#           break
#      m1 = int(line.split(",")[0])
#      m2 = int(line.split(",")[1])
#      m3 = int(line.split(",")[2])

#      print(f"Student{i} Math marks: {m1}")
#      print(f"Student{i} English marks: {m2}")  
#      print(f"Student{i} Science marks: {m3}\n")

# f = open("PYTHON/Musa_Intro.txt", 'w')
# line = ["Syed\n", 'Musa\n', 'SM\n']
# f.writelines(line)
# f.close()

# seek & tell

# with open("PYTHON/Musa_Intro.txt", 'r') as f:
#      f.seek(8)
#      print(f.tell())
#      print(f.read(3))

# with open("PYTHON/Musa_Intro.txt", 'w') as f:
#      f.write("Hey! Musa SM")
#      f.truncate(9)

# Map, filter & reduce

# def cube(x):
#      return x*x*x

# l = [1,2,3,4,5]
# newlist = list(map(cube, l))
# print(newlist)


# def filter_(x):
#      return x > 4

# l = [1,2,3,4,5]
# newlist = list(filter(filter_, l))
# print(newlist)    

# from functools import reduce

# def sum(x, y):
#      return x + y

# l = [1,2,3,4,5]
# newlist = reduce(sum, l)
# print(newlist)   

# OOP in Python

# class person:
#     name = "Muhmmmad Musa"
#     nickname = "MM"
#     def info(self):
#         print(f"{self.name} every body knowns as {self.nickname}")


# n = person()
# n.name = "Syed Musa"
# n.nickname = "SM"
# n.info()

# Constructor

# class person():
#     def __init__(self, name , nickname):
#         print("Hello SM")
#         self.name  = name
#         self.nickname = nickname
#     def info(self):
#         print(f"{self.name} the {self.nickname}")
# n = person("Syed Musa", "SM")        
# n.info()

# Getters & Setters

class myclass():
    def __init__(self, value):
        self.value = value

    def info(self):
        print(f"Value is {self.value}")

    @property
    def getValue(self):
        return 2 * self.value

    @getValue.setter
    def getValue(self, newValue):
        self.value = newValue

obj = myclass(8)
obj.info()
obj.getValue = 9
obj.info()                 