BOOL Tdbm::open(String filename)
{
  // Set the path of your database file.
  // Replace "full_path_to_your_database_file" with the absolute path
  // to your SQLite database file.

  String path;
  path.sprintf(L"Database=%s", filename.c_str());
  conn->Params->Add(path);
  BOOL bSuccess= FALSE;
  try
  {
    // Establish the connection.
    conn->Connected = true;
    bSuccess = TRUE;
  }
  catch( Exception& e)
  {
  	ShowMessage(e.Message);
    bSuccess = FALSE;
  }

  return FALSE;
}