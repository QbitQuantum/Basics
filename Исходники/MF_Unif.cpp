//////////////////////////////////////////////////////////////////////////////////
// Desinstantiates the unification variable "var". 
int unif_desinstantiate(unif_vars_T* UNIF_VARS,unichar* var) {
  int v, w, found;

  found = 0;
  for (v=0; v<UNIF_VARS->no_vars; v++)
    if (!u_strcmp(var,UNIF_VARS->vars[v].id)) {
        found = 1;
        break;
    }
  // if found v points to the variable following the one we want to eliminate
  if (found) {
    free(UNIF_VARS->vars[v].id);
    for (w=v+1; w<UNIF_VARS->no_vars;w++)
    	UNIF_VARS->vars[w-1] = UNIF_VARS->vars[w];
    UNIF_VARS->no_vars--;
  }
  return 0;
}