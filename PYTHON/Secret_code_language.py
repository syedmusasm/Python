Method = input("Do you want Encode or Decode: ")
list = []
if(Method == "Encode"):
    word = input("Enter word: ")
    count = 0
    for i in word:
        list.append(i)
        count = count + 1
    if(count > 2):
        list.append(list[0])
        list.remove(list[0])
        for i in range(3):
            list.insert(i, chr(ord("a")+ i))
            i = i +1
            count = count + 1

        j = count
        itr = 0
        while(True):
            list.insert(j, chr(ord("m")+ itr))
            itr = itr + 1
            j = j + 1
            if(itr == 3):
                break

        print("".join(list))

    else:
        list.reverse()  
        print("".join(list))
else:
    count = 0
    word = input("Enter word: ")
    for i in word:
        list.append(i)
        count = count + 1
    if(count< 3):
        list.reverse()
        print("".join(list))
    else:
        i = 0
        while(True):
            list.remove(list[0])
            i = i +1
            count = count-1  
            if(i == 3):
                break     

        j = count
        itr = 0
        while(True):
            list.remove(list[j-1])
            count= count-1
            itr = itr +1
            j = j -1 
            if(itr == 3):
                break
        x = list.pop(count-1)
        list.insert(0,x)
        print("".join(list))

        