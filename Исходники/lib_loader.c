bool ll_register_foreign_func(LibLoader *ll,
                              char *lisp_func,
                              char *c_func)
{
    PrimFunc *func;

    func = (PrimFunc *)LIBRARY_GETSYM(ll->_prev_handle, c_func);

#ifndef WIN32
    {
        char *error;

        if((error = dlerror()) != NULL) {
            OUTPUT_ERR("problem finding symbol: %s\n", error);
            return false;
        }
    }
#else
    if(func == NULL) {
        OUTPUT_ERR("problem opening function: %s in library\n", c_func);
        return false;
    }
#endif

    if(strcmp(ll->_mod_name, "None") == 0) {
        /* need to first convert to String */
        String tmp_w[MAX_FUNCTION_LEN];
        mbsrtowcs((wchar_t *)tmp_w,
                  (const char **)&lisp_func,
                  MAX_FUNCTION_LEN,
                  NULL);

        REGISTER_FUNC("foreign", (wchar_t*)tmp_w, func);
    } else {
        char tmp[MAX_FUNCTION_LEN];
        char *tmp_p = tmp;
        String tmp_w[MAX_FUNCTION_LEN];

        snprintf(tmp_p, MAX_FUNCTION_LEN,
                 "%s:%s", ll->_mod_name, lisp_func);

        /* need to first convert to String */
        mbsrtowcs((wchar_t*)tmp_w,
                  (const char **)&tmp_p,
                  MAX_FUNCTION_LEN,
                  NULL);

        REGISTER_FUNC("foreign", (wchar_t*)tmp_w, func);
    }
    
    return true;
}