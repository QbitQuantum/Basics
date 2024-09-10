main(){
       char ori[100];
       
       printf("Digite um letra: ");
       scanf("%s",&ori);
       
       char des[100];
       printf("Digite um letra: ");
       scanf("%s",&des);
       
       strCpy(des,ori);
       printf("%s , %s",des,ori);
        
       
       getch();
       }