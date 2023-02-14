### [Lab 1: Population Growth](https://cs50.harvard.edu/x/2023/labs/1/)

### My Assignment Work
`population.c`: The standard answer  
`population2.c`: A failed attempt trying to use a `for` loop 
- It was my first instinct to use a `for` loop, so I tried to make it work after finishing `population.c`. Well, it seems like a `for` loop turned out not to be the best solution.    

### [Problem Set 1 Description](https://cs50.harvard.edu/x/2023/psets/1/)

### My Assignment Work
`hello.c`  
`mario_less.c`: **For those who are *less* comfortable with computer science**
- When input is not an integer, line 10 doesn't print, since the boolean expression in line 13 only considers the situation when input is a wrong integer. Tried to add more conditions to take more datatypes into account but failed - my current knowledge (Feb 13th, 2023) is probably not sufficient to solve this.   

`mario_more.c`: **For those who are *more* comfortable with computer science**
- Can be easily done once worked out `mario_less.c` - just added a new line of printing two spaces and then copied one of the `for` loops.   

`cash.c`: **For those who are *less* comfortable with computer science**  
`credit.c`: **For those who are *more* comfortable with computer science**
- Referred to [this document](https://github.com/lng205/CS50x2022/blob/master/Week1/credit/credit.c) when writing my code, which also provides a neat solution using the conditional `switch`. I found the programming ideas in this document insightful and enlightening - many thanks.
- My initial thought was to follow the instructions given about Luhn's Algorithm (i.e. start with the last digit and work back through the whole card number, multiply every other digit by 2 and calculate the sum, calculate the sum of the digits that weren’t multiplied by 2, then add the sum together and finally use the modulus operator...) and creat my own function to realise the algorithm using something like `cardnumber % pow(10,n)`, where n represents the nth digit. However, it turns out to be easier doing the addtion while going through the string of card number. 
- My initial thought also raised problems for the second phase of the programme - validation, since it separates the numbers in even digits and numbers in odd digits (while separation itself is tricky as well), and doesn't keep track of the number of digits and the first two digits. 
- My takeaway is that when using a loop, try to do everything along with the loop and get the all the values needed when the loop ends. Avoid going back as that will probably make things unnecessarily more complicated. 
