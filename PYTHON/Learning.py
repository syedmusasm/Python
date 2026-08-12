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

with open("PYTHON/Musa_Intro.txt", "a") as f:
     f.write("\n Hello Guys!")
     f.write("My name is Muhammad Musa SM")







