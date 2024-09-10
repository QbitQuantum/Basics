void INITIALIZE()
{
  SHOW_PROGRESS(1);
   
  COPY_FILE_HERE("MIUI_DHD_ROM\\MIUI.zip");   /* move MIUI.zip to work dic */
  
  RENAME("MIUI.zip","temp.zip");
  
  _7zUNPACK("temp.zip");
  
  DELETE_FILE("temp.zip");  
}