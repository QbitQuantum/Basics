//------------------------------------------------------------------------------------
//  Прочитать блок данных непосредственно из Flash - памяти
//	Параметры: PageAdr    -> Номер страницы, с которой начинать чтение
//                  Addr       -> Адрес в странице, с которого начинать чтение
//                  Count      -> Количество байт, которое необходимо прочитать
//  		   *BufferPtr -> Адрес буффера в который заносить данные
//------------------------------------------------------------------------------------
void df_FlashRead( uint16 PageAdr, uint16 Addr, uint16 Count, uint8 *BufferPtr )
{
   SELECT();

   DF_SPI_RW(ContArrayRead);
   DF_SPI_RW((unsigned char)(PageAdr >> (16 - df_Info.page_bit)));
   DF_SPI_RW((unsigned char)((PageAdr << (df_Info.page_bit - 8))+ (Addr>>8)));
   DF_SPI_RW((unsigned char)(Addr));
   DF_SPI_RW(0x00);
   DF_SPI_RW(0x00);
   DF_SPI_RW(0x00);
   DF_SPI_RW(0x00);

   for( uint16 i=0; i < Count; i++ )
   {
      *(BufferPtr) = DF_SPI_RW(0x00);
      BufferPtr++;
   }

   DESELECT();
}