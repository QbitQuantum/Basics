//
// FUNCTION NAME: SIM_End_Transaction
//
// DESCRIPTION: this is a wrapper for pcsclite SCardEndTransaction function.
//              Its job is to call that function and manage error messages
//              eventually returned.
//
// INPUT PARAMETERS: 
//   SCARDHANDLE  hCard    connection handler for this card.
//
// OUTPUT PARAMETERS:
//   None.
//
// NOTES:
//   -  Possible extension will require additional parameters to be chosen by
//      the caller.
//
void SIM_End_Transaction(SCARDHANDLE hCard) {
  LONG rv;

  rv = SCardEndTransaction(hCard, SCARD_LEAVE_CARD);
  switch(rv) {
    case SCARD_E_READER_UNAVAILABLE: {
      bail(EXIT_FAILURE, "SIM_End_Transaction:",ERR_READER_REMOVED);
    }
    case SCARD_E_SHARING_VIOLATION: {
      bail(EXIT_FAILURE, "SIM_End_Transaction:",ERR_SHARING_VIOLATION);
    }
    case SCARD_E_INVALID_HANDLE: {
      bail(EXIT_FAILURE, "SIM_End_Transaction:",ERR_INVALID_CONTEXT_HANDLER);
    }
    case SCARD_S_SUCCESS: {
      printf("TRANSACTION SUCCESSFULLY CLOSED.\n");
      break;
    }
    default: {
      bail(EXIT_FAILURE, "SIM_End_Transaction:",ERR_WRONG_RETURN_VALUE);
    }
  }
}