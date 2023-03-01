### [Lab 4](https://cs50.harvard.edu/x/2023/labs/4/)
`helpers_smiley.c`
> [check50](https://submit.cs50.io/check50/b26414ef44973577506dc647ed8bc85444ed6971): 4/4  
> style50: 1.00  

`volume.c`:
> [check50](https://submit.cs50.io/check50/146813b9484992fbc2a58564ebf80449d4a2ab04): 5/5  
> style50: 1.00  

### [Problem Set 4 Description](https://cs50.harvard.edu/x/2023/psets/4/)
`helpers_filter_less.c`: **For those who are *less* comfortable with computer science**    
> [check50](https://submit.cs50.io/check50/9f177e06ad0f42fa809062c9f9ce1759b09b4c2e): 22/22   
> style50: 1.00  
- The `blur` function is pretty painful. I initially wrote very long code with lots of unnecessary variables etc., so first of all there were lots of grammar/syntax mistakes. After deleting all the unnecessary bits and tidying things up, my code still didn't work. It was not convenient to use `debug50` so I basically just stared at my code and tried to modify anything that I can think of and might go wrong...Till now I am still not sure what went wrong exactly but only have guesses based on `check50`, as once it gave some positive feedback, I knew I got something right. I probably spent 4+ hrs on this and 3/4 of the time on `blur`. Fortunately it worked out eventually... and I'm burned out...
- One thing I'm proud of is that I insisted my own thinking (in terms of which functions to use and how they can work to get the desired results) throughout the coding process, and I kind of developed all the improvements and modifications myself. That's probably also part of the debugging... 
- Referred to [this document](https://github.com/mancuoj/CS50x/blob/master/Week4/1-filter-less.c) and [this video](https://www.youtube.com/watch?v=eoHIX_PNGcE) during my exhausting debugging. Also learned about the use of `continue`. Many thanks. 

`helpers_filter_more.c`: **For those who are *more* comfortable with computer science**    
> [check50](https://submit.cs50.io/check50/c019d97f08a14431cc67cd7167a053ed7f785e09): 23/23   
> style50: 1.00  
- The `edge` function can be solved use the same idea applied in `blur`. 
- My initial plan is to make three functions called `border_pixel`, `gx_compute` and `gy_compute`. `border_pixel` will examine the 3x3 pixel square with the input pixel being the centre, and return a 2D array `RGBTRIPLE border[3][3]`, where each element of the array is a `RGBTRIPLE`, and those invalid pixels will just have values `.rgbtRed/Green/Blue=0`.
- Then `gx_compute` and `gy_compute` will take this 2D array as input, multiple it and the Sobel matrix together to compute the `gx/gy` value for the input pixel. And they will return a `RGBTRIPLE gx/gy`, with `.rgbtRed/Green/Blue` being the newly computed values.
- However, it seems like in C, I cannot have a function returning a 2D array for me. So I merged `border_pixel` into `gx/gy_compute`, while `gx/gy_compute` can still return a `RGBTRIPLE gx/gy`. Nevertheless, it still won't work, for the reason demonstrated in `helpers_filter_more.c`: `.rgbtRed/Green/Blue` are `BYTE`s, so they won't be able to take gx/gy RGB values, as these would be greater than the maximum 255.
- It turns out that considering my current knowledge level, it's probably better not to abstract functions outside the main `edge` function (which is different from the case in `blur`).

`recover.c`    
> [check50](https://submit.cs50.io/check50/25a0d341db5fbd287ce149e403c436a7cf96c277): 7/7   
> style50: 1.00  
- This one made me struggle as well...Fortunately it's less painful than `filter`. I was not that familiar (or say comfortable) with the file pointers, so initially it took a bit more time to think through. 
- For the major problem I encoutered, I made more detailed notes explaining it in the file.
