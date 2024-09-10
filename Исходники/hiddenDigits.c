int main(int argc, const char * argv[]) {
    FILE *file = fopen(argv[1], "r");
    char line[1024];
    while (fgets(line, 1024, file)) {
        
        int i = 0;
    	bool empty = true;
    
    	while (line[i])
    	{		
    		if (line[i] >= 'a' && line[i] <= 'j') 
    		{
    			printf("%d", toascii(line[i]) - 97);
    			empty = false;
    		}
    		if (line[i] >= '0' && line[i] <= '9')
    		{
    			empty = false;
    			printf("%c", line[i]);
    		}
    		i++;
    	}
    	if (empty) printf("NONE");
    	printf("\n");
    }
    return 0;
} 