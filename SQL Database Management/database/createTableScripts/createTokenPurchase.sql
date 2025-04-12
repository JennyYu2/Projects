CREATE TABLE jennyyu.TokenPurchase (
	PID	varchar2(7) NOT NULL,
	MID	varchar2(7),
	tokenNo	integer,
	purchaseDate	date,
	primary key	(PID),
	FOREIGN KEY (MID) REFERENCES jennyyu.Member (MID)
);