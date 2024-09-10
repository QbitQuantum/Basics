/**
 * This function compares two variables. Input and output variables are
 * considered as text content. For dictionary variables, it's the inflected
 * form that is taken into account.
 *
 * Note 1: you can compare variables of different kinds
 * Note 2: you can compare a variable to a constant string. To do that, the string
 *         must start with #
 */
int compare_variables(const unichar* var1,const unichar* var2,struct locate_parameters* p,int case_matters) {
int free_v1;
unichar* v1=get_var_content_str(var1,p,&free_v1);
if (!v1) {
    return VAR_CMP_ERROR;
}
int free_v2;
unichar* v2=get_var_content_str(var2,p,&free_v2);
if (!v2) {
    if (free_v1) free(v1);
    return VAR_CMP_ERROR;
}
int ret=case_matters?u_strcmp(v1,v2):u_strcmp_ignore_case(v1,v2);
if (free_v1) free(v1);
if (free_v2) free(v2);
if (ret==0) {
    return VAR_CMP_EQUAL;
}
return VAR_CMP_DIFF;
}