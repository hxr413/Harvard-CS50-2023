-- Keep a log of any SQL queries you execute as you solve the mystery.
-- All you know is that the theft took place on July 28, 2021 and that it took place on Humphrey Street.

-- check crime scence reports
SELECT description FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = 'Humphrey Street';
-- clues:
-- 1. theft took place at 10.15 at the Humphrey Street bakery;
-- 2. interviews were conducted with 3 witnesses (accomplice?);
-- 3. littering took place at 16:36, no known witnesses (irrelevant?)

-- check interview transcripts
SELECT name, transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;
-- clues:
-- Ruth: Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- Eugene: I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- Raymond: As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |

-- check bakery security logs within 10 min of theft
SELECT activity, license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;
-- result: all activity is 'exit'.

-- obtain a list of suspects who exit the bakery parking lot
SELECT name, phone_number, passport_number FROM people, bakery_security_logs
WHERE people.license_plate = bakery_security_logs.license_plate
AND people.license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25
);
-- name    | phone number   | passport
-- Iman    | (829) 555-5269 | 7049073643
-- Bruce   | (367) 555-5533 | 5773159633
-- Diana   | (770) 555-1861 | 3592750733
-- Kelsey  | (499) 555-9472 | 8294398571
-- Luca    | (389) 555-5198 | 8496433585
-- Vanessa | (725) 555-4692 | 2963008352
-- Barry   | (301) 555-4174 | 7526138472
-- Sofia   | (130) 555-0289 | 1695452385

-- check ATM transactions on Leggett Street
SELECT account_number, amount, transaction_type FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE 'Leggett Street';
-- those who withdrew mouney: account number | amount
-- 28500762 | 48
-- 28296815 | 20
-- 76054385 | 60
-- 49610011 | 50
-- 16153065 | 80
-- 25506511 | 20
-- 81061156 | 30
-- 26013199 | 35

-- check who withdrew the money
SELECT name from people, bank_accounts, atm_transactions
WHERE people.id = bank_accounts.person_id
AND bank_accounts.account_number = atm_transactions.account_number
AND atm_transactions.account_number IN (
    SELECT account_number FROM atm_transactions
    WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE 'Leggett Street'
);
-- results: Bruce, Kaelyn, Diana, Brooke, Kenny, Iman, Luca, Taylor, Benista

-- check phone calls
SELECT caller, receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60;
-- caller         | receiver
-- (130) 555-0289 | (996) 555-8899
-- (499) 555-9472 | (892) 555-8872
-- (367) 555-5533 | (375) 555-8161
-- (609) 555-5876 | (389) 555-5198
-- (499) 555-9472 | (717) 555-1342
-- (286) 555-6063 | (676) 555-6554
-- (770) 555-1861 | (725) 555-3243
-- (031) 555-6622 | (910) 555-3251
-- (826) 555-1652 | (066) 555-9701
-- (338) 555-6650 | (704) 555-2131

-- based on the intersection between those who exit the bakery parking lot and made the phone call on phone numbers, suspects are narrowed down to Sofia, Kesley (2 calls), Bruce, Diana
-- based on the result of who withdrew the money, suspects are narrowed down again to Bruce, Diana

-- find Bruce's receiver
SELECT * FROM people, phone_calls
WHERE people.phone_number = phone_calls.receiver
AND phone_calls.receiver IN (
    SELECT receiver FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60 AND caller = '(367) 555-5533'
);
-- Result: Robin

-- find Diana's receiver
SELECT * FROM people, phone_calls
WHERE people.phone_number = phone_calls.receiver
AND phone_calls.receiver IN (
    SELECT receiver FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60 AND caller = '(770) 555-1861'
);
-- Result: Philip

-- find fiftyville's airport
SELECT id FROM airports WHERE city = 'Fiftyville';
-- result: 8

-- check the earliest flights details
SELECT * FROM flights WHERE origin_airport_id = 8 AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour LIMIT 1;
-- results: flight.id = 36, destination_airport_id = 4

-- check the flight's passenger details and intersections with Bruch or Diana on passport numbers
SELECT passport_number FROM passengers WHERE flight_id = 36
INTERSECT
SELECT passport_number FROM people WHERE name = 'Bruce' OR name = 'Diana';
-- result: 5773159633, which is Bruce's passport number, hence the theif is Bruce, accomplice is Robin

-- find the destination city
SELECT city FROM airports WHERE id = 4;
-- result: New York City