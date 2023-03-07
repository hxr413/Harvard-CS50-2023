# ignore any leading whitespace in the user’s greeting, and treat the user’s greeting case-insensitively
greeting = input('Gretting: ').strip().lower()

# starts with “hello”, output $0
if greeting.startswith('hello'):
    print('$0')
# starts with an “h” (but not “hello”), output $20
elif greeting[0] == 'h':
    print('$20')
# otherwise, output $100
else:
    print('$100')