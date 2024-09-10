static void test_EnumICMProfilesW( HDC dc )
{
    INT ret;

    ret = EnumICMProfilesW( NULL, NULL, 0 );
    ok(ret == -1 || broken(ret == 0) /* win9x, nt4 */, "expected -1, got %d\n", ret);

    ret = EnumICMProfilesW( dc, NULL, 0 );
    ok(ret == -1 || broken(ret == 0) /* win9x, nt4 */, "expected -1, got %d\n", ret);

    ret = EnumICMProfilesW( dc, enum_profiles_callbackW, 0 );
    ok(ret == -1 || broken(ret == 0) /* win9x, nt4 */, "expected -1, got %d\n", ret);
}