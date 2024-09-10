int main(int argc, char *argv[])
{
	if (argc != 2 && argc != 3) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return 1;
	}

	if (argc == 3)
		fault_count_fname = argv[2];
	else
		fault_count_fname = "fault_cnt.out";

	so_init_loader();

	if (AddVectoredExceptionHandler(HANDLER_CALL_FIRST,
					(PVECTORED_EXCEPTION_HANDLER)test_segv_handler) < 0) {
		fprintf(stderr, "cannot set signal handler\n");
		return 1;
	}

	so_execute(argv[1], argv+1);

	// Shouldn't reach here
	return 1;
}