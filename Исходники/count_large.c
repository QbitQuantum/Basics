int main(int argc, char *argv[])
{   
	/* System call shell command */
    
	system("ls -l >> assignment.txt");
    
    /* Read shell command results */

    char temp_hold[LENGTH];
    char permission_hold[LENGTH];
    char *filesize_hold;
    int permission_check = 0;
    int filesize_check = 0;
    char *delim = " ";
    int loop_control;
    char *permission_argv;
    int condition = 0;
    char *filesize_temp;
    int temp_int = 0;
    int flag = 0;


	FILE *fp;
	fp = fopen("./assignment.txt", "r");
    if(fp == NULL)
    {
    	printf("No Such File !!!\n");
    }
    fgets(temp_hold, STRING, fp);
    


	char *num = "1234567890";
	char *p;
    if(argc == 2)
    {  
       p = strpbrk(argv[1], num);
       if(!p)
       {  
          //Only Permission Check
       	  while(!feof(fp))
          {  
             flag = 2;
             fgets(temp_hold, STRING, fp);
             strcpy(permission_hold, strtok(temp_hold, delim));
             permission_argv = strndup(permission_hold+1, 9);
             condition = check_permission(permission_argv, argv[1]);
             if(condition == 1)
             {
                permission_check += 1;
             }

          }
       }
       else
       {  
          //Only Filesize Check
          while(!feof(fp))
          { 
            flag = 1;
            loop_control = 0;
            fgets(temp_hold, STRING, fp);
            filesize_hold = strtok_r(temp_hold, " ", &filesize_temp);
            while(filesize_hold != NULL)
            {   
                if(loop_control == 4)
                {
                   break;
                }
                filesize_hold = strtok_r(NULL, " ", &filesize_temp);
                loop_control++;
            }
            if(filesize_hold)
            {
                temp_int = atoi(filesize_hold);
                if(temp_int >= atoi(argv[1]))
                {
                    filesize_check += 1;

                }
            }
            
          }
       }
    }
    else if(argc == 3)
    {
         while(!feof(fp))
          {
            loop_control = 0;
            fgets(temp_hold, STRING, fp);
            filesize_hold = strtok_r(temp_hold, " ", &filesize_temp);
            while (filesize_hold != NULL)
            {   
                if(loop_control == 4)
                {
                   break;
                }
                filesize_hold = strtok_r(NULL, " ", &filesize_temp);
                loop_control++;
            }
            if(filesize_hold)
            {
                temp_int = atoi(filesize_hold);
                if(temp_int >= atoi(argv[1]))
                {
                    filesize_check += 1;

                }
            }
            
          }

        fclose(fp);

        FILE *fptr;
        fptr = fopen("./assignment.txt", "r");
        if(fptr == NULL)
        {
            printf("No Such File !!!\n");
        }
        fgets(temp_hold, STRING, fptr);
        while(!feof(fptr))
        {  
             fgets(temp_hold, STRING, fptr);
             strcpy(permission_hold, strtok(temp_hold, delim));
             permission_argv = strndup(permission_hold+1, 9);
             condition = check_permission(permission_argv, argv[2]);
             if(condition == 1)
             {
                permission_check += 1;
             }

        }
        fclose(fptr);

    }
    else if(argc == 1)
    {
    	printf("No argument !!\n");
    }
    permission_check = permission_check - 1;
    if(argc == 2)
    {
        if(flag == 1)
        {
           printf("%d \n", filesize_check);
        }
        if(flag == 2)
        {
           printf("%d \n", permission_check);
        }
    }
    if(argc == 3)
    {   
        if(filesize_check > permission_check)
        {
            printf("%d \n", permission_check);
        }
        else
        {
            printf("%d \n", filesize_check);
        }
    }

    return 0;
}