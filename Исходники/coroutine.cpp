void coroutine_destroy(struct coroutine *co)
{
    _aligned_free(co);
}