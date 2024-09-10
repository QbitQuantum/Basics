int main()
{
   EnumWindowStationsW(EnumWindowStationProc, 0xbadbed);

   return 0;
}