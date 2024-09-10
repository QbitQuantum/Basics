void
HyphenateHD_Text( zCPCHAR cpcText, zPCHAR pchReturn, zLONG lMaxLth, zLONG lIdx )
{
   zBOOL bGoodBreak = FALSE;
   zLONG k;

   strcpy_s( pchReturn, lMaxLth, cpcText );
// if ( zstrcmp( cpcText, "M_InsertTextKeywordTitleDU" ) == 0 )
//    TraceLineS( "HyphenateCheck ", cpcText );

   while ( lIdx > 5 && lIdx > (zLONG) (zstrlen( cpcText ) / 2) )  // purist's goto
   {
      zPCHAR  pchTemp;
      zPCHAR  pch;

      // check for lowercase/uppercase change
      k = lIdx + 1;
      while ( k > lIdx - 5 )
      {
         if ( pchReturn[ k ] == '_' || (isupper( pchReturn[ k ] ) && islower( pchReturn[ k - 1 ] )) )
         {
            if ( k <= lIdx )
            {
               bGoodBreak = TRUE;
               if ( pchReturn[ k ] == '_' )
                  lIdx = k;
               else
                  lIdx = k - 1;

               break;
            }
         }

         k--;
      }

      if ( k > lIdx - 5 )
         break;  // we found a good place to break

      // check for standard endings that would make a good place to break the text
      pchTemp = pchReturn + lIdx - 5;
      if ( (pch = zstrstr( pchTemp, "ing" )) != 0 ||
           (pch = zstrstr( pchTemp, "able" )) != 0 ||
           (pch = zstrstr( pchTemp, "tion" )) != 0 ||
           (pch = zstrstr( pchTemp, "bute" )) != 0 ||
           (pch = zstrstr( pchTemp, "er" )) != 0 )
      {
         if ( pch < pchReturn + lIdx )
         {
            k = pchReturn + lIdx - pch;
            lIdx -= k;
         }
      }

      break;  // get out of purist's goto (while)
   }

   k = ++lIdx;
   if ( bGoodBreak == FALSE )
      pchReturn[ lIdx++ ] = '-';

   pchReturn[ lIdx++ ] = '\n';
   strcpy_s( pchReturn + lIdx, lMaxLth - lIdx, cpcText + k );
}