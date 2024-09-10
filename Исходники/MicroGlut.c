static unsigned char scan2ascii(WPARAM vk, LPARAM scancode)
{
   static HKL layout;
   static unsigned char State[256];
   static unsigned char chars[2];
   int count;

   layout = GetKeyboardLayout(0);
   if (GetKeyboardState(State)==FALSE)
      return 0;
   count = ToAsciiEx(vk,scancode,State,&chars,0,layout);
   if (count > 0) return chars[0];
   else return 0;
}