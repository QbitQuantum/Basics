int main()
{
 printf("In getSystemBootTime\n");                                                                                                            
        char var[48];                                                                                                                         
        FILE *fp = NULL;                                                                                                                      
        struct tm tm;
	time_t t;
  	struct timeval tv;

        #define CMD "date -d @$(sed -n '/^btime /s///p' /proc/stat)"                                                               
                                                                  
	memset(var,0,48);                                                                           
        fp = popen(CMD, "r");                                                                                                                
        while (fgets(var, sizeof(var), fp) != NULL)                                                                                         
        {                                                                                                                                    
                printf("%s", var);                                                                                                           
        }                                                                                                                                    
        pclose(fp);                                                                                                                           
                                                                                                                                               
	strptime(var, "%A %b %d %H:%M:%S %Z %Y", &tm);
	
	t = mktime(&tm);
 	tv.tv_sec = t;
 	tv.tv_usec = 0;
	
	printf("######################### %llu\n",getfiletime(&tv));
	return 0;
}