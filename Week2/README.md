### [Lab 2: Scrabble](https://cs50.harvard.edu/x/2023/labs/2/)

### My Assignment Work
`scrabble.c`
> [check50](https://submit.cs50.io/check50/b66754ae039c3659590f4266c8688baa672a8bf7): 11/11   
> style50: 1.00  
- Not sure why `POINTS[(word[i]) - 'A']` works. Obviously `POINTS[(word[i]) - 65]` works as well, though it seems to make sense to me, I don't think I 100% understand why `'A'` is treated as 65. Maybe it has something to do with the `''` syntax? 
- Also I'm not sure why `word[i]` is treated as a number, maybe because it's in a `POINT[]`? So both `word[i]` and `'A'` are treated as numbers. 


### [Problem Set 2 Description](https://cs50.harvard.edu/x/2023/psets/2/)

### My Assignment Work
`readability.c`  
> [check50](https://submit.cs50.io/check50/e32286764c50e4d3ffbee25f2784283a7265070e): 11/11   
> style50: 1.00  
- Pretty much just repeating what's done in `scrabble.c`, but building the entire programme from scratch. Quite fulfilling that I wrote and debugged (using `printf`) everything myself, without looking at any other people's code. 
- A side note: for the `int count_letter(string t)` function, `isalnum` and `isalpha` also work fine as this question doesn't take too many practical details into account. 

`bulbs.c`: **For those who are *less* comfortable with computer science**
> [check50](https://submit.cs50.io/check50/2112743f0bac72755268395a2068a60772283c7e): 10/10   
> style50: 1.00  
- [This video](https://www.youtube.com/watch?v=w72ckSTpoq4) provides the crucial hint of setting up an `int binary[]` array, which was essential in turning ASCII numbers into binary code - many thanks.  

`caesar.c`: **For those who are *less* comfortable with computer science**  
`caesar2.c`: My first attempt, which works fine but misses the specification of using a `char rotate(char c, int n)` function. So I modified this to `caesar.c`.  
> [check50](https://submit.cs50.io/check50/306f69dbe8f5ab40bc01e375d4c0bdf48a6eaed0): 11/11   
> style50: 1.00  

`substitution.c`: **For those who are *more* comfortable with computer science**
> [check50](https://submit.cs50.io/check50/8c753b183aba0832ebd5ad2d121d1f8df254bb2d): 18/18   
> style50: 1.00  
- Can be done relatively easily by modifying `caesar.c`'s code.

`wordle50`: **For those who are *more* comfortable with computer science**
> [check50](https://submit.cs50.io/check50/954539b3afd7306ad6ad947f72feb36fb0297e6a): 13/13   
> style50: 1.00  
- Not difficult as long as following the instructions. I think this one is pretty fun, and can feel that I'm getting a bit more proficient - hoorah!
- Tried to use a `switch` condition, had a bug initially but managed to fix it - fulfilling learning!
