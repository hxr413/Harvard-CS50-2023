### [Lab 6: World Cup](https://cs50.harvard.edu/x/2023/labs/6/)
`tournament.py` and `answers.txt`
> [check50](https://submit.cs50.io/check50/3f127de42666784ee73c618ba833dcfc62fc7e31): 10/10  
> style50: 1.00  
- I'm completely new to Python, so it's a bit confusing to switch from C syntax to Python syntax. 

### [Problem Set 6 Description](https://cs50.harvard.edu/x/2023/psets/6/)
`hello.py`
> [check50](https://submit.cs50.io/check50/0798a1744e5239de649f5a28c1d968eb07058050): 3/3  
> style50: 1.00  

`mario_less.py`: **For those who are *less* comfortable with computer science**    
> [check50](https://submit.cs50.io/check50/2b2f3f3efd3ee182872f83bb70a19f4a156dd0fb): 9/9  
> style50: 1.00  
- Had a little problem with the requirement "rejects a height of 9, and then accepts a height of 2", but managed to solve it with recursion. I think the application of recursion here is pretty cool, and this makes me get to understand the merits (or say beauty?) about Python a little bit.  

`mario_more.py`: **For those who are *more* comfortable with computer science**    
> [check50](https://submit.cs50.io/check50/1a0d15f5917718f3ed0b754db976a573fe9f4c6c): 9/9  
> style50: 1.00  
- Similar to doing this in C - it's easy based on `mario_less.py`.

`cash.py`: **For those who are *less* comfortable with computer science**    
> [check50](https://submit.cs50.io/check50/7d2f8a2eae2e59c24d43c4c99482779a775ce7cc): 10/10  
> style50: 1.00  
- It seems like using floating point values will suffer from floating point imprecision and lead to incorrect final results, so I took advice from the CS50 Discord server and used integers throughout my calculation.  

`credit.py`: **For those who are *more* comfortable with computer science**    
> [check50](https://submit.cs50.io/check50/37b6df7571c1dd326db7344f907bcadcc88919d4): 14/14  
> style50: 1.00  
- The code is basically the same as `credit.c`. One small improvement is that there is no need to declare `digit2` in advance anymore, since in Python, once it is assigned a value, it can exist everywhere including outside the `while` loop.

`dna.py`  
> [check50](https://submit.cs50.io/check50/fe05e2f305455b01db2a19d3564df329560189db): 21/21  
> style50: 1.00  
- It's not hard to understand how to solve this mentally, but I'm so unfamiliar with Python that I had almost no idea how to put ideas into practice...Thanks to this [video](https://www.youtube.com/watch?v=buYRzIURjnY) which walks through everything, and I've indicateed all its contributions in my code.  
- I don't think the lecture (including Shorts) gives enough introduction to Python syntax and methods and everything to handle this problem - just realised that I didn't watch Section before starting problem sets, maybe that will actually help and that's why I had difficulties... Maybe I'll continue to study CS50P after finishing CS50x, just to learn Python in more depth - it's a pretty cool language. 

### [Week 6 Practice Problems](https://cs50.harvard.edu/x/2023/problems/6/)
- To get more familiar with Python, I did some extra practice problems for this week.

`bank.py`  
> [check50](https://submit.cs50.io/check50/fbdb0bca034b7db74abedb7f977a85598d13f688): 7/7  

`figlet.py`  
> [check50](https://submit.cs50.io/check50/77a1a8081562c6c9af41056d0ed96e310e525351): 7/7  
- Got hung up by a really stupid mistake: in line 12 it should be `and` not `or`, and I wrote `or` unawarely, so didn't notice that for a long while...
- I also spent some time thinking about how to deal with the condition at line 14, specifically how to make use of a `for-in` loop, and suddenly realised that I can actually use `not in`...  

`taqueria.py`  
> [check50](https://submit.cs50.io/check50/705f4b1cf827c35ee6cfe10ef997f641ed814496): 7/7  
- Had a bit of difficulty with how to keep prompting for input after showing `Total: `, but solved that with a `while True` loop. It's in the lecture notes so I'm kind of  aware of it, but was just unsure if this is the right place to use it. 
- I was not sure how the `except EOFError:` bit works and thought I need to add some conditions like `if item == 'control-d':`...I looked for some sample code online and the solves the question.

`jar.py`  
- Not finished. The course material doesn't cover enough content on OOP for this problem, so I don't think I'm capable of completing it unless I spend a lot of extra time and effort learning about this. I tried to search online but there seems to be a big knowlegde gap that I can fill in a short time. The specific knowledge about OOP isn't my focus at this point, as I just want to improve my familiarity with Python syntax, so I decided that it's better to move on.
