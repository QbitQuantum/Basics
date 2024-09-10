 bool TabRow::update(const QVariantList& args) const
 {
   if (args.length() == 0)
   {
     return true;  // nothing to do
   }
   
   if ((args.length() % 2) != 0)
   {
     throw std::invalid_argument("Update row: Need an even number of arguments (column / value pairs)");
   }
   
   // create the SQL statement
   QString sql = "UPDATE " + tabName + " SET ";
   
   // split the combined column/values list in "args" into a separate list of values
   QVariantList vals;
   QVariantList::const_iterator i = args.begin();
   while (i != args.end())
   {
     QString colName = (*i).toString();
     if (colName == "id")
     {
       throw std::invalid_argument("Update row: can't alter value of the ID column!");
     }
     sql += colName + " = ?, ";
     i++;
     vals << (*i);
     i++;
   }
   
   // remove the trailing ", "
   sql = sql.left(sql.length() - 2);
   
   // complete the statement
   sql += " WHERE id = ?";
   vals << rowId;
   
   int result = db->execNonQuery(sql, vals);
   
   return (result == 1);
 }