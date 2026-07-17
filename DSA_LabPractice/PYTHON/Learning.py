
# a = input("Enter first number: ")
# b = input("Enter second number: ")
# print(int(a) + int(b))
# print(int(a) - int(b))
# print(int(a) * int(b))
# print(int(a) / int(b))


# c = '1'
# d = '4'
# print(c+d)

# a = "Musa"
# a_length = len(a)
# print(a_length)
# print(a[:])

# print(a[-2:-1])

# nm = "harry"
# print(nm[-4:-2])

# a = "musa@@@@@@musa"
# length = len(a)
# print(a.upper())

# print(a.replace("musa", "SM"))

# a = int(input("Enter your Age: "))
# print("Your Age is: ", a)

# if(a>=18):
#     print("Yes! You can Drive")
# elif(a<18):
#     print("No! you cannot Drive")

# else:
#     print("No! you cannot Drive")

# import time 
# curr_time = time.strftime("%H")
# if(curr_time >= "00" and curr_time < "12"):
#     print("Good Morning")
# elif(curr_time >= "12" and curr_time < "17"):
#     print("Good Afternoon")
# elif(curr_time >= "17" and curr_time < "18"):
#     print("Good Evening")    
# else:
#     print("Good Night")

# day  = int(input("Enter your day number: "))
# match day:
#     case 1:
#         print("Monday")
#     case 2:
#         print("Tuesday")
#     case 3:
#         print("Wednesday")
#     case 4:
#         print("Thursday")
#     case 5:
#         print("Friday")
#     case 6:
#         print("Saturday")   
#     case 7:
#         print("Sunday")  
#     case _:
#         print("Invalid Day Number")

# for i in range(0,11,2):
#     print(i)
#     if(i==4):
#         break

# def calculateGmean(a,b):
#     mean  = (a*b)/(a+b)
#     return mean

# print(calculateGmean(4,5))

# def calculateGmean1(a,b):
#     mean  = (a*b)/(a+b)
#     print(mean)

# calculateGmean1(4,10 )

# Name  = ["Syed", "Musa", "SM", "Ahmad"]

# def PrintName(Name):
#     for i in Name:
#         print(i)

# PrintName(Name)

# def avg(*numbers):
#     sum = 0
#     for i in numbers:
#         sum+=i
#     return sum/len(numbers)


# print("Average is", avg(3,5,8,10))

# Name = [4,8,1,2]
# for i in Name:
#     print(i)

# Name.append(7)
# print(Name)
# Name.append(8)
# Name.sort()
# print(Name)

# Name.reverse()
# print(Name)

# print(Name.index(2))

# print(Name.count(8))

# Name.insert(2, 10)
# print(Name)

# Name.reverse()
# print(Name)

# m = [10, 20, 30]
# Name.extend(m)
# print(Name)

# n = [11, 22, 33]
# k = Name + n
# print(k)

# tup = (1,2,3,4,5)
# # print(tup)
# # print(tup[2:5])

# l = [6,7]
# tup = tup+tuple(l)
# print(tup)

# print(tup.count(3))
# print(tup.index(4, 2, 5))



# x = [5,3,5,7,9,8]
# last = x
# # print(first)
# # print(all)
# print(last)

# print(2 * '3' + '4')

# name = 'messi'
# if name == 'Ronaldo':
#     print("Goat")
# elif name:
#     print("Legend")
# else:
#     print("Player")

# for i in range(3):
#     print(i)

# num = [1,2,3,4]
# # num.remove(2)
# # num.pop(1)

# # print(num)

# a, b, c = int(input("Enter: "))
# print(a)
# print(b)
# print(c)

# letter = "Hey myname is {} andi am from {}"
# country = "Pakistan"
# name = "Musa"

# print(letter.format(name, country))

# name = "Musa"
# country = "Pakistan"
# print(f"hey my name is {name} and i am from {country}")

# price = 39.09999
# txt = f"for only {price:.2f} dollors$"
# # print(txt.format(price = 49.0999))
# print(txt)


# def fac(n):
#     if(n == 0):
#         return 1
    
#     return (n* fac(n-1)) 

# n = int(input("Enter the value of n: "))
# print(fac(n))  
# 

# def fib(n):
#     if(n==0):
#         return 0
#     elif(n==1):
#         return 1
    
#     return fib(n-1) +fib(n-2)
        

# print(fib(6))      

# set = {''}
# print(type(set))

# s1 = {"Syed", 'Musa', 'SM'}
# s2 = {"SM", "Musa"}
# print(s1.union(s2))
# s1.update(s2)
# print(s1, s2)

# s1.intersection_update(s2)
# print(s1)

# s3 = s1.symmetric_difference(s2)
# print(s3)


# s3 = s1.isdisjoint(s2)
# print(s3)

# d1 = {1: 11, 2: 22,5: 55, 6: 66}
# d2 = { 3: 33, 4:44}

# # d1.clear()
# print(d1)

# d1.popitem()
# print(d1)




