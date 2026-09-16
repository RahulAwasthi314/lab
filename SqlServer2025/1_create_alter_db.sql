-- 1. Creating a db


-- https://www.youtube.com/watch?v=TuxuHHacIWU&list=PL08903FB7ACA1C2FB&index=3

Create Database NewDb

-- NewDb.mdf -> data file
-- NewDb.ldf => tranx Log file

Alter Database NewDb 
Modify Name = DbNew

Execute sp_renameDB "NewDb", "DbNew"

-- SP are group of command that are executed together
-- 1 system stored procedure
-- 2 user defined stored procedure

-- sp_helpIndex
-- sp_renameDb