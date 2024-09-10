int main(int argc, const char *argv[])
{
    KonohaContext* kctx = CreateContext();
    int i;
    void *malloced[100];
    for (i = 0; i < 100; ++i) {
        malloced[i] = PLATAPI GCModule.Kmalloc(0, i, NULL);
    }
    for (i = 0; i < 100; ++i) {
        PLATAPI GCModule.Kfree(0, malloced[i], i);
    }
    for (i = 0; i < 100; ++i) {
        malloced[i] = PLATAPI GCModule.Kzmalloc(0, i, NULL);
        int j;
        char *p = (char *)malloced[i];
        for (j = 0; j < i; ++j) {
            assert(p[0] == 0);
        }
    }
    for (i = 0; i < 100; ++i) {
        PLATAPI GCModule.Kfree(0, malloced[i], i);
    }
    DeleteContext(kctx);
    return 0;
}