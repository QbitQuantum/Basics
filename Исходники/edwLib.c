struct sqlConnection *edwConnect()
/* Returns a read only connection to database. */
{
return sqlConnect(edwDatabase);
}