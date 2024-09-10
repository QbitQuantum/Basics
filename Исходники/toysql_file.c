void lex(FILE *fp) {    
   
   int i=0;
   char *toktype=0;	
   char token[MAXLEN];
   
   int curr_char = fgetc(fp);	
        	   
  while (curr_char != '\0') {         
	
  if ( isspace(curr_char) ) { 
        curr_char = fgetc(fp);
       }
            	
  else if (isalpha(curr_char) || curr_char=='_')  { 	 
     while ( (isalnum(curr_char) || curr_char=='_') 
         && i<MAXLEN ) { 		  
		    token[i] = curr_char;
		    curr_char = fgetc(fp);	
		    i++;	  
		}   	
		
    if (search(kw_strings, NUMBER_OF_KEYWORDS, token) == 1 )
           toktype = "Keyword";
    else
           toktype = "Identifier";  		
				
   token[i] = '\0' ;   
   
   parse(token, toktype);   							         
   memset(&token[0], 0, sizeof(token));  // Clear token          
   }  // Keyword or identifier 

      
 else if ( curr_char == '"' ) { 
	   token[i] = curr_char;
	   curr_char = fgetc(fp);  	 
	   i++;	 
	    while ( ( curr_char != '"') && curr_char != '\0' 
	      && i<MAXLEN) {	   	    
			token[i] = curr_char;
		    curr_char = fgetc(fp); 		    
		    i++;	 
          } 
     token[i] = curr_char;  // Append the last quote. 
     token[i+1] = '\0' ;    // Append null char. 
     curr_char = fgetc(fp);	 // Move on from last quote. 
     toktype = "String" ;  
      
     parse(token, toktype); 
     memset(&token[0], 0, sizeof(token));  // Clear token          
   }  // String 	         
	         
	         
   else if ( isdigit(curr_char) )  { 
	  	while (isdigit(curr_char) && curr_char != '\0' 
	  	   && i<MAXLEN) { 	
 			token[i] = curr_char; 			   		    
		    curr_char = fgetc(fp); 		    		    
		    i++;	 
        }    
   toktype = "Number" ;   
   
   parse(token, toktype); 
   memset(&token[0], 0, sizeof(token));  // Clear token          
   }  // Number   	   	         
  	         
  	         
   else if ( ispunct(curr_char) && curr_char != '_' 
        && curr_char != '"' ) { 
		     token[i] = curr_char;
		     curr_char = fgetc(fp); 		
		     i++;	 	
      while (ispunct(curr_char) && curr_char != '\0' 
        && i<MAXLEN) {   
		       token[i] = curr_char;      				  
		       curr_char = fgetc(fp);		   
		       i++;	   	    	 	      
	        }		 
   toktype = "Punct" ;  
   
   parse(token, toktype); 
   memset(&token[0], 0, sizeof(token));  // Clear token           
   }  // Punct 
   
   else {	      
	       exit(0); 
	    }   	    
   memset(&token[0], 0, sizeof(token));  // Clear token   
   i = 0;  // Reset i.     	    	    
   }  // while c != '\0'   
    
   exit(0) ;  
    
}  // lex()  