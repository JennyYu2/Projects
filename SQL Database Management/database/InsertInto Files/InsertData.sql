grant select, delete, update, insert on hamadayaz.Member to public;
grant select, delete, update, insert on hamadayaz.Coupon to public;
grant select, delete, update, insert on hamadayaz.Prize to public;
grant select, delete, update, insert on hamadayaz.PrizeRedemption to public;
grant select, delete, update, insert on hamadayaz.TokenPurchase to public;
grant select, delete, update, insert on hamadayaz.Game to public;
grant select, delete, update, insert on hamadayaz.GamePlay to public;



INSERT INTO hamadayaz.Coupon(CID, MID, description, expirationDate)
VALUES (1, 1, 'Free slice of pizza', TO_DATE('2024-03-23', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.Coupon(CID, MID, description, expirationDate)
VALUES (2, 2, 'Free scoop of ice-Cream', TO_DATE('2025-12-25', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.Coupon(CID, MID, description, expirationDate)
VALUES (3, 3, 'One free beer', TO_DATE('1900-05-03', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.Coupon(CID, MID, description, expirationDate)
VALUES (4, 4, '20 percent off order', TO_DATE('2044-01-04', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.Coupon(CID, MID, description, expirationDate)
VALUES (5, 5, '20 dollar off purchase', TO_DATE('2024-03-23', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.Coupon(CID, MID, description, expirationDate)
VALUES (6, 6, 'Free slice of pizza', TO_DATE('2024-12-31', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.Coupon(CID, MID, description, expirationDate)
VALUES (7, 7, 'One free beer', TO_DATE('2024-03-23', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.Coupon(CID, MID, description, expirationDate)
VALUES (8, 8, 'Free scoop of ice-cream', TO_DATE('1987-11-18', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.Coupon(CID, MID, description, expirationDate)
VALUES (9, 9, '1 dollar any topping pizza', TO_DATE('2022-01-01', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.Coupon(CID, MID, description, expirationDate)
VALUES (10, 10, 'Free slice of pizza', TO_DATE('2024-03-23', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.Coupon(CID, MID, description, expirationDate)
VALUES (11, 11, 'Free slice of pizza', TO_DATE('2024-03-23', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.Coupon(CID, MID, description, expirationDate)
VALUES (12, 12, '50 percent off order', TO_DATE('2019-08-22', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.Coupon(CID, MID, description, expirationDate)
VALUES (13, 13, '20 percent off order', TO_DATE('2024-03-23', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.Coupon(CID, MID, description, expirationDate)
VALUES (14, 14, 'Free scoop of ice-cream', TO_DATE('2018-02-23', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.Coupon(CID, MID, description, expirationDate)
VALUES (15, 15, '20 percent off order', TO_DATE('2099-09-19', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.Coupon(CID, MID, description, expirationDate)
VALUES (16, 16, 'Free slice of pizza', TO_DATE('2024-03-23', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.Coupon(CID, MID, description, expirationDate)
VALUES (17, 17, 'One free beer', TO_DATE('2034-07-18', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.Coupon(CID, MID, description, expirationDate)
VALUES (18, 18, 'Free slice of pizza', TO_DATE('2024-03-23', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.Coupon(CID, MID, description, expirationDate)
VALUES (19, 19, '20 percent off order', TO_DATE('2024-03-23', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.Coupon(CID, MID, description, expirationDate)
VALUES (20, 20, '1 dollar any topping pizza', TO_DATE('2025-10-31', 'YYYY-MM-DD'));

INSERT INTO hamadayaz.Game(GID, name, tokenCost, factor)
VALUES(1, 'Space Invaders', 4, 2);
INSERT INTO hamadayaz.Game(GID, name, tokenCost, factor)
VALUES(2, 'Pac Man', 2, 3);
INSERT INTO hamadayaz.Game(GID, name, tokenCost, factor)
VALUES(3, 'Galaxian', 5, 4);
INSERT INTO hamadayaz.Game(GID, name, tokenCost, factor)
VALUES(4, 'Asteroids', 5, 5);
INSERT INTO hamadayaz.Game(GID, name, tokenCost, factor)
VALUES(5, 'Breakout', 10, 5);
INSERT INTO hamadayaz.Game(GID, name, tokenCost, factor)
VALUES(6, 'Pong', 3, 3);
INSERT INTO hamadayaz.Game(GID, name, tokenCost, factor)
VALUES(7, 'Robotron', 4, 2);
INSERT INTO hamadayaz.Game(GID, name, tokenCost, factor)
VALUES(8, 'Donkey Kong', 5, 5);
INSERT INTO hamadayaz.Game(GID, name, tokenCost, factor)
VALUES(9, 'Frogger', 5, 3);
INSERT INTO hamadayaz.Game(GID, name, tokenCost, factor)
VALUES(10, 'Galaga', 10, 10);
INSERT INTO hamadayaz.Game(GID, name, tokenCost, factor)
VALUES(11, 'Dig Dug', 2, 2);
INSERT INTO hamadayaz.Game(GID, name, tokenCost, factor)
VALUES(12, 'R-Type', 5, 3);
INSERT INTO hamadayaz.Game(GID, name, tokenCost, factor)
VALUES(13, 'Starwars', 10, 2);
INSERT INTO hamadayaz.Game(GID, name, tokenCost, factor)
VALUES(14, 'Final Fight', 2, 5);
INSERT INTO hamadayaz.Game(GID, name, tokenCost, factor)
VALUES(15, 'Tempest', 4, 4);
INSERT INTO hamadayaz.Game(GID, name, tokenCost, factor)
VALUES(16, 'Mortal Combat', 5, 3);
INSERT INTO hamadayaz.Game(GID, name, tokenCost, factor)
VALUES(17, 'Street Fighter', 10, 10);
INSERT INTO hamadayaz.Game(GID, name, tokenCost, factor)
VALUES(18, 'Bean Bash', 3, 7);
INSERT INTO hamadayaz.Game(GID, name, tokenCost, factor)
VALUES(19, 'Josh Bosh', 2, 10);
INSERT INTO hamadayaz.Game(GID, name, tokenCost, factor)
VALUES(20, 'Metal Slug', 2, 2);

INSERT INTO hamadayaz.GamePlay(GameplayID, GID, MID, score, ticketsEarned, datePlayed)
VALUES(1, 2, 1, 100, 33, TO_DATE('2022-09-11', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.GamePlay(GameplayID, GID, MID, score, ticketsEarned, datePlayed)
VALUES(2, 3, 2, 150, 37, TO_DATE('2022-09-11', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.GamePlay(GameplayID, GID, MID, score, ticketsEarned, datePlayed)
VALUES(3, 4, 2, 1000, 200, TO_DATE('2001-01-01', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.GamePlay(GameplayID, GID, MID, score, ticketsEarned, datePlayed)
VALUES(4, 19, 2, 1050, 105, TO_DATE('2012-10-11', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.GamePlay(GameplayID, GID, MID, score, ticketsEarned, datePlayed)
VALUES(5, 5, 5, 100, 20, TO_DATE('1990-08-23', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.GamePlay(GameplayID, GID, MID, score, ticketsEarned, datePlayed)
VALUES(6, 20, 12, 110, 55, TO_DATE('2020-09-04', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.GamePlay(GameplayID, GID, MID, score, ticketsEarned, datePlayed)
VALUES(7, 5, 5, 200, 40, TO_DATE('2018-02-23', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.GamePlay(GameplayID, GID, MID, score, ticketsEarned, datePlayed)
VALUES(8, 5, 6, 3100, 620, TO_DATE('2090-12-30', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.GamePlay(GameplayID, GID, MID, score, ticketsEarned, datePlayed)
VALUES(9, 10, 1, 10000, 1000, TO_DATE('2020-11-11', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.GamePlay(GameplayID, GID, MID, score, ticketsEarned, datePlayed)
VALUES(10, 9, 10, 160, 53, TO_DATE('2003-10-09', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.GamePlay(GameplayID, GID, MID, score, ticketsEarned, datePlayed)
VALUES(11, 11, 11, 1010, 505, TO_DATE('2022-09-11', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.GamePlay(GameplayID, GID, MID, score, ticketsEarned, datePlayed)
VALUES(12, 10, 18, 1600, 533, TO_DATE('2002-07-18', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.GamePlay(GameplayID, GID, MID, score, ticketsEarned, datePlayed)
VALUES(13, 10, 13, 100, 10, TO_DATE('2022-09-11', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.GamePlay(GameplayID, GID, MID, score, ticketsEarned, datePlayed)
VALUES(14, 10, 2, 400000, 40000, TO_DATE('1989-03-24', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.GamePlay(GameplayID, GID, MID, score, ticketsEarned, datePlayed)
VALUES(15, 15, 5, 16, 4, TO_DATE('2090-04-06', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.GamePlay(GameplayID, GID, MID, score, ticketsEarned, datePlayed)
VALUES(16, 1, 16, 9000, 4500, TO_DATE('2034-08-05', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.GamePlay(GameplayID, GID, MID, score, ticketsEarned, datePlayed)
VALUES(17, 17, 17, 360, 36, TO_DATE('2022-03-31', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.GamePlay(GameplayID, GID, MID, score, ticketsEarned, datePlayed)
VALUES(18, 8, 3, 45000, 900, TO_DATE('2020-12-25', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.GamePlay(GameplayID, GID, MID, score, ticketsEarned, datePlayed)
VALUES(19, 9, 9, 280, 93, TO_DATE('2030-05-28', 'YYYY-MM-DD'));
INSERT INTO hamadayaz.GamePlay(GameplayID, GID, MID, score, ticketsEarned, datePlayed)
VALUES(20, 20, 20, 3200, 1600, TO_DATE('2023-11-12', 'YYYY-MM-DD'));

INSERT INTO hamadayaz.Member(MID, name, phoneNo, address, tier, totalSpent, totalTickets)
VALUES(1, 'John', '689-411-0506', '4384 E. Reem St.', 'Diamond', 10000, 600);
INSERT INTO hamadayaz.Member(MID, name, phoneNo, address, tier, totalSpent, totalTickets)
VALUES(2, 'Bon', '111-222-3333', '900 Diane Blvd.', 'None', 30, 0);
INSERT INTO hamadayaz.Member(MID, name, phoneNo, address, tier, totalSpent, totalTickets)
VALUES(3, 'Arnald', '094-8833-4583', 'Bridgewater', 'Diamond', 230020, 90);
INSERT INTO hamadayaz.Member(MID, name, phoneNo, address, tier, totalSpent, totalTickets)
VALUES(4, 'Josh', '560-0933-9584', '8544 Blooming Fields Dr.', 'Diamond', 980000, 50000);
INSERT INTO hamadayaz.Member(MID, name, phoneNo, address, tier, totalSpent, totalTickets)
VALUES(5, 'Hamad', '123-456-7890', '123 N. Planter Ave.', 'Gold', 250, 5);
INSERT INTO hamadayaz.Member(MID, name, phoneNo, address, tier, totalSpent, totalTickets)
VALUES(6, 'Jenny', '690-532-4500', '9685 S. Salty Rock Dr.', 'None', 100, 100);
INSERT INTO hamadayaz.Member(MID, name, phoneNo, address, tier, totalSpent, totalTickets)
VALUES(7, 'Jerry', '987-234-0000', '9685 S. Salty Rock Dr.', 'Diamond', 9900, 80);
INSERT INTO hamadayaz.Member(MID, name, phoneNo, address, tier, totalSpent, totalTickets)
VALUES(8, 'Alex', '909-764-0022', 'S. Bean Ave.', 'Diamond', 300000, 40);
INSERT INTO hamadayaz.Member(MID, name, phoneNo, address, tier, totalSpent, totalTickets)
VALUES(9, 'May', '990-223-1111', 'Maybe It Maybaline', 'None', 200, 0);
INSERT INTO hamadayaz.Member(MID, name, phoneNo, address, tier, totalSpent, totalTickets)
VALUES(10, 'Winnie Wouse', '800-032-9445', '98 Club House Rd.', 'None', 50, 9000);
INSERT INTO hamadayaz.Member(MID, name, phoneNo, address, tier, totalSpent, totalTickets)
VALUES(11, 'Harold', '689-404-9876', '984 S. Kino Pky.', 'Gold', 300, 10);
INSERT INTO hamadayaz.Member(MID, name, phoneNo, address, tier, totalSpent, totalTickets)
VALUES(12, 'Barney', '320-876-3340', '098 Iron Cat Palace', 'None', 0, 0);
INSERT INTO hamadayaz.Member(MID, name, phoneNo, address, tier, totalSpent, totalTickets)
VALUES(13, 'Alfie', '320-876-3340', '098 Iron Cat Palace', 'None', 0, 0);
INSERT INTO hamadayaz.Member(MID, name, phoneNo, address, tier, totalSpent, totalTickets)
VALUES(14, 'Kiwi', '320-876-3340', '098 Iron Cat Palace', 'None', 0, 0);
INSERT INTO hamadayaz.Member(MID, name, phoneNo, address, tier, totalSpent, totalTickets)
VALUES(15, 'Sprout', '320-876-3340', '098 Iron Cat Palace', 'None', 0, 0);
INSERT INTO hamadayaz.Member(MID, name, phoneNo, address, tier, totalSpent, totalTickets)
VALUES(16, 'David', '123-333-3333', 'Whoop Whoop Dr.', 'Diamond', 980000, 20);
INSERT INTO hamadayaz.Member(MID, name, phoneNo, address, tier, totalSpent, totalTickets)
VALUES(17, 'Lester McCann', '900-900-9000', '21 Database Design Rd.', 'Diamond', 29000, 900);
INSERT INTO hamadayaz.Member(MID, name, phoneNo, address, tier, totalSpent, totalTickets)
VALUES(18, 'Beenie Beenie', '222-222-2222', 'Been Boi Bean', 'Gold', 400, 2);
INSERT INTO hamadayaz.Member(MID, name, phoneNo, address, tier, totalSpent, totalTickets)
VALUES(19, 'Phil', '689-422-4957', '908 E. Roger Rd.', 'Gold', 360, 60000);
INSERT INTO hamadayaz.Member(MID, name, phoneNo, address, tier, totalSpent, totalTickets)
VALUES(20, 'Loocus', '890-777-8417', '4384 E. Reem St.', 'Gold', 450, 90);

INSERT INTO hamadayaz.Prize(prizeID, description, ticketCost, inventoryCount)
VALUES(1, 'Bean plushie', 1000, 10);
INSERT INTO hamadayaz.Prize(prizeID, description, ticketCost, inventoryCount)
VALUES(2, 'Baked potato', 50, 10);
INSERT INTO hamadayaz.Prize(prizeID, description, ticketCost, inventoryCount)
VALUES(3, 'Assorted candy', 20, 10);
INSERT INTO hamadayaz.Prize(prizeID, description, ticketCost, inventoryCount)
VALUES(4, 'Nintendo Switch', 50000, 10);
INSERT INTO hamadayaz.Prize(prizeID, description, ticketCost, inventoryCount)
VALUES(5, 'Can of soup', 100, 10);
INSERT INTO hamadayaz.Prize(prizeID, description, ticketCost, inventoryCount)
VALUES(6, 'Meow meow plushie', 1000, 10);
INSERT INTO hamadayaz.Prize(prizeID, description, ticketCost, inventoryCount)
VALUES(7, 'Josh plushie', 1000, 10);
INSERT INTO hamadayaz.Prize(prizeID, description, ticketCost, inventoryCount)
VALUES(8, 'Dell XPS 13', 35000, 10);
INSERT INTO hamadayaz.Prize(prizeID, description, ticketCost, inventoryCount)
VALUES(9, 'Pants', 9000, 10);
INSERT INTO hamadayaz.Prize(prizeID, description, ticketCost, inventoryCount)
VALUES(10, 'Soda', 80, 10);
INSERT INTO hamadayaz.Prize(prizeID, description, ticketCost, inventoryCount)
VALUES(11, 'Dragon plushie', 1000, 10);
INSERT INTO hamadayaz.Prize(prizeID, description, ticketCost, inventoryCount)
VALUES(12, 'Jumbo unicorn plushie', 10000, 10);
INSERT INTO hamadayaz.Prize(prizeID, description, ticketCost, inventoryCount)
VALUES(13, 'Jumbo bean plushie', 10000, 10);
INSERT INTO hamadayaz.Prize(prizeID, description, ticketCost, inventoryCount)
VALUES(14, 'Wooden pencil', 20, 10);
INSERT INTO hamadayaz.Prize(prizeID, description, ticketCost, inventoryCount)
VALUES(15, 'Potted plant', 2500, 10);
INSERT INTO hamadayaz.Prize(prizeID, description, ticketCost, inventoryCount)
VALUES(16, 'Basket of corn', 8000, 10);
INSERT INTO hamadayaz.Prize(prizeID, description, ticketCost, inventoryCount)
VALUES(17, 'Jumbo nugget plushie', 10000, 10);
INSERT INTO hamadayaz.Prize(prizeID, description, ticketCost, inventoryCount)
VALUES(18, 'Lizard', 3000, 10);
INSERT INTO hamadayaz.Prize(prizeID, description, ticketCost, inventoryCount)
VALUES(19, 'Turtle plushie', 1000, 10);
INSERT INTO hamadayaz.Prize(prizeID, description, ticketCost, inventoryCount)
VALUES(20, 'Jumbo panda plushie', 10000, 10);
