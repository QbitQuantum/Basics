void updateCmd(char* cmdName,char* cmdValue) {
/* this function test the command ID matching 
 * and if a received command is valid, set the UARTCde[].ready variable at 1.
 * It is used to get the value of the new command*/

    unsigned char i;
    
        for(i=1;i<NB_CMD;i++) {

            if(strCmp(cmdName,commandID[i],3)) { 		//compare command ID with stored ID
                UARTCde[i].value=toShort(cmdValue);		//convert received value to a short and store it
                UARTCde[i].ready=1;
            }
        }
}