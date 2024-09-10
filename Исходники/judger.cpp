int compile(int lang) {
	int pid;

	const char * CP_C[] = { "gcc", "Main.c", "-o", "Main", "-O2","-Wall", "-lm",
		"--static", "-std=c99", "-DONLINE_JUDGE", NULL };
	const char * CP_X[] = { "g++", "Main.cc", "-o", "Main", "-O2", "-Wall",
		"-lm", "--static", "-DONLINE_JUDGE", NULL };
	const char * CP_P[] = { "fpc", "Main.pas", "-O2","-Co", "-Ct","-Ci", NULL };
	const char * CP_J[] = { "javac", "-J-Xms32m", "-J-Xmx256m", "Main.java",
		NULL };
	const char * CP_R[] = { "ruby", "-c", "Main.rb", NULL };
	const char * CP_B[] = { "chmod", "+rx", "Main.sh", NULL };
	const char * CP_Y[] = { "python","-c","import py_compile; py_compile.compile(r'Main.py')", NULL };
	const char * CP_PH[] = { "php", "-l","Main.php", NULL };
	const char * CP_PL[] = { "perl","-c", "Main.pl", NULL };
	const char * CP_CS[] = { "gmcs","-warn:0", "Main.cs", NULL };
	pid = fork();
	if (pid == 0) {
		struct rlimit LIM;
		LIM.rlim_max = 60;
		LIM.rlim_cur = 60;
		setrlimit(RLIMIT_CPU, &LIM);

		LIM.rlim_max = 8 * STD_MB;
		LIM.rlim_cur = 8 * STD_MB;
		setrlimit(RLIMIT_FSIZE, &LIM);

		LIM.rlim_max = 1024 * STD_MB;
		LIM.rlim_cur = 1024 * STD_MB;
		setrlimit(RLIMIT_AS, &LIM);
		if (lang != 2) {
			freopen("ce.txt", "w", stderr);
			//freopen("/dev/null", "w", stdout);
		} else {
			freopen("ce.txt", "w", stdout);
		}
		switch (lang) {
			case 0:
				execvp(CP_C[0], (char * const *) CP_C);
				break;
			case 1:
				execvp(CP_X[0], (char * const *) CP_X);
				break;
			case 2:
				execvp(CP_P[0], (char * const *) CP_P);
				break;
			case 3:
				execvp(CP_J[0], (char * const *) CP_J);
				break;
			case 4:
				execvp(CP_R[0], (char * const *) CP_R);
				break;
			case 5:
				execvp(CP_B[0], (char * const *) CP_B);
				break;
			case 6:
				execvp(CP_Y[0], (char * const *) CP_Y);
				break;
			case 7:
				execvp(CP_PH[0], (char * const *) CP_PH);
				break;
			case 8:
				execvp(CP_PL[0], (char * const *) CP_PL);
				break;
			case 9:
				execvp(CP_CS[0], (char * const *) CP_CS);
				break;
			default:
				printf("nothing to do!\n");
		}
		if (DEBUG)
			printf("compile end!\n");
		exit(!system("cat ce.txt"));
		//exit(0);
	} else {
		int status=0;

		waitpid(pid, &status, 0);
		if(lang>3&&lang<7)
			status=get_file_size("ce.txt");
		if (DEBUG)
			printf("status=%d\n", status);
		return status;
	}

}