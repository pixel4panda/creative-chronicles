def get_int(text):
    while True:
        # kickstarts the function with user prompt
        print(f"{text}", end="")

        # tries to obtain an integer
        try:
            return int(input())
        # in case of error prints the explanation and returns to the start
        except ValueError:
            print ("Error: please input integer")
            pass
