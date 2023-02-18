### [Lab 2: Scrabble](https://cs50.harvard.edu/x/2023/labs/2/)

### My Assignment Work
`scrabble.c`
- Not sure why `POINTS[(word[i]) - 'A']` works. Obviously `POINTS[(word[i]) - 65]` works as well, though it seems to make sense to me, I don't think I 100% understand why `'A'` is treated as 65. Maybe it has something to do with the `''` syntax? 
- Also I'm not sure why `word[i]` is treated as a number, maybe because it's in a `POINT[]`? So both `word[i]` and `'A'` are treated as numbers. 


### [Problem Set 2 Description](https://cs50.harvard.edu/x/2023/psets/2/)

### My Assignment Work
`readability.c`  
- Pretty much just repeating what's done in `scrabble.c`, but building the entire programme from scratch. Quite fulfilling that I wrote and debugged (using `printf`) everything myself, without looking at any other people's code. 
- A side note: for the `int count_letter(string t)` function, `isalnum` and `isalpha` also work fine as this question doesn't take too many practical details into account. 

`bulbs.c`: **For those who are *less* comfortable with computer science**
