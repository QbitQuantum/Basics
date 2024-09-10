void decompose(char* in,char* wr,Decomposed_word **morph_list, Dictionary    dict){

	char *o;
	char tempstr[MDWL];
	int i;
	Decomposed_word  *morph_node;
 	o=(char *) xalloc(MAX_WORD*sizeof(char));
	strcpy(o,"");
 	for (i=0;wr[i]!='\0';i++){
		o=strncat(o,wr+i,1);
		if (dictionary_lookup(dict, o))
		{
          strcpy(tempstr,in);
		  strcat(in," ");
          strcat(in,o);
		  decompose(in, wr+i+1,morph_list, dict);
          strcpy(in,tempstr);
		}
	}
	if ((wr[0]=='\0')&&(in[0]))	{

		morph_node=(Decomposed_word *) xalloc(sizeof(Decomposed_word));
		strcpy(morph_node->word,in);
		morph_node->next = (*morph_list);
		if(*morph_list!=NULL){
			(*morph_list)->prev=morph_node;
		}
		(*morph_list)=morph_node;

	}
	xfree(o,MAX_WORD*sizeof(char));
}