#Writing a function that converts Hexadecimal numbers into decimal numbers. Kind of wanted to know how the int(hexNum, 16) function behaves. I actually might expand this later to other bases. 

hexNumbers = {
    '0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9,
    'A': 10, 'B': 11, 'C': 12, 'D': 13, 'E': 14, 'F': 15
}

def hexToDec(hexNum):

    #user does not input a valid text
    #where types of invalid text are length ==0 or letters not in dictionary

    if len(hexNum) == 0: 
        return None
    for char in hexNum:
        if char not in hexNumbers:
            return None
        

    # user inputs a valid text 'ABC'
    # I separate A, B and C, find their dict values, and multiply by 16**2 16**1 and 16 ** 0
    # A * 16 ** (len(hexNum)-1) + B * 16 ** (len(hexNum)-2)...

    posit = 0
    answer = 0
    exp = len(hexNum) - 1
    for value in range (len(hexNum)):
        posit = value
        answer = answer + (hexNumbers[hexNum[posit]]*(16**exp))
        exp = exp-1

    return answer

        

user_hex = input ('Please input the hexadecimal: ')
print (hexToDec(user_hex))
