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

marks = [1,2,3,4,5,6]

for index,mark in enumerate(marks):
    print(mark)
    if(index == 5):
        print("SM, Awesome")




