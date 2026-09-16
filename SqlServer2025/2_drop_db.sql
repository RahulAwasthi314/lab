Drop Database NewDb

sp_deleteDb 'NewDb'

-- The db should not be in use when you drop it. If it is in use, you will get an error message. You can set the db to single user mode before dropping it.
-- so that multiple users cannot access it. That way while deleting only you will have access.
-- multi user mode

Alter Database NewDb 
Set Single_User 
With Rollback Immediate
-- with rollback immediate will rollback any uncommitted transactions and disconnect any other users that are connected to the database. This will rollback any incomplete transaction and closes connection to db.
-- system db cannot be dropped.