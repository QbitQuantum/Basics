//------------------------------------------------------------------------------
int callback_sqlite_chrome(void *datas, int argc, char **argv, char **azColName)
{
  FORMAT_CALBAK_READ_INFO *type = datas;
  char tmp[MAX_PATH]="";
  char date[DATE_SIZE_MAX]="";
  unsigned int i,size=0;

  if (type->type <= nb_sql_CHROME)
  {
    //special case of password !!!
    if(sql_CHROME[type->type].test_string_id == SPECIAL_CASE_CHROME_PASSWORD)
    {
      char password[MAX_PATH]="", raw_password[MAX_PATH]="";

      //decrypt datas password !!!
      CRYPT_INTEGER_BLOB data_in, data_out;
      data_in.cbData = strlen(argv[3]);
      data_in.pbData = (BYTE*)argv[3];

      snprintf(tmp,MAX_PATH,"%s, %s",argv[1],argv[2]);
      snprintf(raw_password,MAX_PATH,"%s",argv[3]);

      if (CryptUnprotectData(&data_out,NULL,NULL,NULL,NULL,0,&data_in))
      {
        snprintf(password,MAX_PATH,"%s",data_out.pbData);
        LocalFree(data_out.pbData);
      }
      convertStringToSQL(tmp, MAX_PATH);
      convertStringToSQL(password, MAX_PATH);
      convertStringToSQL(raw_password, MAX_PATH);
      addPasswordtoDB(tmp_file_chrome,tmp,password,raw_password,SPECIAL_CASE_CHROME_PASSWORD,current_session_id,db_scan);
    }else
    {
      //copy datas
      for (i=0;i<argc && MAX_PATH-size > 0 && start_scan;i++)
      {
        if (argv[i] == NULL)continue;

        //date or not ?
        if (strlen(argv[i]) == DATE_SIZE_MAX-1)
        {
          if (argv[i][4] == '/' && argv[i][13] == ':')
          {
            if (strcmp("1970/01/01 01:00:00",argv[i])!=0 && strcmp("1601/01/01 01:00:00",argv[i])!=0)strncpy(date,argv[i],DATE_SIZE_MAX);
            continue;
          }
        }
        if (i>0)snprintf(tmp+size,MAX_PATH-size,", %s",convertUTF8toUTF16(argv[i], strlen(argv[i])+1));
        else snprintf(tmp+size,MAX_PATH-size,"%s",convertUTF8toUTF16(argv[i], strlen(argv[i])+1));
        size = strlen(tmp);
      }
      //get datas and write it
      convertStringToSQL(tmp, MAX_PATH);
      addChrometoDB(tmp_file_chrome,sql_CHROME[type->type].params,tmp,date,sql_CHROME[type->type].test_string_id,current_session_id,db_scan);
    }
  }
  return 0;
}