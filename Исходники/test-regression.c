void test_join_restricted_process()
{
	pfq_t * x = pfq_open_group(Q_CLASS_DEFAULT, Q_POLICY_GROUP_RESTRICTED, 64, 1024, 1024);
	pfq_t * z = pfq_open_group(Q_CLASS_DEFAULT, Q_POLICY_GROUP_SHARED, 64, 1024, 1024);

	assert(x);
	assert(z);

	int p = fork();
	if (p == 0) {
		pfq_t * y = pfq_open_group(Q_CLASS_DEFAULT, Q_POLICY_GROUP_UNDEFINED, 64, 1024, 1024);

		int gid = pfq_group_id(z);
		assert( pfq_join_group(y, gid, Q_CLASS_DEFAULT, Q_POLICY_GROUP_SHARED) == gid);
		assert( pfq_join_group(y, pfq_group_id(x), Q_CLASS_DEFAULT, Q_POLICY_GROUP_SHARED) == -1);

		pfq_close(y);

		_Exit(1);
	}

	wait(NULL);

	pfq_close(x);
	pfq_close(z);
}