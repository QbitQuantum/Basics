/**
 * Allocates, initializes and returns a new corpus_entry structure.
 */
struct corpus_entry* new_corpus_entry(const unichar* line){
struct corpus_entry* entry = (corpus_entry*)malloc(sizeof(corpus_entry));
if(entry == NULL){
	fatal_alloc_error("compute_corpus_entry");
}
/* we fill corpus entry with information extracted from the corpus line*/
int pos = u_strrchr(line,'/');
if(pos == -1){
	fatal_error("Wrong format for line %S\n",line);
}
entry->word = (unichar*)malloc(sizeof(unichar)*(pos+1));
if(entry->word == NULL){
	fatal_alloc_error("compute_corpus_entry");
}
unichar* tmp = u_strcpy_sized(entry->word,pos+1,line);
u_strcat(tmp,"\0");

int code_pos = u_strrchr(line,':');
/* there are no morphological codes associated to this entry */
if(code_pos == -1){
	entry->pos_code = (unichar*)malloc(sizeof(unichar)*(u_strlen(line)-pos));
	if(entry->pos_code == NULL){
		fatal_alloc_error("new_corpus_entry");
	}
	u_strcpy(entry->pos_code,&line[pos+1]);
	entry->overall_codes = u_strdup(entry->pos_code);
}
else{
	entry->pos_code = (unichar*)malloc(sizeof(unichar)*(code_pos-pos));
	if(entry->pos_code == NULL){
		fatal_alloc_error("new_corpus_entry");
	}
	entry->overall_codes = (unichar*)malloc(sizeof(unichar)*(u_strlen(line)-pos));
	if(entry->overall_codes == NULL){
		fatal_alloc_error("new_corpus_entry");
	}
	unichar* tmp2 = u_strcpy_sized(entry->pos_code,code_pos-pos,&line[pos+1]);
	u_strcat(tmp2,"\0");
	u_strcpy(entry->overall_codes,&line[pos+1]);
}
/* if the token is not annotated in the corpus, we put "UNK" */
if(u_strlen(entry->pos_code) == 0){
	free(entry->pos_code);
	free(entry->overall_codes);
	entry->pos_code = u_strdup("UNK");
	entry->overall_codes = u_strdup("UNK");
}
return entry;
}