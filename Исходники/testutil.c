void initialize(void) {
    apr_initialize();
    atexit(apr_terminate);
    
    apr_pool_create(&p, NULL);
}