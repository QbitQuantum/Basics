static void
lookup_complex(const atf_tc_t *tc, const char *mountpath)
{
	char pb[MAXPATHLEN];
	struct stat sb1, sb2;

	USES_DIRS;

	if (FSTYPE_UDF(tc))
		atf_tc_expect_fail("PR kern/49033");

	sprintf(pb, "%s/dir", mountpath);
	if (rump_sys_mkdir(pb, 0777) == -1)
		atf_tc_fail_errno("mkdir");
	if (rump_sys_stat(pb, &sb1) == -1)
		atf_tc_fail_errno("stat 1");

	sprintf(pb, "%s/./dir/../././dir/.", mountpath);
	if (rump_sys_stat(pb, &sb2) == -1)
		atf_tc_fail_errno("stat 2");

	if (memcmp(&sb1, &sb2, sizeof(sb1)) != 0) {
		printf("what\tsb1\t\tsb2\n");

#define FIELD(FN)	\
		printf(#FN "\t%lld\t%lld\n", \
		(long long)sb1.FN, (long long)sb2.FN)
#define TIME(FN)	\
		printf(#FN "\t%lld.%ld\t%lld.%ld\n", \
		(long long)sb1.FN.tv_sec, sb1.FN.tv_nsec, \
		(long long)sb2.FN.tv_sec, sb2.FN.tv_nsec)

		FIELD(st_dev);
		FIELD(st_mode);
		FIELD(st_ino);
		FIELD(st_nlink);
		FIELD(st_uid);
		FIELD(st_gid);
		FIELD(st_rdev);
		TIME(st_atim);
		TIME(st_mtim);
		TIME(st_ctim);
		TIME(st_birthtim);
		FIELD(st_size);
		FIELD(st_blocks);
		FIELD(st_flags);
		FIELD(st_gen);

#undef FIELD
#undef TIME

		atf_tc_fail("stat results differ, see ouput for more details");
	}
	if (FSTYPE_UDF(tc))
		atf_tc_fail("random failure of PR kern/49033 "
			    "did not happen this time");
}