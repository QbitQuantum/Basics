static void
h_check(int test)
{
	struct sigaction sa;
	jmp_buf jb;
	sigjmp_buf sjb;
	sigset_t ss;
	int i, x;

	myself = pthread_self();
	i = getpid();

	if (test == TEST_SETJMP || test == TEST_SIGSETJMP_SAVE)
		expectsignal = 0;
	else if (test == TEST_U_SETJMP || test == TEST_SIGSETJMP_NOSAVE)
		expectsignal = 1;
	else
		atf_tc_fail("unknown test");

	sa.sa_handler = aborthandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	REQUIRE_ERRNO(sigaction(SIGABRT, &sa, NULL) != -1);
	REQUIRE_ERRNO(sigemptyset(&ss) != -1);
	REQUIRE_ERRNO(sigaddset(&ss, SIGABRT) != -1);
	REQUIRE_ERRNO(sigprocmask(SIG_BLOCK, &ss, NULL) != -1);
	ATF_REQUIRE(myself == pthread_self());

	if (test == TEST_SETJMP)
		x = setjmp(jb);
	else if (test == TEST_U_SETJMP)
		x = _setjmp(jb);
	else 
		x = sigsetjmp(sjb, !expectsignal);

	if (x != 0) {
		ATF_REQUIRE(myself == pthread_self());
		ATF_REQUIRE_MSG(x == i, "setjmp returned wrong value");
		kill(i, SIGABRT);
		ATF_REQUIRE_MSG(!expectsignal, "kill(SIGABRT) failed");
		ATF_REQUIRE(myself == pthread_self());
		atf_tc_pass();
	}

	ATF_REQUIRE(myself == pthread_self());
	REQUIRE_ERRNO(sigprocmask(SIG_UNBLOCK, &ss, NULL) != -1);

	if (test == TEST_SETJMP)
		longjmp(jb, i);
	else if (test == TEST_U_SETJMP)
		_longjmp(jb, i);
	else 
		siglongjmp(sjb, i);

	atf_tc_fail("jmp failed");
}