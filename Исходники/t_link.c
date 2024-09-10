ATF_TC_BODY(link_stat, tc)
{
	struct stat sa, sb;
	int fd;

	(void)memset(&sa, 0, sizeof(struct stat));
	(void)memset(&sb, 0, sizeof(struct stat));

	pathl = getpath();
	fd = open(path, O_RDWR | O_CREAT, 0600);

	ATF_REQUIRE(fd >= 0);
	ATF_REQUIRE(pathl != NULL);

	ATF_REQUIRE(link(path, pathl) == 0);
	ATF_REQUIRE(stat(path, &sa) == 0);
	ATF_REQUIRE(lstat(pathl, &sb) == 0);

	if (sa.st_uid != sb.st_uid)
		atf_tc_fail("unequal UIDs");

	if (sa.st_mode != sb.st_mode)
		atf_tc_fail("unequal modes");

	if (sa.st_ino != sb.st_ino)
		atf_tc_fail("unequal inodes");

	ATF_REQUIRE(close(fd) == 0);
	ATF_REQUIRE(unlink(path) == 0);
	ATF_REQUIRE(unlink(pathl) == 0);
}