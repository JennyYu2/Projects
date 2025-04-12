CREATE TABLE jennyyu.Prize (
	prizeID	varchar2(7) NOT NULL,
	description	varchar2 (100),
	ticketCost	integer,
	inventoryCount	integer DEFAULT 0,
	primary key	(prizeID)
);