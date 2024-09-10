int
main(int argc, char** argv)
{
	if (argc > 1 && !strcmp(argv[1], "-v"))
		gVerbose = true;

	BFile file;
	status_t status = file.SetTo(kTempFile, B_CREATE_FILE | B_READ_WRITE);
	if (status != B_OK) {
		fprintf(stderr, "Could not create temporary file: %s\n",
			strerror(status));
		return 1;
	}

	puts("--------- Remove Tests ----------");

	// remove test, many attributes

	puts("Test 1...");

	for (int32 count = 5; count <= 100; count += 5) {
		add_attributes(file, 1, count);
		add_marker_attribute(file, count);
		add_attributes(file, count + 1, count);

		test_remove_attributes(file, 1, count,
			count & 1 ? count - 1 : count + 1, count, -1);

		remove_attributes(file, 1, count * 2);
	}

	// remove test, all positions

	puts("Test 2...");

	for (int32 i = 1; i < 100; i++) {
		add_attributes(file, 1, 50);
		add_marker_attribute(file, 51);
		add_attributes(file, 51, 50);

		test_remove_attributes(file, 1, 100, i, 51, -1);

		remove_attributes(file, 1, 100);
	}

	// remove test, all positions, remove many

	puts("Test 3...");

	for (int32 i = 1; i < 100; i++) {
		add_attributes(file, 1, 33);
		add_marker_attribute(file, 33);
		add_attributes(file, 34, 34);
		add_marker_attribute(file, 67);
		add_attributes(file, 68, 33);

		test_remove_attributes(file, 1, 100, i, 33, 67);

		remove_attributes(file, 1, 100);
	}

	puts("--------- Add Tests ----------");

	// add test, many attributes

	puts("Test 4...");

	for (int32 count = 10; count <= 200; count += 10) {
		add_attributes(file, 1, count);

		int32 half = count / 2;

		test_add_attributes(file, 1, count,
			half & 1 ? half - 1 : half + 1, half - 2, half + 2);

		remove_attributes(file, 1, count);
	}

	// add test, all iterator positions

	puts("Test 5...");

	for (int32 i = 1; i < 100; i++) {
		add_attributes(file, 1, 100);

		test_add_attributes(file, 1, 100, i, 50, -1);

		remove_attributes(file, 1, 100);
	}

	// add test, all attribute positions

	puts("Test 6...");

	for (int32 i = 1; i < 100; i++) {
		add_attributes(file, 1, 100);

		test_add_attributes(file, 1, 100, 50, i, -1);

		remove_attributes(file, 1, 100);
	}

	// add test, many attributes

	puts("Test 7...");

	for (int32 i = 1; i < 100; i++) {
		add_attributes(file, 1, 100);

		test_add_attributes(file, 1, 100, i, 33, 67);

		remove_attributes(file, 1, 100);
	}

	// add test, many attributes

	puts("Test 8...");

	for (int32 i = 1; i < 100; i++) {
		add_attributes(file, 1, 100);

		test_add_attributes(file, 1, 100, 50, i - 1, i + 1);

		remove_attributes(file, 1, 100);
	}

	BEntry entry;
	if (entry.SetTo(kTempFile) == B_OK)
		entry.Remove();

	return 0;
}