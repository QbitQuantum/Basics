CTString IFeel_GetProjectFileName()
{
  CTString strIFeelTable;
  CTFileName fnIFeelTable = (CTString)"Data\\IFeel.txt";
  CTString strDefaultProjectFile = "Data\\Default.ifr";
  // get product name
  CTString strProduct = IFeel_GetProductName();
  try
  {
    strIFeelTable.Load_t(fnIFeelTable);
  }
  catch(char *strErr)
  {
    CPrintF("%s\n",strErr);
    return "";
  }

  CTString strLine;
  // read up to 1000 devices
  for(INDEX idev=0;idev<1000;idev++)
  {
    char strDeviceName[256];
    char strProjectFile[256];
    strLine = strIFeelTable;
    // read first line
    strLine.OnlyFirstLine();
    if(strLine==strIFeelTable)
    {
      break;
    }
    // remove that line 
    strIFeelTable.RemovePrefix(strLine);
    strIFeelTable.DeleteChar(0);
    // read device name and project file name
    strIFeelTable.ScanF("\"%256[^\"]\" \"%256[^\"]\"",&strDeviceName,&strProjectFile);
    // check if this is default 
    if(strcmp(strDeviceName,"Default")==0) strDefaultProjectFile = strProjectFile;
    // check if this is current device 
    if(strProduct == strDeviceName) return strProjectFile;
  }
  // device was not found, return default project file
  CPrintF("No project file specified for device '%s'.\nUsing default project file\n",strProduct);
  return strDefaultProjectFile;
}