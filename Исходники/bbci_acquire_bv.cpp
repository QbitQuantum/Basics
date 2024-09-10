static void abv_close()
{
  closeConnection();
  connected = 0;
  
  filterClose();
}