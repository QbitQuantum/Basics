 //enum errorType WritePort(char *buff ,unsigned int num_to_write);  gsSerialPort definition
 errorType Write(GSIChar chr) {return(WritePort( (char *)&chr,1));}