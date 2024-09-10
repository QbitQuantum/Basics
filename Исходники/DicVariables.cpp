/**
 * Sets the given dic variable, inserting it in the variable list if absent.
 */
void set_dic_variable(const unichar* name,struct dela_entry* dic_entry,struct dic_variable* *list,int must_clone) {
while (*list!=NULL) {
   if (!u_strcmp((*list)->name,name)) {
      /* If we have found the variable we were looking for */
      /* We have to free the previous value */
      free_dela_entry((*list)->dic_entry);
      if (must_clone) {
    	  (*list)->dic_entry=clone_dela_entry(dic_entry);
      } else {
    	  (*list)->dic_entry=dic_entry;
      }
      return;
   }
   list=&((*list)->next);
}
*list=new_dic_variable(name,dic_entry,NULL,must_clone);
}