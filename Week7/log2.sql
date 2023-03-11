-- Find the thief

SELECT name FROM people
-- evidence from bakery parking lot security footage
WHERE people.license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = 'exit'
)
-- evidence from ATM transactions on Leggett Street
AND people.id IN (
    SELECT person_id FROM bank_accounts
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
    WHERE atm_transactions.year = 2021 AND atm_transactions.month = 7 AND atm_transactions.day = 28
    AND atm_transactions.transaction_type = 'withdraw' AND atm_transactions.atm_location = 'Leggett Street'
)
-- evidence from phone calls
AND people.phone_number IN (
    SELECT caller FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60
)
-- intersection with tomorrow's first flight passenger list
AND people.passport_number IN (
    SELECT passport_number FROM passengers
    WHERE flight_id = (
        SELECT id FROM flights
        WHERE origin_airport_id = (
            SELECT id FROM airports WHERE city = 'Fiftyville'
            )
        AND year = 2021 AND month = 7 AND day = 29
        ORDER BY hour LIMIT 1
    )
);
-- result:
-- +-------+
-- | name  |
-- +-------+
-- | Bruce |
-- +-------+

-- Find the destination city by locating tomorrow's first flight
SELECT city FROM airports WHERE id = (
    SELECT destination_airport_id FROM flights
    WHERE year = 2021 AND month = 7 AND day = 29
    ORDER BY hour LIMIT 1
);
-- result:
-- +---------------+
-- |     city      |
-- +---------------+
-- | New York City |
-- +---------------+

-- Find the accomplice through the phone call
SELECT name FROM people
WHERE people.phone_number = (
    SELECT receiver FROM phone_calls
    WHERE caller = (
        SELECT phone_number FROM people
        WHERE name = 'Bruce'
    )
    AND year = 2021 AND month = 7 AND day = 28 AND duration <= 60
);
-- result:
-- +-------+
-- | name  |
-- +-------+
-- | Robin |
-- +-------+
