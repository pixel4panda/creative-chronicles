# Creates Mario's pyramid (both sides)

def main():
    # Get pyramid height, between 1 and 8
    while True:
        height = get_int("Pyramid height(1 to 8): ")
        # if it is an int, checks to see if it is in valid range
        if height >= 1 and height <= 8:
            break
        else:
            pass

    # Defines pyramid width
    width = (height * 2) + 2

    # Find pyramid middle
    middle1 = width / 2 - 1
    middle2 = width / 2

    # Building the pyramid
    for i in range(height):
        spaces = height - 1 - i
        pyramid_row(width, spaces, middle1, middle2)


def get_int(text):
    # Prompts the user for an int
    while True:
        print(text, end="")
        # tries to turn the user input into an int
        try:
            return int(input())
        except ValueError:
            pass


def pyramid_row(length, spc, mid1, mid2):
    # Prints a single pyramid row
    for i in range(length - spc):
        if i < spc:
            print(" ", end="")
        elif i == mid1 or i == mid2:
            print(" ", end="")
        else:
            print("#", end="")
    print()
    return


if __name__ == "__main__":
    main()
