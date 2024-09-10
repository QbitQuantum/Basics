   int LER_LerParmNome( char * Parm , int * tamNome , int dimNome )
   {

      int inxParm = 0 ;

      #ifdef _DEBUG
         TST_ASSERT( Inicializado ) ;
      #endif

      PularBrancos( ) ;

      *tamNome = 0 ;

      if ( ! isalpha( LER_Buffer[ LER_InxBuffer ] ))
      {
         ExibirErro( "Nome deve iniciar com letra." ) ;
         Parm[ inxParm ] = 0 ;
         return 0 ;
      } /* if */

      Parm[ inxParm ] = LER_Buffer[ LER_InxBuffer ] ;

      LER_InxBuffer ++ ;
      inxParm ++ ;

      while ( LER_InxBuffer < LER_TamBuffer )
      {
         if ( __iscsym( LER_Buffer[ LER_InxBuffer ] ))
         {
            Parm[ inxParm ] = LER_Buffer[ LER_InxBuffer ] ;

         } else
         {
            Parm[ inxParm ] = 0 ;
            *tamNome        = inxParm ;
            return TRUE ;
         } /* if */

         LER_InxBuffer ++ ;
         inxParm ++ ;

         if ( inxParm > dimNome )
         {
            ExibirErro( "Nome longo demais." ) ;
            Parm[ dimNome - 1 ] = 0 ;
            *tamNome            = dimNome - 1 ;
            return FALSE ;
         } /* if */
         
      } /* while */

      Parm[ inxParm ] = 0 ;
      *tamNome        = inxParm ;
      return TRUE ;

   } /* Fim função: LER  &Ler parâmetro nome */