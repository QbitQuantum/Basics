int main()
{
     FILE *pFile = NULL;
     int lineCnt = 0;
     int i = 0;
     ipList_t* ipList = NULL;

    /*thread pool 갯수 지정 */
     threadpool thpool = thpool_init(THREAD_CNT);

    /* 읽을 파일의 라인수를 체크 */
    lineCnt = lineCount(CHECKLIST_FILE_PATH);

    printf("lineCnt :[%d] \n",lineCnt);

    ipList = (ipList_t*)malloc(sizeof(ipList_t)*(lineCnt+10));
    memset(ipList,0x00, sizeof(ipList_t)*(lineCnt+10));
   
   
    pFile = fopen( CHECKLIST_FILE_PATH, "r" );
    
    if( pFile != NULL )
    {
        char strTemp[255];
        char *pStr;

        while( !feof( pFile ) )
        {
            char* ss = NULL;
            pStr = fgets( strTemp, sizeof(strTemp), pFile ); 
			
            printf( "pStr:[%s] \n", pStr );
            printf( "strTemp:[%s] \n", strTemp );

            if(pStr != NULL)
            {
                pStr = rtrim(pStr);
                char* trimStr;

                //strncpy((ipList+i)->ip, pStr, STR_LEN); //ipList+0 번째가 깨진다.
                strcpy((ipList+i)->ip, pStr);
                 i++;
                
            }
        }

        fclose( pFile );
    }

    for(i =0 ;i < lineCnt;i++)
    {
        printf("ipList[%d]:[%s] \n",i,(ipList+i)->ip);
        thpool_add_work(thpool, (void*)pingChk, (ipList+i)->ip);
    }

    

    thpool_wait(thpool);

    thpool_destroy(thpool);

    free(ipList);

#if 0
    pthread_t p_thread[THREAD_CNT]; 
    int thr_id; //쓰레드ID
    int status;

    //char p1[] = "thread_1";   // 1번 쓰레드 이름
    //char p2[] = "thread_2";   // 2번 쓰레드 이름
    //char pM[] = "thread_m";   // 메인 쓰레드 이름
 
        // 파일 읽기
        if(fRead() == ERROR)
        {
            printf("FRead Error \n");        }
        Fread();





    sleep(2);  // 2초 대기후 쓰레드 생성
 


    sys

    // ① 1번 쓰레드 생성
    // 쓰레드 생성시 함수는 t_function
    // t_function 의 매개변수로 p1 을 넘긴다.  
    thr_id = pthread_create(&p_thread[0], NULL, t_function, (void *)p1);

    // pthread_create() 으로 성공적으로 쓰레드가 생성되면 0 이 리턴됩니다
    if (thr_id < 0)
    {
        perror("thread create error : ");
        exit(0);
    }
 
    // ② 2번 쓰레드 생성
    thr_id = pthread_create(&p_thread[1], NULL, t_function, (void *)p2);
    if (thr_id < 0)
    {
        perror("thread create error : ");
        exit(0);
    }
 
    // ③ main() 함수에서도 쓰레드에서 돌아가고 있는 동일한 함수 실행
    //t_function((void *)pM);
 
    // 쓰레드 종료를 기다린다. 
    pthread_join(p_thread[0], (void **)&status);
    pthread_join(p_thread[1], (void **)&status);
 
    printf("언제 종료 될까요?\n");
 #endif

    return SUCCESS;
}