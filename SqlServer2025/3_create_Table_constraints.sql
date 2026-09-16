-- specify the database to use
Use [DbNew]
Go

create table tblGender {
    ID int NOT NULL PRIMARY KEY,
    Gender varchar(10) NOT NULL
}

create table tblEmployee {
    ID int NOT NULL PRIMARY KEY,
    Name varchar(50) NOT NULL,
    Email varchar(50) NOT NULL,
    GenderID int NOT NULL FOREIGN KEY REFERENCES tblGender(ID),
    Salary decimal(10,2) NOT NULL
}

-- foreign key prevents invalid data from being inserted into the foreign key column. It also prevents data from being deleted from the parent table if it is being used in the child table.

-- add foreign key constraint to the table
Alter table tblEmployee
Add constraint FK_tblEmployee_tblGender
Foreign Key (GenderID) References tblGender(ID)

-- add unique constraint to the table
Alter table tblEmployee
Add constraint UNQ_tblEmployee_Email
Unique (Email)

-- how to remove two constraints in one statement
Alter table tblEmployee
Add constraint FK_tblEmployee_tblGender
Foreign Key (GenderID) References tblGender(ID),
Add constraint UNQ_tblEmployee_Email
Unique (Email)

-- drop constraints
Alter table tblEmployee
Drop constraint FK_tblEmployee_tblGender,
Drop constraint UNQ_tblEmployee_Email