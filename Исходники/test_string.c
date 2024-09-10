int main(int argc, const char *argv[])
{
    KonohaContext* konoha = CreateContext();
    int i;
    for (i = 0; i < 100; ++i) {
        test_kString(konoha);
    }
    DeleteContext(konoha);
    return 0;
}