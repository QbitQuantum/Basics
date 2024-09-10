void test__getprotobynumber__int(void)
{
    struct test_struct {
	const char *	result;
	int		parameter;
    } test_unit[] = {
	{NULL,		-1},
	{"ip",		0},
	{"icmp",	1},
	{"tcp",		6},
	{"udp",		17},
	{"ipv6",	41},
	{"gre",		47},
	{"encap",	98},
	{"l2tp",	115},
    };
    char *ret;

    test_unit_count = sizeof(test_unit) / sizeof(test_struct);

    for (i = 0; i < test_unit_count; i++) {
	printf("test: %s(%d) = %s\n", function_name, test_unit[i].parameter, test_unit[i].result);
	ret = PHP.getprotobynumber(test_unit[i].parameter);

	assert((test_unit[i].result == ret || !strcmp(test_unit[i].result, ret)));
    }
}