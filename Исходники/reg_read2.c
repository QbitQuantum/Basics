int main(int argc, char *argv[])
{
char data[256];
char key1[180]="SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\SideBySide\\Installations\\x86_Microsoft.Tools.VisualCPlusPlus.Runtime-Libraries_6595b64144ccf1df_6.0.0.0_x-ww_ff9986d7\\Codebases\\OS";
char key2[90]= "software\\microsoft\\windows nt\\currentversion"; 
HKEY hkey;              // Handle to registry key
unsigned long datalen;  // data field length(in), data returned length(out) 
unsigned long datatype; // #defined in winnt.h (predefined types 0-11)
// Open the HKLM key, key1, from which we wish to get data
if (!RegOpenKeyExA(HKEY_LOCAL_MACHINE,
   key1,
   NULL,
   KEY_QUERY_VALUE, // Set up field value query activity
   &hkey) == ERROR_SUCCESS)
      {
      printf("Error opening HKLM subkey: %s\n",key1);
      return GetLastError();
      }
printf("\n");
// Datalen is an in/out field, so reset it for every query
// I've ignored displays in the event of an error ...
// The error is most likely to be a misspelled value field name
datalen = 255;
// Read the value for "prompt" via the handle 'hkey'
if (RegQueryValueExA(hkey,
    "prompt",
    NULL,
    &datatype,
    data,
    &datalen) == ERROR_SUCCESS)
    printf("Edition:\t%s\n",data);
// That's all for this key. Close it.
RegCloseKey(hkey);
// Open up the next key for reading
if (!RegOpenKeyExA(HKEY_LOCAL_MACHINE,
   key2,
   NULL,
   KEY_QUERY_VALUE,
   &hkey) == ERROR_SUCCESS)
      {
      printf("Error opening HKLM subkey: %s\n",key2);
      return GetLastError();
      }
datalen = 255;
if (RegQueryValueExA(hkey,
    "ProductId",
    NULL,
    &datatype,
    data,
    &datalen) == ERROR_SUCCESS)
    printf("Product Id:\t%s\n",data);
datalen = 255;
if (RegQueryValueExA(hkey,
    "productname",
    NULL,
    &datatype,
    data,
    &datalen) == ERROR_SUCCESS)
    printf("Product:\t%s\n",data);
datalen = 255;
if (RegQueryValueExA(hkey,
    "registeredowner",
    NULL,
    &datatype,
    data,
    &datalen) == ERROR_SUCCESS)
    printf("Reg Owner:\t%s\n",data);
datalen = 255;
if (RegQueryValueExA(hkey,
    "CurrentVersion",
    NULL,
    &datatype,
    data,
    &datalen) == ERROR_SUCCESS)
    printf("OS Version:\t%s\n",data);
datalen = 255;
if (RegQueryValueExA(hkey,
    "CurrentBuildNumber",
    NULL,
    &datatype,
    data,
    &datalen) == ERROR_SUCCESS)
    printf("Build #:\t%s\n",data);
datalen = 255;
if (RegQueryValueExA(hkey,
    "Buildlab",
    NULL,
    &datatype,
    data,
    &datalen) == ERROR_SUCCESS)
    printf("Build Label:\t%s\n",data);
datalen = 255;
if (RegQueryValueExA(hkey,
    "CSDVersion",
    NULL,
    &datatype,
    data,
    &datalen) == ERROR_SUCCESS)
    printf("Srvc Level:\t%s\n",data);
RegCloseKey(hkey);
return 0;
}