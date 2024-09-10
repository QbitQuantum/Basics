DWORD WINAPI ProcWaitSignal( LPVOID lpParam){
	while(1){
		printf("checking queue\n");
        Sleep(1000);
        if (NbElmt != 0){
        	if ((!IsUpper(buf)) && (!IsLower(buf))) {
	            printf("Mengonsumsi ke - %d : %c\n", ind, buf.TI[ind]);
	            ind++;
	            NbElmt--; // konsumsi buffer            
	        } else if (IsUpper(buf)) {
	           	SendXOFF();
	           	printf("Masuk Upper limit\n");
	            printf("Mengonsumsi ke - %d : %c\n", ind, buf.TI[ind]);
	            ind++;
	            NbElmt--; // konsumsi buffer
	        } else if (IsLower(buf)) {
	            SendXON();
	            printf("Masuk Lower limit\n");
	            // no consume0
	        }
        }
        
	}
	return 0;
};