void test_odb_largefiles__read_header(void)
{
	git_oid oid;
	size_t len;
	git_otype type;

#ifndef GIT_ARCH_64
	cl_skip();
#endif

	if (!cl_is_env_set("GITTEST_INVASIVE_FS_SIZE") ||
		!cl_is_env_set("GITTEST_SLOW"))
		cl_skip();

	writefile(&oid);
	cl_git_pass(git_odb_read_header(&len, &type, odb, &oid));

	cl_assert_equal_sz(LARGEFILE_SIZE, len);
	cl_assert_equal_i(GIT_OBJ_BLOB, type);
}