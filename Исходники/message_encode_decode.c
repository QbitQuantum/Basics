char *code_message(msg *a){
    char *coded_msg=(char *)malloc(sizeof(int)*5+sizeof(double)+300*sizeof(char)+20);
    coded_msg[0]='\0';
    char num[10];
  
   	snprintf(num,10,"%d",a->sender_id);
    strcat(coded_msg,num);
    strcat(coded_msg," ");
  
    snprintf(num,10,"%d",a->receiver_id);
    strcat(coded_msg,num);
    strcat(coded_msg," ");
  
	snprintf(num,10,"%d",a->msg_type);
    strcat(coded_msg,num);
    strcat(coded_msg," ");	    


    int dec_pl,sign;
    strcat(coded_msg,fcvt((double) a->timestamp, 0, &dec_pl, &sign));
    strcat(coded_msg," ");
    
    snprintf(num,10,"%d",a->coming_from);
    strcat(coded_msg,num);
    strcat(coded_msg," ");      
  

    snprintf(num,10,"%d",a->message_id);
    strcat(coded_msg,num);
    strcat(coded_msg," ");

    strcat(coded_msg," ");
    strcat(coded_msg,a->message);
  
 // 	puts("This is encoded string:");
 // 	puts(coded_msg);
    return coded_msg;
}