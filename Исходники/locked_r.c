/* A function to fix the locked reactions by reading the optional argument -L */
int fix_locked (int n_locked, double *s, double **s_locked, double *lock_v, char *locked){
    
    char *l_index1 = locked, *l_index2, *l_index3, *copy1, *copy2;
    
    int locked_string_length = strlen( locked ), which, n_zeros=0;
    
    double l_value, **dummy_s = s_locked;
    
    
    /* if there is only one locked reaction */
    if ( n_locked == 1 ){
        
        /* cut the string at ":" separating the index of reaction to lock from the value to assign */
        l_index1 = strchr(locked, ':');
        
        /* copy the index bit of the string to a new string */
        copy1 = get_substring (locked, l_index1);
        
        /* get the index from the substring */
        which = atoll (copy1) - 1;
        
        /* get the value to assign from the rest of the string */
        l_value = atof (l_index1 + 1);
        
        /* if value = 0 flag that there is a null reaction*/
        if (l_value == 0.) n_zeros += 1;
        
        /* assign the pointer to the fixed reaction */
        *dummy_s = s + which;
        
        /* assign the value to the array of fixed values lock_v*/
        *lock_v = l_value;
        
        /* free the substring */
        free ( copy1 );
        
    }
    
    /* otherwise */
    else if ( n_locked > 1 ){
        
        /* for each fixed reaction (found through the ":")*/
        while ( (int) (l_index1 - locked) < locked_string_length + 1 && strchr(l_index1, ':') != NULL )  {
            
            /* find the substring containing the index of the reaction */
            l_index2 = strchr(l_index1, ':');
            
            /* find the substring containing the value to assign */
            l_index3 = strchr(l_index1, ',');
            
            /* if it is the last reaction there are no more "," - the value substring lasts till the end */
            if ( l_index3 == NULL ) l_index3 = locked + locked_string_length;
            
            /* copy the index substring to a new string */
            copy1 = get_substring (l_index1, l_index2);
            
            /* get the numerical index of the index */
            which = atoi (copy1) - 1;
            
            /* copy the value substring to a new string */
            copy2 = get_substring (l_index2 + 1 , l_index3);
            
            /* get the numerical value of the flux value */
            l_value = atof (copy2);
            
            /* if value = 0 flag that there is a null reaction*/
            if (l_value == 0.) n_zeros += 1;
            
            /* assign a pointer to the locked reaction */
            *dummy_s = s + which;
            
            /* assign the value to the array */
            *lock_v = l_value;
            
            /* free the first substring */
            free ( copy1 );
            
            /* free the second substring */
            free ( copy2 );
            
            /* get to next pointer to locked reactions */
            dummy_s++;
            
            /* get to next array element of locked values*/
            lock_v++;
            
            /* iterate over the whole string up to the next "," */
            l_index1 = l_index3 + 1;
            
        }
        
    }
    
    /* return the number of zero reactions*/
    /* useful to check the problem is solvable, i.e. no metabolite is consumed only */
    return n_zeros;
    
}