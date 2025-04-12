CREATE TABLE hamadayaz.Coupon (
    CID varchar2(7) NOT NULL,
    MID varchar2(7),
    description varchar2(100),
    expirationDate date,
    PRIMARY KEY (CID),
    FOREIGN KEY (MID) REFERENCES hamadayaz.Member(MID)
);

CREATE TABLE hamadayaz.GamePlay (
    GameplayID varchar2(7) NOT NULL,
    GID varchar2(7),
    MID varchar2(7),
    score integer,
    ticketsEarned integer,
    datePlayed date,
    PRIMARY KEY (GameplayID),
    FOREIGN KEY (GID) REFERENCES hamadayaz.Game(GID),
    FOREIGN KEY (MID) REFERENCES hamadayaz.Member(MID)
);

CREATE TABLE hamadayaz.Member (
    MID varchar2(7) NOT NULL,
    name varchar2(100),
    phoneNo varchar2(13),
    address varchar2(100),
    tier varchar2(7),
    totalSpent number(8, 2),
    totalTickets integer,
    PRIMARY KEY (MID)
);

CREATE TABLE hamadayaz.PrizeRedemption (
    xactID varchar2(7) NOT NULL,
    MID varchar2(7),
    PrizeID varchar2(7),
    xactDate date,
    PRIMARY KEY (xactID),
    FOREIGN KEY (MID) REFERENCES hamadayaz.Member(MID),
    FOREIGN KEY (PrizeID) REFERENCES hamadayaz.Prize(prizeID)
);

CREATE TABLE hamadayaz.TokenPurchase (
    PID varchar2(7) NOT NULL,
    MID varchar2(7),
    tokenNo integer,
    purchaseDate date,
    PRIMARY KEY (PID),
    FOREIGN KEY (MID) REFERENCES hamadayaz.Member(MID)
);

CREATE TABLE hamadayaz.Game (
        GID     varchar2(7) NOT NULL,
        name    varchar2(100),
        tokenCost       integer,
        ticketAmount    integer,
        primary key     (GID)
);

CREATE TABLE hamadayaz.Prize (
    prizeID varchar2(7) NOT NULL,
    description varchar2(100),
    ticketCost integer,
    inventoryCount NUMBER DEFAULT 0,
    PRIMARY KEY (prizeID)
);
