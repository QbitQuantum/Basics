char * getNextSection(struct _CMCIConnection * con)
{
	char * xmlb    = NULL;
  char * workptr = NULL;
  char * curptr  = NULL;
  int    xmlblen = 0;
  int    tagval  = 0;
  int    retcode = 0; 
  int    toval   = 0;
  
   /*
    * free that old buffer 
    */
  
  if(con->asynRCntl.escanInfo.section != NULL) {
     free(con->asynRCntl.escanInfo.section);
     con->asynRCntl.escanInfo.section = NULL ;
  }
  
  if((retcode = pthread_mutex_lock(&(con->asynRCntl.escanlock))) != 0){
     printf(" getNextSection pthread lock return code %d\n",retcode) ;	
  }
  
  /*
   * If we have no more new data from the server , we 
   * unlock and sleep then check till we see that we have 
   * received new data 
   */
  
  while(con->asynRCntl.escanInfo.prevtotl == con->asynRCntl.escanInfo.recdtotl){
     if((retcode = pthread_mutex_unlock(&(con->asynRCntl.escanlock))) != 0){
        printf(" getNextSection pthread lock return code %d\n",retcode) ;	
     }
     /* *******************************************
      * ******************************************* 
      * timeout toval keeps us from hanging forever
      * *******************************************
      * *******************************************
      */
     usleep(1000) ;
     toval++ ;

     if(toval>5000) 
         longjmp (save_env, 1);
     
     if(con->asynRCntl.escanInfo.prevtotl != con->asynRCntl.escanInfo.recdtotl){
     	  /* 
     	   * we got more data , exit this loop
     	   */
        if((retcode = pthread_mutex_lock(&(con->asynRCntl.escanlock))) != 0){
             printf(" getNextSection pthread lock return code %d\n",retcode) ;	
        }
        break;
     }   
  }

  if((con->asynRCntl.xfer_state == XFER_DATA_RECVD) ||
     (con->asynRCntl.xfer_state == XFER_COMPLETE)	)    {

     workptr = LASTPTR(&(con->asynRCntl.escanInfo)) ;
     curptr  = CURPTR(&(con->asynRCntl.escanInfo));
  
     con->asynRCntl.escanInfo.ssecoff = con->asynRCntl.escanInfo.curoff ;
     
     toval = 0;
     while(workptr > curptr) {   
        if(*workptr == '>'){
        	 tagval = checkTag(workptr , con->asynRCntl.eMethodType) ;
        	 if(tagval == 0){
              con->asynRCntl.escanInfo.curoff = con->asynRCntl.escanInfo.curoff + (workptr - curptr) + 1 ;
              xmlblen = ((workptr - curptr) + 5) ;
           
              xmlb = malloc(xmlblen + 64) ;
              con->asynRCntl.escanInfo.section = xmlb ;

              con->asynRCntl.escanInfo.sectlen = xmlblen + 5 ;
              memset(xmlb , 0x0cc , xmlblen + 5) ;
                                   
              if(xmlb != NULL){
                 memcpy(xmlb , SSECPTR(&con->asynRCntl.escanInfo) , xmlblen) ;
                 strcpy((xmlb+(xmlblen - 4)) , "<EC>") ;
                 con->asynRCntl.escanInfo.getnew = 0 ;
 
              } else {
           	     /* getNextSection xmlb is NULL !!! This is bad */
              }
                           
              con->asynRCntl.escanInfo.prevtotl = con->asynRCntl.escanInfo.recdtotl ;

              if((retcode =  pthread_mutex_unlock(&(con->asynRCntl.escanlock))) != 0){
              	 printf(" getNextSection pthread lock return code %d\n",retcode) ;	
              }
              return(xmlb) ;
          } else {
          	  /* 
          	   * backup before this tag 
          	   */
              workptr = workptr - tagval ;
              if(workptr <= curptr){
                 if (con->asynRCntl.escanInfo.prevtotl != con->asynRCntl.escanInfo.recdtotl){
                 	  pthread_mutex_unlock(&(con->asynRCntl.escanlock));
                 	  usleep(1000) ;
                 	  toval++ ;
                 	  if(toval > 5000)
                 	     longjmp (save_env, 2);
                 	  pthread_mutex_lock(&(con->asynRCntl.escanlock));
                    workptr = LASTPTR(&(con->asynRCntl.escanInfo)) ;
                    curptr  = CURPTR(&(con->asynRCntl.escanInfo));                	
                 }
              }
              continue;
          }
        } else {
           workptr-- ;
           if(workptr <= curptr){
              if (con->asynRCntl.escanInfo.prevtotl != con->asynRCntl.escanInfo.recdtotl){
                 workptr = LASTPTR(&(con->asynRCntl.escanInfo)) ;
                 curptr  = CURPTR(&(con->asynRCntl.escanInfo));
              }
           }
        }
     }
  }
  
  if((retcode =  pthread_mutex_unlock(&(con->asynRCntl.escanlock))) != 0){
     printf(" getNextSection pthread unlock return code %d\n",retcode) ;	
  }
  return(NULL) ;
}