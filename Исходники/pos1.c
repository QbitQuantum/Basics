/* helper function for the posxxx() functions */
static void do_pos1( int iSwitch )
{

   if( ( ISCHAR( 1 ) )                       /* all functions need string as 1st param */
       &&
       ( ( iSwitch != DO_POS1_POSRANGE )     /* that's the only condition for all funcs _except_ POSRANGE */
         ||
         ( ( iSwitch == DO_POS1_POSRANGE )   /* In addition, POSRANGE needs .. */
          &&
          ( ISCHAR( 2 ) )                    /* .. string as 2nd .. */
          &&
          ( ISCHAR( 3 ) )                    /* .. and 3rd param */
         )
       )
       )
   {

      unsigned char *   pcString;
      size_t            sStrLen;
      unsigned char *   puc, ucChar1 = ' ', ucChar2 = ' ';
      int               iMode;
      size_t            sIgnore;
      int               iParamShift = 0;

      if( iSwitch == DO_POS1_POSRANGE )
      {

         if( hb_parclen( 1 ) == 0 )
         {
            hb_retnl( 0 );
            return;
         }
         else
         {
            ucChar1 = *( hb_parc( 1 ) );
         }

         if( hb_parclen( 2 ) == 0 )
         {
            hb_retnl( 0 );
            return;
         }
         else
         {
            ucChar2 = *( hb_parc( 2 ) );
         }

         iParamShift += 2;
      }

      pcString = ( unsigned char * ) hb_parc( iParamShift + 1 );
      sStrLen  = ( size_t ) hb_parclen( iParamShift + 1 );

      if( ISLOG( iParamShift + 2 ) )
         iMode = hb_parl( iParamShift + 2 );
      else
         iMode = 0;

      if( ISNUM( iParamShift + 3 ) )
         sIgnore = ( size_t ) hb_parnl( iParamShift + 3 );
      else
         sIgnore = 0;

      for( puc = pcString + sIgnore; puc < pcString + sStrLen; puc++ )
      {
         int iDoRet = 0;
         switch( iSwitch )
         {
            case DO_POS1_POSALPHA:
            {
               iDoRet = ISALPHA( *puc );
            }; break;

            case DO_POS1_POSLOWER:
            {
               iDoRet = ISLOWER( *puc );
            }; break;

            case DO_POS1_POSRANGE:
            {
               iDoRet = ( ( ucChar1 <= *puc ) && ( ucChar2 >= *puc ) );
            }; break;

            case DO_POS1_POSUPPER:
            {
               iDoRet = ISUPPER( *puc );
            }; break;
         }

         if( ( iMode && ! iDoRet ) || ( ! iMode && iDoRet ) )
         {
            hb_retns( puc - pcString + 1 );
            return;
         }
      }

      hb_retnl( 0 );

   }
   else /* ISCHAR (1) etc. */
   {
      PHB_ITEM pSubst         = NULL;
      int      iArgErrorMode  = ct_getargerrormode();
      if( iArgErrorMode != CT_ARGERR_IGNORE )
      {
         switch( iSwitch )
         {
            case DO_POS1_POSALPHA:
            {
               pSubst = ct_error_subst( ( USHORT ) iArgErrorMode, EG_ARG, CT_ERROR_POSALPHA,
                                        NULL, "POSALPHA", 0, EF_CANSUBSTITUTE, 3,
                                        hb_paramError( 1 ), hb_paramError( 2 ), hb_paramError( 3 ) );
            }; break;

            case DO_POS1_POSLOWER:
            {
               pSubst = ct_error_subst( ( USHORT ) iArgErrorMode, EG_ARG, CT_ERROR_POSLOWER,
                                        NULL, "POSLOWER", 0, EF_CANSUBSTITUTE, 3,
                                        hb_paramError( 1 ), hb_paramError( 2 ), hb_paramError( 3 ) );
            }; break;

            case DO_POS1_POSRANGE:
            {
               pSubst = ct_error_subst( ( USHORT ) iArgErrorMode, EG_ARG, CT_ERROR_POSRANGE,
                                        NULL, "POSRANGE", 0, EF_CANSUBSTITUTE, 5,
                                        hb_paramError( 1 ), hb_paramError( 2 ), hb_paramError( 3 ),
                                        hb_paramError( 4 ), hb_paramError( 5 ) );
            }; break;

            case DO_POS1_POSUPPER:
            {
               pSubst = ct_error_subst( ( USHORT ) iArgErrorMode, EG_ARG, CT_ERROR_POSUPPER,
                                        NULL, "POSUPPER", 0, EF_CANSUBSTITUTE, 3,
                                        hb_paramError( 1 ), hb_paramError( 2 ), hb_paramError( 3 ) );
            }; break;
         }
      }

      if( pSubst != NULL )
      {
         hb_itemRelease( hb_itemReturnForward( pSubst ) );
      }
      else
      {
         hb_retnl( 0 );
      }
   }
}