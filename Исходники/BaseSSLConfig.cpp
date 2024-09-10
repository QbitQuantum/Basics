void ssl_lock_dyn_destroy_callback(CRYPTO_dynlock_value* l, const char *file, int line) {
    DeleteCriticalSection(&l->lock);
    free(l);
}