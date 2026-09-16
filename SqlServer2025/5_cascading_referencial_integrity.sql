-- delete the value of foreign key from parent table, causes four cases:
-- 1. Restrict: Prevents deletion of the parent row if there are any related child rows.
-- 2. Cascade: Automatically deletes the related child rows when the parent row is deleted.
-- 3. Set Null: Sets the foreign key values in the related child rows to NULL
-- 4. Set Default: Sets the foreign key values in the related child rows to their default value.

Delete from tblGender 
Where GenderID = 1;

