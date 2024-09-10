int finalSanitation(int * vectorMap, char **argv, int bFlag, Array *Employees, Array *Guests) {
	
	char *curr = NULL;
		
	if (vectorMap[1] != 0) {  																				     // -K sanitize
		 	curr = argv[vectorMap[1]];
			while (*curr != 0) {
				if (!(isAlpha(curr) || isNum(curr))) {
					if (DEBUG) printf("-K value error! Only alphanumeric chars allowed!\n");  //REMOVE
					error(bFlag); 
					return 0;  		
				}   
				curr++;			
   		 }
   		}
   
      int iter = 0;
		for (iter; iter < Employees->used; ++iter) {
			if (DEBUG) printf("Sanitizing Employee number %d: %s\n", iter+1, argv[Employees->array[iter]]);
			curr = argv[Employees->array[iter]];
			while (*curr != 0) {
				if (!isAlpha(curr)) {
					if (DEBUG) printf("-E value error! Only alphabets chars allowed!\n");  //REMOVE
					error(bFlag); 
					return 0;  		
				}   
				curr++;			
   		 }
		}
		iter = 0;
		for (iter; iter < Guests->used; ++iter) {
			if (DEBUG) printf("Sanitizing Guest number %d: %s\n", iter+1, argv[Guests->array[iter]]);
			curr = argv[Guests->array[iter]];
			while (*curr != 0) {
				if (!isAlpha(curr)) {
					if (DEBUG) printf("-G value error! Only alphabets chars allowed!\n");  //REMOVE
					error(bFlag); 
					return 0;  		
				}   
				curr++;			
   		 }
		} 
		
		
		
		if (vectorMap[5] != 0) {  																				     // <log> sanitize
		 	curr = argv[vectorMap[5]];
			while (*curr != 0) {
				if (!(isAlpha(curr) || isNum(curr) || isUnderscore(curr) || *curr == '.' || *curr == '/')) {
					if (DEBUG) printf("<log> error! Only alphanumeric chars allowed and underscore(_)!\n");  //REMOVE
					error(bFlag);
					return 0;   		
				}   
				curr++;			
   		 }
   		}
		
		
	
 
   
   return 1;
}