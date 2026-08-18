i = 1
swg = 0
print("Welcome to SnakeWaterGun(SWG) Game\n")
while(True):
    print("Options\n0 for Snake\n1 for Water\n2 for Gun")
    swg = (int(input("Enter your choice from above options:")))

    f = open("PYTHON/File.txt", 'r')
    for j in range(1):
        n = int(f.readline())
        if(n == swg):
            print(f"You: {swg}")
            print(f"SM: {n}")
            print("Draw")
        elif(n == 0 and swg == 1):  
            print(f"You: {swg}")
            print(f"SM: {n}")
            print("SM Win\nYou Lose!!!")
        elif(n == 0 and swg == 2):
            print(f"You: {swg}")
            print(f"SM: {n}")
            print("You Win\nSM Lose!!!")
        elif(n == 1 and swg == 0):
            print(f"You: {swg}")
            print(f"SM: {n}")
            print("You Win\nSM Lose!!!")     
        elif(n == 1 and swg == 2):
            print(f"You: {swg}")
            print(f"SM: {n}")
            print("SM Win\nYou Lose!!!")
        elif(n == 2 and swg == 0):
            print(f"You: {swg}")
            print(f"SM: {n}")
            print("SM Win\nYou Lose!!!")
        elif(n == 2 and swg == 1):
            print(f"You: {swg}")
            print(f"SM: {n}")
            print("You Win\nSM Lose!!!") 
        else:
            print("You Enter Invalid Number!!!!")
            break; 
        i= i+ 1