////////////////////////////////////////////////////////////////////////////////////////////////
//Send the HEX command over the wire
int send_command(int cmd)
{
int loop;
printf("%i\n",cmd);
char data [4] = ""; //create the null.

for (loop =0; loop < 4; loop++)  //build the command string.
        data[loop] = command_list[cmd].command_hex[loop]; 
        
        if (!writeport(fd, data)){
                printf("write failed\n");  //something went horribly wrong.. 
                return -1;
                }
                
return 0;  
}