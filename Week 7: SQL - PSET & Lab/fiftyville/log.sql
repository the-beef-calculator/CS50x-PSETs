-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Crime info: Took place on July 28, 2021 on Humphrey Street.
-- 1st Query: .schema:
-- Done to get an idea of what i'm working with.


-- 2nd Query: SELECT description FROM crime_scene_reports WHERE street = "Humphrey Street" AND day = 28 AND month = 7 AND year = 2021;

-- Query for  crime report for when the crime took place. Report says: "Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
-- Littering took place at 16:36. No known witnesses.

-- Key takeaways: Crime took place at 10:15AM. Three witnesses were interviewed. All of them mention the bakery.

-- 3rd Query: SELECT activity FROM bakery_security_logs WHERE month = 7 AND year = 2021 AND day = 28;

-- Finding out what activity the store tracks. Seems activity tracks entrances and exits. 
