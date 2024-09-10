void fini_getenv_state(GETENV_STATE *state)
{
    FreeEnvironmentStringsW(state->environment_strings);
    state->environment_strings = state->next_string = NULL;
    erts_rwmtx_runlock(&environ_rwmtx);
}