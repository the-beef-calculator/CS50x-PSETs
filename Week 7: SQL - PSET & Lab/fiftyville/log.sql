-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Crime info: Took place on July 28, 2021 on Humphrey Street.

-- 1st Query: .schema:
-- Done to get an idea of what i'm working with.


-- 2nd Query: SELECT description FROM crime_scene_reports WHERE street = "Humphrey Street" AND day = 28 AND month = 7 AND year = 2021;
-- Query for  crime report for when the crime took place.
-- Report says: "Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
-- Littering took place at 16:36. No known witnesses.
-- Key takeaways: Crime took place at 10:15AM. Three witnesses were interviewed. All of them mention the bakery.


-- 3rd Query: SELECT activity FROM bakery_security_logs WHERE month = 7 AND year = 2021 AND day = 28;
-- Finding out what activity the store tracks.
-- Key takeaways: "activity" refers to the number of exits and entrances.


-- 4th Query: SELECT activity FROM bakery_security_logs WHERE month = 7 AND year = 2021 AND day = 28 AND hour = 10 AND minute >= 10 <= 20;
-- Finding out the entrances and exits between 10:10 and 10:20. *Reminder: CS50 Duck was taken at 10:15.*
-- Key takeaways: 2 entrances, 9 exits, then 3 more entances. (Considering tracing all activity from open to 10:20?)
-- Considering another query that displays the time for each entrance and exit.


-- 5th Query: SELECT hour,minute,activity FROM bakery_security_logs WHERE month = 7 AND year = 2021 AND day = 28 AND hour = 10 AND minute <= 20;
-- Pulled time records.
-- Key Takeaways: There was an entrance one minute before the theft, and an exit one minute after. I don't think anything else can be learned from here.


-- 6th Query: SELECT transcript,month,day,year FROM interviews WHERE month = 7 AND day = 28 AND year = 2021 AND transcript LIKE "%bakery%";
-- Read the interviews with the three witnesses.
-- Key takeaways: The thief withdrew money from an ATM before the theft, Entered the bakery and stole the duck, made a call that lasted < 60 secs,
--                detailing the person on the other end to buy the earliest flight out of town, then exited the bakery, got in his car and drove off within 10 minutes of the theft.
--                License plate captured on camera.

-- 7th Query: SELECT license_plate,month,day,hour,minute FROM bakery_security_logs WHERE month = 7 AND day = 28 AND year = 2021 AND hour = 10;
-- Gathering a list of all the license plates.
-- Key takeaways: 8 possible suspects. Plate #'s are: 5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7JE, 0NTHK55.

-- 8th Query: SELECT name,license_plate FROM people WHERE license_plate IN ({the license plates});
-- Cross referencing the plate numbers with the people table.
-- Key takeaways: {Vanesa,5P2BI95}, {Barry, 94KLI3X}, {Iman, L93JTIZ}, {Sofia, G412CB7}, {Luca, 4328GD8}, {Diana, 322W7J2}, {Kelsey, 0NTHK55}, {Bruce, 94KL13X}

-- 9th Query: SELECT caller,receiver,duration,month,day,year FROM phone_calls WHERE month = 7, AND day = 28, AND year = 2021 AND duration < 60;
-- Pulling the call logs. Recieved a table of numbers when I thought there'd be names. Great.

-- 10th Query: SELECT * FROM people WHERE name IN ("Vanessa",Barry","Iman,"Sofia","Luca","Diana","Kelsey","Bruce");
-- Retrieving ALL info on suspects. Probably should have done this the first time around but... oh well. Relevant info though!
-- Key takeaways: list narrowed down to four suspects! Gonna confirm with next query...

--11th Query: SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND year = 2021 AND duration < 60 AND caller IN("(725) 555-4692","(301) 555-4174","(829) 555-5269","(130) 555-0289","(389) 555-5198","(770) 555-1861","(499) 555-9472","(367) 555-5533");
-- Seeing who made a call that day following the parameters.
--key takeaways: List of suspects narrowed down to: Sofia,Diana,Kelsey,Bruce.

--12th Query: SELECT * FROM bank_accounts JOIN people ON bank_accounts.person_id = people.id WHERE name IN("Sofia","Diana","Kelsey","Bruce");
-- Retrieving bank account info for our new narrowed list of suspects. If my queries were correct, it seems only two people have active bank accounts.
--Key takeaways: Bruce and Diana are the only people with active bank accounts in Fiftyville.

-- +----------------+-----------+---------------+--------+-------+----------------+-----------------+---------------+
--| account_number | person_id | creation_year |   id   | name  |  phone_number  | passport_number | license_plate |
--+----------------+-----------+---------------+--------+-------+----------------+-----------------+---------------+
--| 49610011       | 686048    | 2010          | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
--| 26013199       | 514354    | 2012          | 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
--+----------------+-----------+---------------+--------+-------+----------------+-----------------+---------------+

--13th Query: SELECT * FROM atm_transactions WHERE account_number IN(49610011,26013199) AND month = 7 AND day = 28 AND year = 2021;
-- Retrieving transaction details.
-- key takeaways: Both suspects withdrew money from the atm on leggett street.
--+-----+----------------+------+-------+-----+----------------+------------------+--------+
--| id  | account_number          | year | month | day |  atm_location  | transaction_type | amount |
--+-----+----------------+------+-------+-----+----------------+------------------+--------+
--| 267 | 49610011 {bruce}       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
--| 336 | 26013199 {diana}      | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     |
--+-----+----------------+------+-------+-----+----------------+------------------+--------+

--14th Query: SELECT * FROM people WHERE name IN("Bruce","Diana");
-- retrieving all info for two suspects
--+--------+-------+----------------+-----------------+---------------+
--|   id   | name  |  phone_number  | passport_number | license_plate |
--+--------+-------+----------------+-----------------+---------------+
--| 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
--| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
--+--------+-------+----------------+-----------------+---------------+

--15th Query: SELECT caller,receiver FROM phone_calls WHERE caller IN("(770) 555-1861","(367) 555-5533") AND duration < 60 AND month = 7 AND day = 28 AND year = 2021;
-- Figuring out who they talked to.

--+----------------+----------------+
--|     caller     |    receiver    |
--+----------------+----------------+
--| (367) 555-5533 | (375) 555-8161 |
--| (770) 555-1861 | (725) 555-3243 |
--+----------------+----------------+

--16th Query:  SELECT * FROM  people WHERE phone_number IN ("(375) 555-8161","(725) 555-3243");
-- Call receiver names and info.
--Key takeaway: Diana called Philip, Bruce called Robin.
--+--------+--------+----------------+-----------------+---------------+
--|   id   |  name  |  phone_number  | passport_number | license_plate |
--+--------+--------+----------------+-----------------+---------------+
--| 847116 | Philip | (725) 555-3243 | 3391710505      | GW362R6       |
--| 864400 | Robin  | (375) 555-8161 | NULL            | 4V16VO0       |
--+--------+--------+----------------+-----------------+---------------+



