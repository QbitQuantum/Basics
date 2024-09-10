String PropertyUtils::getFormattedNumber( String numberStr, IsoString numberFormat )
{
   if ( numberStr.IsEmpty() )
      return numberStr;

   size_t im = numberFormat.Find( 'm' );
   if ( im == String::notFound )
      return String().Format( numberFormat.c_str(), stringToFloatSafe( numberStr ) );

   numberFormat.DeleteRight( im );
   numberFormat.DeleteLeft( 1 );
   StringList tokens;
   numberFormat.Break( tokens, '.', true/*trim*/ );
   size_t fraction = stringToIntSafe( tokens[1] );
   size_t width    = stringToIntSafe( tokens[0] ) - fraction;
   assert( width > 0 );
   int hours = Trunc( stringToFloatSafe( numberStr ) );
   switch ( fraction )
   {
   case 3:
      {
         int minutes = Trunc( (stringToFloatSafe( numberStr ) - hours)*60 );
         IsoString formatStr = '%' + IsoString().Format( "%dd",width ) + ":%02d";
         return String().Format( formatStr.c_str(), hours, Abs( minutes ) );
      }
   case 5:
      {
         int minutes     = Trunc( (stringToFloatSafe( numberStr ) - hours)*60 );
         int minutesfrac = Trunc( ((stringToFloatSafe( numberStr ) - hours)*60 - minutes)*10);
         IsoString formatStr = '%' + IsoString().Format( "%dd", width ) + ":%02d.%d";
         return String().Format( formatStr.c_str(), hours, Abs( minutes ), Abs( minutesfrac ) );
      }
   case 6:
      {
         int minutes     = Trunc( (stringToFloatSafe( numberStr ) - hours)*60 );
         int seconds     = Trunc( ((stringToFloatSafe( numberStr ) - hours)*60 - minutes)*60 );
         IsoString formatStr = '%' + IsoString().Format( "%dd", width ) + ":%02d:%02d";
         return String().Format( formatStr.c_str(), hours, Abs( minutes ), Abs( seconds ) );
      }
   case 8:
      {
         int minutes     = Trunc( (stringToFloatSafe( numberStr ) - hours)*60 );
         int seconds     = Trunc( ((stringToFloatSafe( numberStr ) - hours)*60 - minutes)*60 );
         int secondsfrac = Trunc( (((stringToFloatSafe( numberStr ) - hours)*60 - minutes)*60 - seconds)*10 );
         IsoString formatStr = '%' + IsoString().Format( "%dd", width ) + ":%02d:%02d.%d";
         return String().Format( formatStr.c_str(), hours, Abs( minutes ), Abs( seconds ), Abs( secondsfrac ) );
      }
   case 9:
      {
         int minutes     = Trunc( (stringToFloatSafe( numberStr ) - hours)*60 );
         int seconds     = Trunc( ((stringToFloatSafe( numberStr ) - hours)*60 - minutes)*60 );
         int secondsfrac = Trunc( (((stringToFloatSafe( numberStr ) - hours)*60 - minutes)*60 - seconds)*100 );
         IsoString formatStr = '%' + IsoString().Format( "%dd", width ) + ":%02d:%02d.%02d";
         return String().Format( formatStr.c_str(), hours, Abs( minutes ), Abs( seconds ), Abs( secondsfrac ) );
      }
   default:
      return String();
   }
}