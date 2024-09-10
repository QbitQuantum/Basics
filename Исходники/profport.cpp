static char * read_value (char *buff)
{  
    char * eq = strrchr (buff,'=');    /* Parse out the equal sign */
    if (eq) {
    	eq++;
    	while (*eq && isBlank(*eq))
    		eq++;
//    	return *eq ? eq : 0;
    	return eq;
    }
    return eq;
 }