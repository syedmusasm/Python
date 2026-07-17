

QuestionList = ["What is the capital of France?/n", "How many days are there in a week?", 'What color is the sky on a clear day?', 'Which animal is known as the King of the Jungle?', "How many months are there in a year?"]
AnswerList = ["Paris", "7", "Blue", "Lion", "12"]
OptionList = [['A) London', 'B) Paris', 'C) Berlin', 'D) Madrid'], ['A) 5', 'B) 6', 'C) 7', 'D) 8'], ['A) Green', 'B) Blue', 'C) Red', 'D) Yellow'], ['A) Tiger', 'B) Elephant', 'C) Lion', 'D) Bear'], ['A) 10', 'B) 11', 'C) 12', 'D) 13']]

sum = 0

Fq = input("Do you want to play KBC enter (yes/no): ")

if(Fq == "yes"):
    print("Wlecome to KBC")

    for i in range(len(QuestionList)):
       print(QuestionList[i])       

       for n in OptionList[i]:
           print(n)

       ans = input("Enter your answer: ")

       if(ans == AnswerList[i]):
           print("Great! your answer is correct")
           sum = sum + 100

       else:
           print("Sorry! your answer is wrong") 
           Lq = input("Do you want to play more enter (1/0):")
           if(Lq == "0"):
            break     
              
print("You have won price: ", sum, "$")
print("Thanks for Playing KBC") 