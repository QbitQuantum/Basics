int OpenInFilePC(char *NameF)                                  //Открыли входной файл для чтения с компьютера
{
   Size_inF.QuadPart = 0;
   inFile = CreateFile(NameF, GENERIC_READ, FILE_SHARE_READ, NULL,
                       OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
   if(inFile == INVALID_HANDLE_VALUE)
      return ErrorSys2(NameF, (Lan+84)->msg);                //"Ошибка при открытии файла для чтения.");
   Size_inF.u.LowPart = GetFileSize(inFile, &Size_inF.u.HighPart);
   if(Size_inF.u.LowPart == 0xFFFFFFFF && GetLastError() != NO_ERROR)
      return ErrorSys2(NameF, (Lan+85)->msg);                //"Ошибка при запросе размера файла."
   if(Size_inF.QuadPart == 0)
      return Error2(NameF, (Lan+86)->msg);                   //"Недопустимо малый размер файла."
   GetFileTime(inFile, NULL, NULL, &Time_inF);               //Дата последней записи
   return 0;
}