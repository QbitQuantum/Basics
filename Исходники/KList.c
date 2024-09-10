VOID 
ShowNTError( 
	LPSTR szAPI, 
	NTSTATUS Status 
	) 
{     
    // 
    // Convert the NTSTATUS to Winerror. Then call ShowLastError().     
    // 
    ShowLastError(szAPI, LsaNtStatusToWinError(Status));
} 