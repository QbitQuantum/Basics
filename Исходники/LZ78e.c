unsigned char* PrintDict(dict_t *dict, unsigned int total_index){	
	dict_t *dict_ptr = dict;
	dict_t *temp_ptr;

	/* calculating needed allocated memory */
	size_t factor_size = WIDTH_DATA + WIDTH_INDEX;
	size_t total_size = factor_size * total_index;
	total_size = total_size + WIDTH_HEADER;
	
	/* allocating and checking for memory */
	unsigned char* output_stream = (unsigned char*) malloc(total_size);
	assert(output_stream != NULL);	
	
	unsigned char* index_char;
	
	int i = 0, j = 0;
	
	/* creating header bytes for output */
	index_char = HeaderDictSize(total_index);
	while(j < WIDTH_HEADER - 1){
		output_stream[j] = index_char[j];
		j++;
	}
	/* freeing memory */
	free(index_char);

	output_stream[j] = (unsigned char) WIDTH_DATA;
	j++;
	output_stream[j] = (unsigned char) WIDTH_INDEX;
	j++;

	/* appending dictionary for output */
	while(dict_ptr != NULL){
		index_char = IntToChar(dict_ptr->parent_index); 
		while(i < 4){
			if(i == 0){
				output_stream[j+i] = dict_ptr->node->data;
			}
			else{
				output_stream[j+i] = index_char[i-1];
			}
			i++;
		}
		temp_ptr = dict_ptr;
		dict_ptr = dict_ptr->next;
		
		/* freeing memory */
		free(index_char);
		index_char = NULL;
		free(temp_ptr->node);
		temp_ptr->node = NULL;
		free(temp_ptr);
		temp_ptr = NULL;
	
		i = 0;
		j += 4;
	}

	/* NULL-dereferencing for safety */
	dict_ptr = NULL;
	return output_stream;
}