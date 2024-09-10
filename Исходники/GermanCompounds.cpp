//
// returns 1 if the INF code refers to a valid right component, 0 else
//
char check_valid_right_component_for_one_INF_code_german(const unichar* s) {
unichar temp[2000];
u_strcpy(temp,"x,");
u_strcat(temp,s);
struct dela_entry* d=tokenize_DELAF_line(temp,0);
char res=check_N_not_FF(d);
free_dela_entry(d);
return res;
}