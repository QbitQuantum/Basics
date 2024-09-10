struct schedule * coroutine_open(void) {
    struct schedule *S = (struct schedule*)malloc(sizeof(*S));
    S->nco = 0;
    S->cap = DEFAULT_COROUTINE;
    S->running = -1;
    S->co = (struct coroutine**)malloc(sizeof(struct coroutine *) * S->cap);
    memset(S->co, 0, sizeof(struct coroutine *) * S->cap);
    S->main = ConvertThreadToFiber(NULL);
    return S;
}