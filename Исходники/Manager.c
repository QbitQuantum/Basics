int main(int argc,char **argv)
{
    key_t keysem,keyque1,keyque2,keyque3;
    struct sembuf wait1,signal1;
    pid_t managerPID = getpid();
    MESSAGE msg;
    pid_t allPID[10];
    for(i=0;i<2*COUNT;++i)
        {
            for(j=0;j<2;++j)
            {
                matrix_array[i][j] = '0';
            }
            matrix_array[i][j] = '\0';
        }

    FILE * f;
    f = fopen("./matrix.txt","w");
    for(i=0;i<2*COUNT;++i)
    {
        fprintf(f, "%s\n",matrix_array[i]);
    }
    fclose(f);
    signal(SIGUSR1,produce);
    signal(SIGUSR2,consume);
    signal(SIGINT,delete_all);
    if(argc < 2)
    {
        printf("Incorrect Arguments\n");
        printf("Enter the type of process\n");
    }
    int type = atoi(argv[1]);
    wait1.sem_num = 0;
    wait1.sem_op = -1;
    wait1.sem_flg = 0;

     signal1.sem_num = 0;
    signal1.sem_op = 1;
    signal1.sem_flg = 0;


    keysem = ftok(".", 'M');
    int nsem=9;
    semID=semget(keysem, nsem, IPC_CREAT|0666);

    
    ushort val[11] = {1, 1, 1, 1, 1, 10, 0, 10, 0};
// 0 mutex file 1,2 mutex producer q1,q2  3,4 mutex consumer q1,q2 5,6 full,empty q1 7,8 full,empty q2  
    semctl(semID, 0, SETALL, val);

    
    keysem = ftok(".", '1');
    if((mID1 = msgget(keysem, IPC_CREAT | 0660))<0){
        printf("Error Creating Message Queue1\n");
        exit(-1);
    }
    
    
    keysem = ftok(".", '2');
    if((mID2 = msgget(keysem, IPC_CREAT | 0660))<0){
        printf("Error Creating Message Queue2\n");
        exit(-1);
    }
//Creating the producers and consumers
    i=0,j=0;
    while(i<COUNT)
    {
        char parameter1[10],parameter2[10];
        sprintf(parameter1,"%d",managerPID);
        sprintf(parameter2,"%d",i);
        if((allPID[j++] = fork()) == 0)
            {
                int execpro = execl("./producer","./producer",parameter1,parameter2,(const char*) NULL);
                if(execpro <0 ) perror("Error in making producer");
                exit(0);
            }
        i++;
    }
    i=0;
    while(i<COUNT)
    {
        char parameter1[10],parameter2[10];
        sprintf(parameter1,"%d",managerPID);
        sprintf(parameter2,"%d",i);
        if((allPID[j++] = fork()) == 0)
            {
                int execcon = execl("./consumer","./consumer",parameter1,parameter2,argv[1],(const char*) NULL);
                if(execcon < 0) perror("Error in making consumer");
                exit(0);
            }
        i++;
    }
    i=0,j=0;

     while(1)
     {
        sleep(2);
        semop(semID,&wait1,1);
        fp = fopen("matrix.txt", "r");
        if(fp == NULL){
            perror("fopen");
        }
        ssize_t read;
        char *line = NULL;
        size_t len = 0; 
        i=0,j=0;
        while ((read=getline(&line, &len, fp)) != -1)
        {
            // printf("line in manager= %s\n",line);
            for(i=0;i<2;++i)
            {
                matrix_array[j][i] = line[i];
            }
            j++;
        }
        fclose(fp);
        semop(semID,&signal1,1);
        // for(i=0;i<10;++i)
        // {
        //     for(j=0;j<2;++j)
        //     {
        //         printf("%c",matrix_array[i][j]);
        //     }
        //     printf("\n");
        // }
        makeResourceGraph();
        // for(i=0;i<12;++i)
        // {
        //     for(j=0;j<12;++j)
        //     {
        //         printf("%d",graph[i][j]);
        //     }
        //     printf("\n");
        // }
        int flag = checkDeadlock();
        semctl(semID, 0, GETALL, val);     
        if(flag == 1){
            // printf("Deadlock Detected\n");
             for(i=0;i<2*COUNT;++i)
            {
                kill(allPID[i],SIGKILL);
            }
            break;
        }   
    }
    fp = fopen("result.txt", "a");
    if(fp == NULL){
        perror("fopen");
    }
    fprintf(fp,"produce_count = %d consume_count = %d \n",produce_count,consume_count);
    fclose(fp);

    delete_all();
    return 0;
}