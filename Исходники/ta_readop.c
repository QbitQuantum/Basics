static TA_RetCode findTokenId( TA_Libc *libHandle,
                               const char *str,
                               TA_TokenId *id,
                               TA_Integer *optionalParam )
{
   TA_PROLOG;
   unsigned int i;
   const char *cmp_str;
   TA_TokenId tokenId;
   unsigned int extractedParam;
   TA_RetCode retCode;

   TA_TRACE_BEGIN( libHandle, findTokenId );

   *id = TA_TOK_END;
   *optionalParam = 0;

   tokenId = TA_TOK_END;
   extractedParam = 0;

   /* First check for token directly mapping to a simple string. */
   for( i=0; (i < TA_NB_TOKEN_ID) && (tokenId == TA_TOK_END); i++ )
   {
      cmp_str = TA_TokenString( libHandle, (TA_TokenId)i );

      if( cmp_str )
      {
          #if defined( WIN32 )
          if( stricmp( str, cmp_str ) == 0 )
          #else
          if( strcasecmp( str, cmp_str ) == 0 )
          #endif
          {
             tokenId = (TA_TokenId)i;
             extractedParam = 1;
          }
      }
   }

   /* If not found, look for more advanced token taking
    * optional "=n" parameters.
    */
   if( tokenId == TA_TOK_END )
   {
      retCode = findTokenIdWithParam( libHandle, &str[0], &tokenId, &extractedParam );

      if( retCode != TA_SUCCESS )
      {
         TA_TRACE_RETURN( retCode );
      }
   }

   /* Make sure it is a valid field for a file description. */
   switch( tokenId )
   {
   case TA_TOK_YYYY:
   case TA_TOK_YY:
   case TA_TOK_Y:
   case TA_TOK_M:
   case TA_TOK_MM:
   case TA_TOK_MMM:
   case TA_TOK_D:
   case TA_TOK_DD:
   case TA_TOK_OPEN:
   case TA_TOK_HIGH:
   case TA_TOK_LOW:
   case TA_TOK_CLOSE:
   case TA_TOK_VOLUME:
   case TA_TOK_OPENINTEREST:
   case TA_TOK_HOUR:
   case TA_TOK_MIN:
   case TA_TOK_SEC:
   case TA_TOK_HH:
   case TA_TOK_MN:
   case TA_TOK_SS:
   case TA_TOK_SKIP_N_CHAR:
   case TA_TOK_SKIP_N_HEADER_LINE:
   case TA_TOK_SKIP_N_REAL:
   case TA_TOK_SKIP_N_INTEGER:
      break;
   default:
      TA_TRACE_RETURN( TA_INVALID_FIELD );
   }

   /* Everything is fine, return the information. */
   *id = tokenId;
   *optionalParam = extractedParam;

   TA_TRACE_RETURN( TA_SUCCESS );
}