/*
打印指定的格式的数值
参数
title,前缀字符串
value,需要显示的数值
format,需要显示的进制，十进制为10,十六进制为16
*/
void NPI_PrintValue(char *title, uint16 value, uint8 format)
{
  uint8 tmpLen;
  uint8 buf[128];
  uint32 err;

  tmpLen = (uint8)osal_strlen( (char*)title );
  osal_memcpy( buf, title, tmpLen );
  buf[tmpLen] = ' ';
  err = (uint32)(value);
  _ltoa( err, &buf[tmpLen+1], format );
  NPI_PrintString(buf);		
}