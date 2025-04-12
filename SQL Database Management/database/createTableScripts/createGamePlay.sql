CREATE TABLE jennyyu.GamePlay (
	GameplayID	varchar2(7) NOT NULL,
	GID	varchar2(7),
	MID	varchar2(7),
	score	integer,
	ticketsEarned	integer,
	datePlayed	date,
	primary key	(GameplayID),
        FOREIGN KEY (GID) REFERENCES jennyyu.Game(GID),
        FOREIGN KEY (MID) REFERENCES jennyyu.Member(MID)
);