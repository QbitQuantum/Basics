/**
 * Returns 1 if the line is a valid right "A" component.
 */
char check_A_right_component(unichar* s) {
/* We produce an artifical dictionary entry with the given INF code,
 * and then, we tokenize it in order to get grammatical and inflectional
 * codes in a structured way. */
unichar temp[2000];
u_strcpy(temp,"x,");
u_strcat(temp,s);
struct dela_entry* d=tokenize_DELAF_line(temp,0);
unichar t1[2];
u_strcpy(t1,"A");
unichar t2[4];
u_strcpy(t2,"sie");
char res=dic_entry_contain_gram_code(d,t1) && !dic_entry_contain_inflectional_code(d,t2);
/* We free the artifical dictionary entry */
free_dela_entry(d);
return res;
}