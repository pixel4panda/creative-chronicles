# The goal of this code was to generate 6 random numbers from 1 to 60 in ascending order, without repetition. 
# This way, when mom asks me for lucky numbers for her to play, this is what I give her. 

import random

lottery = []

while len (lottery)<6:
    number = random.randint(1,60)
    if number not in lottery:
        lottery.append(number)


lottery.sort()

for n in lottery:
    print (n)
