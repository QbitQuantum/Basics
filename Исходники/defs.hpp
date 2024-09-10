void PrintTime(){
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(time_buffer,64,"%x %H:%M:%S",timeinfo);//"%a %b %d %Y %X %z",timeinfo);
    printf(time_buffer);
}