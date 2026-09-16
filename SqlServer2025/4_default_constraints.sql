select * from tblEmployee
select * from tblGender

Insert into tblEmployee (ID, Name, Email, GenderID, Salary) values (1, 'John Doe', 'a@bc.com', 1, 50000.00)

-- null values can be skipped in the insert statement
-- whenever a nullable value is skipped, 
-- adding the default constraint allows the db to insert default values into the column. 

-- add default constraint to the table
Alter table tblEmployee
Add constraint DF_tblEmployee_GenderID
Default 3 for GenderID

-- for now 3 stands for 'Not Specified' in the tblGender table.

-- adding NULL specifically in the nullable field does not trigger the default constraint. 
-- The default constraint is only triggered when the column is omitted from the insert statement.

-- drop default constraint
Alter table tblEmployee
Drop constraint DF_tblEmployee_GenderID