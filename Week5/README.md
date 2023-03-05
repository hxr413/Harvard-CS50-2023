### [Lab 5: Inheritance](https://cs50.harvard.edu/x/2023/labs/5/)
`inheritance.c`
> [check50](https://submit.cs50.io/check50/f0ee35ba13d9f78c1b2ad93aa1999abdfc749300): 7/7  
> style50: 1.00  
- A bit confused about when to add `*` in my code and when not - most of the time just rely on the error message from 'make' to debug...But in general not hard.
- For the `TODO: Randomly assign current person's alleles based on the alleles of their parents`, the hint video gives a solution without writing an extra function. I added that method in my code file as notes. 

### [Problem Set 5 Description](https://cs50.harvard.edu/x/2023/psets/5/)
`dictionary.c`: This one passes `check50` and `valgrind`  
`dictionary2.c`: This one passes `check50` but has memory leaks  
> [check50](https://submit.cs50.io/check50/f7dbacfca6ca32141d5cc0d318314b2ac12a801a): 9/9  
> style50: 1.00  
- Not that difficult/complicated. In general things went through relatively smoothly, which is good for this final problem set in C - a happy ending!

| File | xueqin1.txt | xueqin2.txt | shakespeare.txt | 
| --- | --- | --- | --- | 
| Words Misspelled | 11089 | 17725 | 71776 | 
| Words in Dictionary | 143091 | 143091 | 143091 | 
| Words in Text | 189138 | 265867 | 904612 | 
| Time in `load` | 0.02 | 0.02 | 0.03 | 
| Time in `check` | 0.66 | 0.93 | 3.13 | 
| Time in `size` | 0.00 | 0.00 | 0.00 | 
| Time in `unload` | 0.00 | 0.00 | 0.00 | 
| Time in Total | 0.69 | 0.95 | 3.16 |

- I'm pretty happy with the performance of my hash function as well.
