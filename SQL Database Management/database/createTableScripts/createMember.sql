CREATE TABLE jennyyu.Member (
	MID	varchar2(7) NOT NULL,
	name	varchar2(100),
	phoneNo	varchar2(13),
	address	varchar2(100),
	tier	varchar2(7),
	totalSpent	number(8, 2),
	totalTickets	integer,
	primary key	(MID)
);