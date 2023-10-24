-- Keep a log of any SQL queries you execute as you solve the mystery.
- Keep a log of any SQL queries you execute as you solve the mystery.
    -- Descobrir: i) Quem é o ladrão?; ii) Por onde o ladrão escapou (para onde foi)?; iii) Quem é o cumplice do ladrão?.

-- Selecionar todos os registros de crime com data de 28/07 e que ocorrem em Chamberlin Street
SELECT description FROM crime_scene_reports WHERE day = "28" AND month = "7" AND street = "Chamberlin Street";

-- O pato estava às 10h15 na Chamberlin Street Courthouse. Verificar as entrevistas de quem passou pela courthouse.
SELECT transcript FROM interviews WHERE day = "28" AND "month" = "7" AND transcript LIKE "%courthouse%";

-- Verificar os registros de segurança de Courthouse para encontrar placas de carro que estiveram no local em um espaço de 10 minutos e em seguida cruzar a placa do carro com os nomes das pessoas.
SELECT name FROM people JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate WHERE day = "28" AND month = "7" AND year = "2020" AND hour = "10" AND minute >= "15" AND minute < "25" AND activity = "exit";

-- Com base na segunda entrevista, verificando nomes de pessoas que sacaram dinheiro da ATM na Fifer Street no dia do roubo.
SELECT DISTINCT name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number WHERE day = "28" AND month = "7" AND year = "2020" AND transaction_type = "withdraw" AND atm_location = "Fifer Street";

-- Com base na terceira entrevista, verificando nomes de pessoas que compraram passagem de voo para o dia depois do roubo.
SELECT name FROM people JOIN passengers ON people.passport_number = passengers.passport_number WHERE flight_id = (SELECT id FROM flights WHERE day = "29" AND month = "7" AND year = "2020" ORDER BY hour,minute LIMIT 1);

-- Com base na terceira entrevista, verificando nomes de pessoas que fizeram ligação de menos de um minuto no dia do roubo.
SELECT name FROM people JOIN phone_calls ON people.phone_number = phone_calls.caller WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60";

-- Validando todas as condições para encontrar o ladrão.
SELECT name FROM people JOIN passengers ON people.passport_number = passengers.passport_number WHERE flight_id = (SELECT id FROM flights WHERE day = "29" AND month = "7" AND year = "2020" ORDER By hour, minute LIMIT 1) INTERSECT SELECT DISTINCT name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number WHERE day = "28" AND month = "7" AND year = "2020" AND transaction_type = "withdraw" AND atm_location = "Fifer Street" INTERSECT SELECT name FROM people JOIN phone_calls ON people.phone_number = phone_calls.caller WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60" INTERSECT SELECT name FROM people JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate WHERE day = "28" AND month = "7" AND year = "2020" AND hour = "10" AND minute >= "15" AND minute < "25" AND activity = "exit";

-- Encontrando o destino do voo comprado por Ernest, para o dia depois do roubo.
SELECT city FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE day = "29" AND month = "7" AND year = "2020" ORDER BY hour,minute LIMIT 1);

-- Descobrindo quem é o cumplice (pessoa para quem Ernest ligou por menos de 1 minuto no dia do roubo).
SELECT name FROM people JOIN phone_calls ON people.phone_number = phone_calls.receiver WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60" AND caller = (SELECT phone_number FROM people WHERE name = "Ernest");

-- Resolução: i) Ernest é ladrão; ii) Fugiu para London e iii) Berthold foi seu cumplice.