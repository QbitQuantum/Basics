//----------------------------
int main(int argc, char* argv[])
{
	// Declare our dll variable 
    char dll[MAX_PATH]; 

	if ( argc != 3 ) {
		cout << "Usage :" << argv[0] << " <PROCESS NAME> <DLL FULL PATH>" << endl;
		exit(1);
	}
	
    // Get the full path of our .dll 
	GetFullPathName( argv[2] , MAX_PATH, dll , NULL);  
	
	// Get PID of notepad.exe		
	DWORD ID = GetProcessId(argv[1]); 
    
	if (!CreateRemoteThreadInject(ID, dll)) {
		
        //If CreateRemoteThreadInject Returned true 
        cout << "Injection failed!" << endl ; 
        exit(1); 
         

    } else {
		
        //If CreateRemoteThreadInject Returned true 
        cout << "Injection of" << argv[2] << " into " << argv[1]  << " is successful!" << endl; 
        exit(1); 
    
	} 
    
	return 0;
}