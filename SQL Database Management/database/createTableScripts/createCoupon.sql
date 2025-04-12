CREATE TABLE jennyyu.Coupon (
	CID	varchar2(7) NOT NULL,
	MID	varchar2(7),
	description	varchar2(100),
	expirationDate	date,
	primary key	(CID),
	FOREIGN KEY (MID) REFERENCES jennyyu.Member(MID)
);