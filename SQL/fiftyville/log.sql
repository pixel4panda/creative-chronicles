-- Step 01: read the crime report that happened on July 28, 2024
SELECT * FROM crime_scene_reports
 WHERE year = 2024
   AND month = 7
   AND day = 28
   AND street = 'Humphrey Street';

        -- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
        -- Interviews were conducted today with three witnesses who were present at the time
        -- – each of their interview transcripts mentions the bakery.

-- Step 02: read the interviews from the 3 witnesses and get their names
SELECT name, transcript FROM interviews
 WHERE year = 2024
   AND month = 7
   AND day = 28
   AND transcript LIKE '%bakery%';

        -- Ruth : Sometime within ten minutes of the theft, I saw the thief get into a car in the
        -- bakery parking lot and drive away. If you have security footage from the bakery parking
        -- lot, you might want to look for cars that left the parking lot in that time frame.
        -- Eugene : I don't know the thief's name, but it was someone I recognized. Earlier this
        -- morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street
        -- and saw the thief there withdrawing some money.
        -- Raymond : As the thief was leaving the bakery, they called someone who talked to them
        -- for less than a minute. In the call, I heard the thief say that they were planning to
        -- take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on
        -- the other end of the phone to purchase the flight ticket.

-- Step 03: (follow Ruth's lead) Look at security footage from the bakery parking lot
-- Obtain possible names for the thief
SELECT people.name AS unsub01a FROM people
 WHERE license_plate IN
        -- Obtain license plate from cars
       (SELECT license_plate FROM bakery_security_logs
         WHERE year = 2024
           AND month = 7
           AND day = 28
           -- Within 10 minutes of 10:15am
           AND hour = 10
           AND minute BETWEEN 15 AND 25
           AND activity = 'exit')
ORDER BY unsub01a;

-- Step 04: (follow Eugene's lead) Look at atm transactions at Leggett Street
-- Obtain name from people
SELECT DISTINCT people.name AS unsub01b FROM people
    JOIN bank_accounts ON people.id = bank_accounts.person_id
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
 WHERE atm_transactions.account_number IN
-- Withdrawing transactions
    (SELECT account_number FROM atm_transactions
     WHERE year = 2024
       AND month = 7
       AND day = 28
       -- at Leggett Street
       AND atm_location = 'Leggett Street'
       AND transaction_type = 'withdraw')
ORDER BY unsub01b;

-- Step 05: (follow Raymond's lead) Look at phone calls
-- Obtain name from people
SELECT people.name AS unsub01c FROM people
    JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE year = 2024
  AND month = 7
  AND day = 28
  -- Where the duration is ledd than 60s
  AND duration < 60
ORDER BY unsub01c;

-- Step 06: (follow Raymond's lead) Earliest flight out of fiftyville tomorrow
SELECT people.name AS unsub01d FROM people
    JOIN passengers ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id =
-- Obtain ID of earliest flight out of Fiftyville
  (SELECT flights.id FROM flights
      JOIN airports ON airports.id = flights.origin_airport_id
  WHERE airports.city = 'Fiftyville'
    AND flights.year = 2024
    AND flights.month = 7
    AND flights.day = 29
  ORDER BY hour ASC, minute ASC
  LIMIT 1)
ORDER BY unsub01d;

-- Step 07: Intersect all information obtained by using INTERSECT
SELECT people.name AS unsub01a FROM people
 WHERE license_plate IN
       (SELECT license_plate FROM bakery_security_logs
         WHERE year = 2024
           AND month = 7
           AND day = 28
           AND hour = 10
           AND minute BETWEEN 15 AND 25
           AND activity = 'exit')

INTERSECT

SELECT DISTINCT people.name AS unsub01b FROM people
    JOIN bank_accounts ON people.id = bank_accounts.person_id
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
 WHERE atm_transactions.account_number IN
    (SELECT account_number FROM atm_transactions
     WHERE year = 2024
       AND month = 7
       AND day = 28
       AND atm_location = 'Leggett Street'
       AND transaction_type = 'withdraw')

INTERSECT

SELECT people.name AS unsub01c FROM people
    JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE year = 2024
  AND month = 7
  AND day = 28
  AND duration < 60

INTERSECT

SELECT people.name AS unsub01d FROM people
    JOIN passengers ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id =
(SELECT flights.id FROM flights
    JOIN airports ON airports.id = flights.origin_airport_id
WHERE airports.city = 'Fiftyville'
  AND flights.year = 2024
  AND flights.month = 7
  AND flights.day = 29
ORDER BY hour ASC, minute ASC
LIMIT 1);

-- Step 08: Find where Bruce scape to
SELECT city FROM airports
 WHERE id =
(SELECT flights.destination_airport_id FROM flights
    JOIN airports ON airports.id = flights.origin_airport_id
WHERE airports.city = 'Fiftyville'
  AND flights.year = 2024
  AND flights.month = 7
  AND flights.day = 29
ORDER BY hour ASC, minute ASC
LIMIT 1);

-- Step 09: Find the accomplice through the phone call
SELECT people.name AS unsub02 FROM people
    JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE year = 2024
  AND month = 7
  AND day = 28
  AND duration < 60
  AND caller =
  (SELECT phone_number FROM people
    WHERE name = 'Bruce');
