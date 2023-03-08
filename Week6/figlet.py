import sys
from pyfiglet import Figlet

figlet = Figlet()
font_names = figlet.getFonts()

# Expects 0 or 2 command-line arguments
if len(sys.argv) != 1 and len(sys.argv) != 3:
    sys.exit('Invalid usage')
elif len(sys.argv) == 3:
    # the 1st should be -f or --font
    if sys.argv[1] != "-f" and sys.argv[1] != "--font":
        sys.exit('Invalid usage')
    # the 2nd should be the name of the font
    if sys.argv[2] not in font_names:
        sys.exit('Invalid usage')

# Prompts the user for a str of text
text = input('Input: ')

# 0 if the user would like to output text in a random font
if len(sys.argv) == 1:
    font_name = random.choice(font_names)
# 2 if the user would like to output text in a specific font
if len(sys.argv) == 3:
    font_name = sys.argv[2]

# output text in random or the desired font
figlet.setFont(font=font_name)
print(figlet.renderText(text))


