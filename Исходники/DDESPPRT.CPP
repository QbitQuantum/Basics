/*------------------------------*/ BOOL     //--------------------------------
/*module ::*/                                                        DDE_Error
(
DWORD   DDEIdentifier ,
const String&  FunctionNameRef ,
const String&  MessageRef
)
   {
   BOOL   Error_Occured  =  FALSE;
   
   int  DDE_Error_Number = DdeGetLastError( DDEIdentifier );
   if(  DDE_Error_Number !=  DMLERR_NO_ERROR )
      {
		String	Error_String;
		switch( DDE_Error_Number )
			{
			case DMLERR_ADVACKTIMEOUT : 
					{ Error_String = "ADVACKTIMEOUT";       break; } 
			case DMLERR_BUSY :              
					{ Error_String = "BUSY";                break; } 
			case DMLERR_DATAACKTIMEOUT : 
					{ Error_String = "DATAACKTIMEOUT";      break; } 
		   case DMLERR_DLL_NOT_INITIALIZED : 
					{ Error_String = "DLL_NOT_INITIALIZED"; break; } 
		   case DMLERR_DLL_USAGE : 
					{ Error_String = "DLL_USAGE";           break; } 
		   case DMLERR_EXECACKTIMEOUT : 
					{ Error_String = "EXECACKTIMEOUT";      break; } 
		   case DMLERR_INVALIDPARAMETER : 
					{ Error_String = "INVALIDPARAMETER";    break; } 
		   case DMLERR_LOW_MEMORY : 
					{ Error_String = "LOW_MEMORY";          break; } 
		   case DMLERR_MEMORY_ERROR : 
					{ Error_String = "MEMORY_ERROR";        break; } 
		   case DMLERR_NO_CONV_ESTABLISHED : 
					{ Error_String = "NO_CONV_ESTABLISHED"; break; } 
		   case DMLERR_NOTPROCESSED : 
					{ Error_String = "NOTPROCESSED";        break; } 
		   case DMLERR_POKEACKTIMEOUT : 
					{ Error_String = "POKEACKTIMEOUT";      break; } 
		   case DMLERR_POSTMSG_FAILED : 
					{ Error_String = "POSTMSG_FAILED";      break; } 
		   case DMLERR_REENTRANCY : 
					{ Error_String = "REENTRANCY";          break; } 
		   case DMLERR_SERVER_DIED : 
					{ Error_String = "SERVER_DIED";         break; } 
		   case DMLERR_SYS_ERROR : 
					{ Error_String = "SYS_ERROR";           break; } 
		   case DMLERR_UNADVACKTIMEOUT :
					{ Error_String = "UNADVACKTIMEOUT";     break; } 
		   case DMLERR_UNFOUND_QUEUE_ID :
					{ Error_String = "UNFOUND_QUEUE_ID";    break; } 
			default:
				{
				String   Error_Number( 10, "", ' ' );
				_itoa( DDE_Error_Number, (char*)Error_Number, 10 );
      		Error_String = Error_Number;
				}
			
			} //end switch on error number
      String   Error_Msg( "DDE error: " );
		Error_Msg = Error_Msg 
                + Error_String 
                + ": "
                + MessageRef;
		MessageBox( NULL, Error_Msg, FunctionNameRef, MB_OK );		
      Error_Occured = TRUE;      
		}//end if error occured
   
	return   Error_Occured;   
   }