void increase_switch_nesting_level(ExecNode *e)
{
    ++switch_nesting_level;
    if (switch_nesting_level >= MAX_SWITCH_NEST)
        TERMINATE("error: too many nested switch statements (>= %d)", MAX_SWITCH_NEST);
    switch_case_counter[switch_nesting_level] = 1;
    switch_contr_expr_types[switch_nesting_level] = get_type_category(&e->type);
}