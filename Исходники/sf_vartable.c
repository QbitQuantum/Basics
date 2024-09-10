int main()
{
    vartable_t *table;
    sfip_var_t *var;
    sfip_t *ip;

    puts("********************************************************************");
    puts("Testing variable table parsing:");
    table = sfvt_alloc_table();
    /* These are all valid */
    TEST(sfvt_add_str(table, "foo [ 1.2.0.0/16, ffff:dead:beef::0 ] ", &var) == SFIP_SUCCESS);
    TEST(sfvt_add_str(table, " goo [ ffff:dead:beef::0 ] ", &var) == SFIP_SUCCESS);
    TEST(sfvt_add_str(table, " moo [ any ] ", &var) == SFIP_SUCCESS);

    /* Test variable redefine */
    TEST(sfvt_add_str(table, " goo [ 192.168.0.1, 192.168.0.2, 192.168.255.0 255.255.248.0 ] ", &var) == SFIP_DUPLICATE);

    /* These should fail since it's a variable name with bogus arguments */
    TEST(sfvt_add_str(table, " phlegm ", &var) == SFIP_FAILURE);
    TEST(sfvt_add_str(table, " phlegm [", &var) == SFIP_FAILURE);
    TEST(sfvt_add_str(table, " phlegm [ ", &var) == SFIP_FAILURE);
    TEST(sfvt_add_str(table, " phlegm [sdfg ", &var) == SFIP_FAILURE);
    TEST(sfvt_add_str(table, " phlegm [ sdfg, 12.123.1.4.5 }", &var) == SFIP_FAILURE);
    TEST(sfvt_add_str(table, " [ 12.123.1.4.5 ]", &var) == SFIP_FAILURE);
    TEST(sfvt_add_str(table, NULL, &var) == SFIP_FAILURE);
    TEST(sfvt_add_str(table, "", &var) == SFIP_FAILURE);

    puts("");
    puts("********************************************************************");
    puts("Expansions:");
    /* Note: used this way leaks memory */
    printf("\t%s\n", sfvt_alloc_expanded(table, "$foo"));
    printf("\t%s\n", sfvt_alloc_expanded(table, "goo $goo sf sfasdfasdf $moo"));
    printf("\t%s\n", sfvt_alloc_expanded(table, " ssdf $moo $moo asdf $fooadff $foo "));
    printf("\t%s\n", sfvt_alloc_expanded(table, " ssdf $moo $moo\\sdf $foo adff"));

    puts("");
    puts("********************************************************************");
    puts("Containment checks:");
    var = sfvt_lookup(table, "goo");
    ip = sfip_alloc("192.168.248.255");
    TEST(sfvar_ip_in(var, ip) == SFIP_SUCCESS);

    /* Check against the 'any' variable */
    var = sfvt_lookup_var(table, "moo");
    TEST(sfvar_ip_in(var, ip) == SFIP_SUCCESS);

    /* Verify it's not in this variable */
    var = sfvt_lookup_var(table, "foo");
    TEST(sfvar_ip_in(var, ip) == SFIP_FAILURE);

    /* Check boundary cases */
    var = sfvt_lookup_var(table, "goo");
    free_ip(ip);
    ip = sfip_alloc_str("192.168.0.3");
    TEST(sfvar_ip_in(var, ip) == SFIP_FAILURE);
    free_ip(ip);
    ip = sfip_alloc_str("192.168.0.2");
    TEST(sfvar_ip_in(var, ip) == SFIP_SUCCESS);


    puts("");
    puts("********************************************************************");

    printf("\n\tTotal Failures: %d\n", failures);
    return 0;
}