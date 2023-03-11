### [Lab 7: Songs](https://cs50.harvard.edu/x/2023/labs/7/)
`songs.sql` and `answers.txt`
> [check50](https://submit.cs50.io/check50/f36bfeb6470eea197f2154f1c0d6feebb2d9d194): 11/11  

### [Problem Set 7 Description](https://cs50.harvard.edu/x/2023/psets/7/)
`movies.sql`
> [check50](https://submit.cs50.io/check50/dab39e2489abae8dde8e6185f3a4cf0b05308af5): 14/14  
- Pretty straight forward until `11.sql`. I wasn't aware of `IN` and had been using `=` all the time, but `4.sql` helped me fix that. 
- Since `11.sql` I start to pay attention to styles and write two columns after `FROM`, use techniques like `FROM movies, ratings WHERE ratings.movie_id = movies.id`, which I learned from CS50 Discord server. 
- In `12.sql` I learned about `INTERSECT`, but I still wonder if there are ways to make the code shorter and reduce the repeated part. Similarly for `13.sql`, I learned about `EXCEPT`, but it seems like I can only write `EXCEPT SELECT name FROM people WHERE name = 'Kevin Bacon'`, which is kind of long, as `EXCEPT 'Kevin Bacon'` will lead to syntax error.  

 `log.sql`,  `log2.sql` and `answers.txt`  
> [check50](https://submit.cs50.io/check50/3e3763961a26ce7a08e49271a6ea30b48d0dd1cf): 3/3 
- This one is really chill and fun - best problem set quesion so far!
- `log.sql` is my original log, and 'log2.sql' is inspired by [this post](https://www.reddit.com/r/cs50/comments/llxhvl/fiftyville_greatest_problem_set_ever/) and @CashAccomplished7309's code. I tried to shorten and merge my queries as @CashAccomplished7309 did. 
- One thing I learned from @CashAccomplished7309's code is that I can do `SELECT name FROM people WHERE people.license_plate IN ( SELECT license_plate FROM bakery_security_logs WHERE ...)` as I thought I must do something like `SELECT name FROM people, bakery_security_logs WHERE people.license_plate = bakery_security_logs.license_plate AND people.license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE ...)`.
- Another thing is that I learned about using `JOIN` in cases like `... AND people.id IN (SELECT person_id FROM bank_accounts JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number WHERE ...)` rather than using the same old syntax of `SELECT name from people, bank_accounts, atm_transactions WHERE people.id = bank_accounts.person_id AND bank_accounts.account_number = atm_transactions.account_number AND atm_transactions.account_number IN (SELECT account_number FROM atm_transactions ...)`
