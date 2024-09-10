int binarysearch( ListA& l, int ArraySize, int compare, int index )
{
   int hold,tempi = ArraySize/2;
   ListA newL( tempi+1 );

   //if the array size is larger than one run this condition
   if( ArraySize > 1 )
   {
      l.gotoBeginning();

      //put the cursor on the middle of the list
      toNext( tempi, l, index );

      l.getCursor( hold );
      
      //if the number appears in the lower half of the list runs this condition
      if( compare < hold )
      {
         tempi = ArraySize/2;

         //creates a new list from the bottom half of the current list
         l.gotoBeginning();
         newList( newL, tempi, l );

         //passes the new list for recursion
         return binarysearch( newL, tempi, compare, index-tempi );
      }
      //if the number appears in the upperhalf of the list runs this condition
      else
      {
         tempi = ArraySize - ArraySize/2;

         //creates a new list from the top half of the current list
         newList( newL, tempi, l );

         //passes the new list for recursion
         return binarysearch( newL, tempi, compare, index );
      }
   }
   else
      //this is the end condition
      return index;

   //the function should never reach this point this is just to stop the warning
   return -1;

}