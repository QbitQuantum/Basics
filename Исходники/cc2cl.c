void nostdinc() {
	putenv("INCLUDE=");		// Windows
	putenv("INCLUDE");		// POSIX
	//assert(!getenv("INCLUDE"));
	add_to_argv("-X");
}