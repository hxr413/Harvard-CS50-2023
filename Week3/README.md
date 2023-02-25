### [Lab 3: Sort](https://cs50.harvard.edu/x/2023/labs/3/)

### My Assignment Work
`answers.txt`
> [check50](https://submit.cs50.io/check50/0eafc2bdafbbf1f27f8e6b304d742d1e8ffc60ab): 3/3     

|  | sorted5000 | sorted10000 | sorted50000 | reversed5000 | reversed10000 | reversed50000 | random5000 | random10000 | random50000 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| sort1 | 0.033s | 0.068s | 0.458s | 0.069s | 0.259s | 5.408s | 0.083s | 0.318s | 7.186s |
| sort2 | 0.024s | 0.061s | 0.497s | 0.025s | 0.053s | 0.378s | 0.029s | 0.076s | 0.327s |
| sort3 | 0.067s | 0.188s | 2.969s | 0.059s | 0.166s | 2.950s | 0.066s | 0.183s | 2.936s |


### [Problem Set 3 Description](https://cs50.harvard.edu/x/2023/psets/3/)

### My Assignment Work
`plurality.c`  
> [check50](https://submit.cs50.io/check50/199f0393f0c24071933707b0872946f0b87fd8c6): 14/14   
> style50: 1.00  
- Referred to [this document](https://github.com/mancuoj/CS50x/blob/master/Week3/1-plurality.c) for the idea of finding out the maximum votes first, then find the corresponding candidates with the maximum votes, i.e. the winner. A similar approach can be found [here](https://github.com/lng205/CS50x2022/blob/master/Week3/plurality/plurality.c).  

`runoff.c`: **For those who are *less* comfortable with computer science**  
> [check50](https://submit.cs50.io/check50/1b2f78796a678947a22d4f92967ad0e37ccc7f6e): 25/25   
> style50: 1.00  
- Basically made it on my first attempt (despite some small grammar mistakes). No major mistakes/misunderstandings in the thinking process and going through the whole coding process smoothly - feel like I'm getting more familiar with programming now, whether it's writing code or thinking like a programmer.
- It's interesting to see how others deal with the `bool is_tie` function. I had a look at [this document](https://github.com/mancuoj/CS50x/blob/master/Week3/2-runoff.c) (after finishing my own work) and it's pretty neat. 

`tideman.c`: **For those who are *more* comfortable with computer science**  
> [check50](https://submit.cs50.io/check50/af6ee462cb2c41149b37a9f4f1102228427e1896): 18/18   
> style50: 1.00  
- For the `sort_pairs` function, I referred to [this code of selection sort](https://www.geeksforgeeks.org/selection-sort/).
- For the `lock_pairs` function, I figured out that I should use recursion, and know that I need to track if there is a path going from "start: winner 1" (to loser 1 = winner 2, then to loser 2 = winner 3, ..., to loser n-1 = winner n) to "end: loser n = winner 1" and hence forming a cycle. I tried to build everything from a base case, but still I am not sure how to implement that in code exactly, so I had a look at [this document](https://github.com/mancuoj/CS50x/blob/master/Week3/2-tideman.c) and [this document](https://github.com/lng205/CS50x2022/blob/master/Week3/tideman/tideman.c) for inspiration.
- I think it's kind of clever for the finding-cycle algorithm to make the loser in a pair as the "start" of the cycle, and the winner in the pair at the "end". As the winner and the loser is in the same pair, they are "bounded together", which kind of ensures the arrow pointing from winner to loser and hence the cycle, when there is a path evetually pointing at the winner. While I initially took the winner in the pair as the start (as explained above), which is not that neat. 
- For the `print_winner` function, notice that simply write `if (!locked[j][i]) printf("%s\n", candidates[i]);` will not work. It should work like this: `j` goes through all the cases from 0 to `candidate_count-1`, making sure that no arrow points at `i`. If finds an arrow, break the `j` loop; if not, when it reaches the end of the loop and/or breaks the loop, declare that `i` is the winner. Then the `j` loop starts again for `i++`(i=i+1).
- This one is indeed much more difficult, in the sense that it requires more brainwork to get my head around. But after thinking things through and figuring them out, it is actually not complicated.
