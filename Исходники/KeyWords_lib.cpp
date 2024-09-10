/**
 * Loads a compound word file, adding each word to the keywords.
 */
void load_compound_words(char* name,VersatileEncodingConfig* vec,
		struct string_hash_ptr* keywords) {
U_FILE* f=u_fopen(vec,name,U_READ);
if (f==NULL) return;
Ustring* line=new_Ustring(256);
Ustring* lower=new_Ustring(256);
while (EOF!=readline(line,f)) {
	if (line->str[0]=='{') {
		/* We skip tags */
		continue;
	}
	u_strcpy(lower,line->str);
	u_tolower(lower->str);
	int index=get_value_index(lower->str,keywords,INSERT_IF_NEEDED,NULL);
	if (index==-1) {
		fatal_error("Internal error in load_tokens_by_freq\n");
	}
	KeyWord* value=(KeyWord*)keywords->value[index];
	add_keyword(&value,line->str,1);
	keywords->value[index]=value;
}
free_Ustring(line);
free_Ustring(lower);
u_fclose(f);
}