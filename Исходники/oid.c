static void testOIDToAlgID(void)
{
    int i;
    DWORD alg;

    /* Test with a bogus one */
    alg = CertOIDToAlgId("1.2.3");
    ok(!alg, "Expected failure, got %d\n", alg);

    for (i = 0; i < sizeof(oidToAlgID) / sizeof(oidToAlgID[0]); i++)
    {
        alg = CertOIDToAlgId(oidToAlgID[i].oid);
        /* Not all Windows installations support all these, so make sure it's
         * at least not the wrong one.
         */
        ok(alg == 0 || alg == oidToAlgID[i].algID,
         "Expected %d, got %d\n", oidToAlgID[i].algID, alg);
    }
}