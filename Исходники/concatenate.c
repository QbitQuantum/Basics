int main(void)
{
   ListPtr list1 = createlist('0');
   ListPtr list2 = createlist('A');

   showlist(list1);
   showlist(list2);

   concatenate(list1, list2);

   showlist(list1);

   return 0;
} /* E0F main */