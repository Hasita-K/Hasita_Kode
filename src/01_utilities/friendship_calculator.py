def friendship_score(name1, name2):
   name1, name2 =  name1.lower(), name2.lower()
   score = 0
   shared_letters = set(name1) & set(name2)
   vowels = set('aeiou')

   score += len(shared_letters) * 5
   score += len(vowels & shared_letters) * 10
   
   return min(score, 100)

def run_friendship_calculator():
    print("💓 Friendship Compatibility Calculator 💓")
    name1 = input("Enter first name: ")
    name2 = input("Enter second name: ")

    score = friendship_score(name1, name2)

    if score > 80:
      print("You guys are like chai and samosa! Made for eachother")
    elif score > 50:
       print("You guys are warm spices")
    else:
       print("You are tea and your friend is coffee.. maybe you were not meant to be")

    print(f"\n {score}")


run_friendship_calculator()