static void test_TTIsEmbeddingEnabledForFacename(void)
{
    BOOL status;
    LONG ret;

    ret = TTIsEmbeddingEnabledForFacename(NULL, NULL);
    ok(ret == E_FACENAMEINVALID, "got %#x\n", ret);

    status = 123;
    ret = TTIsEmbeddingEnabledForFacename(NULL, &status);
    ok(ret == E_FACENAMEINVALID, "got %#x\n", ret);
    ok(status == 123, "got %d\n", status);

    ret = TTIsEmbeddingEnabledForFacename("Arial", NULL);
    ok(ret == E_PBENABLEDINVALID, "got %#x\n", ret);

    status = 123;
    ret = TTIsEmbeddingEnabledForFacename("Arial", &status);
    ok(ret == E_NONE, "got %#x\n", ret);
    ok(status != 123, "got %d\n", status);
}