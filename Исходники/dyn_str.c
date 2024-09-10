void dyn_str_print_reverse(DynStr *dyn_str, FILE *fp) {
    wchar_t *current_ptr = dyn_str_ptr_to_last_char(dyn_str);

    while (current_ptr >= dyn_str->content) {
        fputwc(*current_ptr, fp);
        current_ptr--;
    }
}