### [Lab 7: Songs](https://cs50.harvard.edu/x/2023/labs/7/)
`songs.sql` and `answers.txt`
> [check50](https://submit.cs50.io/check50/f36bfeb6470eea197f2154f1c0d6feebb2d9d194): 11/11  

### [Problem Set 7 Description](https://cs50.harvard.edu/x/2023/psets/7/)
`movies.sql`
> [check50](https://submit.cs50.io/check50/dab39e2489abae8dde8e6185f3a4cf0b05308af5): 14/14  
- Pretty straight forward until `11.sql`. I wasn't aware of `IN` and had been using `=` all the time, but `4.sql` helped me fix that. 
- Since `11.sql` I start to pay attention to styles and write two columns after `FROM`, use techniques like `FROM movies, ratings WHERE ratings.movie_id = movies.id`, which I learned from CS50 Discord server. 
- In `12.sql` I learned about `INTERSECT`, but I still wonder if there are ways to make the code shorter and reduce the repeated part. Similarly for `13.sql`, I learned about `EXCEPT`, but it seems like I can only write `EXCEPT SELECT name FROM people WHERE name = 'Kevin Bacon'`, which is kind of long, as `EXCEPT 'Kevin Bacon'` will lead to syntax error. 
