unsigned int Password_Test(char * str)
{
     unsigned int score = 0;
     unsigned int Upper_Count = 0;  // NmA 1
     unsigned int Lower_Count = 0;  // NmA 2
     unsigned int Number_Count = 0; // NmA 3
     unsigned int Symbol_Count = 0; // NmA 4

     unsigned int Num_middle_Alpha = 0;    
     unsigned int Num_middle_Alpha_prev = 0;
      
     unsigned int passwd_mid = 0;
     
     unsigned int Upper_repeat = 0;
     unsigned int Lower_repeat = 0;
     unsigned int Number_repeat = 0;
     unsigned int Symbol_repeat = 0;
     unsigned int Ascii_repeat = 0;    
     unsigned int CTT_repeat = 0;

     unsigned int AsciiCode_prev,AsciiCode_current;

     unsigned int len;
         
     
     AsciiCode_prev = -1;
     AsciiCode_current = -1;  
  
     len = strlen(str);  

     char * buffer = (char*)malloc(sizeof(char)*(len+1));
     strcpy(buffer,str);
            
     
    while((*str)!='\0'){
      if( isupper(*str)){
          
           Upper_Count++; 

           Num_middle_Alpha_prev = Num_middle_Alpha;
           Num_middle_Alpha = 1;

           AsciiCode_prev = AsciiCode_current;
           AsciiCode_current = (unsigned int)(*str);
         }
     else if( islower(*str)){
           
              Lower_Count++;
             
              Num_middle_Alpha_prev = Num_middle_Alpha;    
              Num_middle_Alpha = 2;

             AsciiCode_prev = AsciiCode_current;
           AsciiCode_current = (unsigned int)(*str);
         
         }
     else if( isdigit(*str)){
              Number_Count++;
             
              Num_middle_Alpha_prev = Num_middle_Alpha;
              Num_middle_Alpha = 3;

              AsciiCode_prev = AsciiCode_current;
           AsciiCode_current = (unsigned int)(*str);
        }
     else if( issymbol(*str)){
         Symbol_Count++;
         Num_middle_Alpha_prev = Num_middle_Alpha;
         Num_middle_Alpha = 4;

         AsciiCode_prev = AsciiCode_current;
           AsciiCode_current = (unsigned int)(*str);

        }
     

      /*--------------------------------------------------------------------*/
     if(Number_middle_Alpha(Num_middle_Alpha,Num_middle_Alpha_prev)){passwd_mid++;}

     /*--------------------Decersing Score------------------------------*/


     if(UpperAlpha(Num_middle_Alpha_prev,Num_middle_Alpha)){
         //  printf("Upper\n");
           Upper_repeat++;
     }
     if(LowerAlpha(Num_middle_Alpha_prev,Num_middle_Alpha)){
         //  printf("Lower\n");
          Lower_repeat++; 
      }    
     if(NumberRpt(Num_middle_Alpha_prev,Num_middle_Alpha)){
         Number_repeat++;
      }
     if(SymbolRpt(Num_middle_Alpha_prev,Num_middle_Alpha)){
         Symbol_repeat++;
      }

     Ascii_repeat = AsciiRpt(buffer);
      
      
      
     unsigned int end_or_not = *(str+1) == '\0' ? -1  : (unsigned int)(*(str+1));
     if( Continue_Three_Time(AsciiCode_prev,AsciiCode_current,end_or_not) ){
           CTT_repeat++;
      }
      str++;
    }



  /* printf("%u:%u:%u:%u:%u\n  %u:%u:%u:%u:%u:%u\n",Upper_Count,Lower_Count,Number_Count,Symbol_Count,passwd_mid,
                                                     Upper_repeat,Lower_repeat,Number_repeat,Symbol_repeat,Ascii_repeat,CTT_repeat);       */
     
   //------------------------------------day to Crack------------------------------------------------------//
   if(Upper_Count !=0 && Lower_Count!=0 && Number_Count!=0 && Symbol_Count!=0){my_pow(95,len);}

   else if(Upper_Count != 0 && Lower_Count != 0 && Number_Count!=0){my_pow(63,len);}
  
   else if(Upper_Count != 0 && Lower_Count != 0 && Symbol_Count!=0){my_pow(85,len);}
   
   else if(Upper_Count != 0 && Number_Count != 0 && Symbol_Count !=0){my_pow(69,len);}
   
   else if(Lower_Count != 0 && Number_Count != 0 && Symbol_Count!=0 ){my_pow(69,len);}

   else if(Upper_Count != 0 && Lower_Count !=0){my_pow(52,len);}
 
   else if(Upper_Count != 0 && Number_Count !=0){my_pow(36,len);}
   
   else if(Upper_Count !=0 && Symbol_Count!=0){my_pow(58,len);}

   else if(Lower_Count != 0 && Number_Count!=0){my_pow(36,len);}
   
   else if(Lower_Count != 0 && Symbol_Count!=0){my_pow(58,len);}
  
   else if(Symbol_Count != 0 && Number_Count!=0){my_pow(42,len);}

   else if(Upper_Count!=0){my_pow(26,len);}
   
   else if(Lower_Count!=0){my_pow(26,len);}

   else if(Symbol_Count!=0){my_pow(32,len);}

   else if(Number_Count!=0){my_pow(10,len);}
    
}