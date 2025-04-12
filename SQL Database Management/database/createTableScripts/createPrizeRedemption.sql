CREATE TABLE jennyyu.PrizeRedemption (
	xactID	varchar2(7) NOT NULL,
	MID	varchar2(7),
	prizeID	varchar2(7),
	xactDate	date,
	primary key	(xactID),
    	FOREIGN KEY (MID) REFERENCES jennyyu.Member(MID),
    	FOREIGN KEY (prizeID) REFERENCES jennyyu.Prize(prizeID)
);