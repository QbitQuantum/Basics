int main(int argc, char **argv)
{
	uint32_t *handle, *start_val;
	uint32_t start = 0;
	int i, fd, count;

	igt_simple_init(argc, argv);

	fd = drm_open_driver(DRIVER_INTEL);

	igt_require(IS_GEN3(intel_get_drm_devid(fd)));

	count = 0;
	if (argc > 1)
		count = atoi(argv[1]);
	if (count == 0)
		count = 3 * gem_aperture_size(fd) / (1024*1024) / 2;
	igt_info("Using %d 1MiB buffers\n", count);

	handle = malloc(sizeof(uint32_t)*count*2);
	start_val = handle + count;

	for (i = 0; i < count; i++) {
		handle[i] = create_bo(fd, start);
		start_val[i] = start;
		start += 1024 * 1024 / 4;
	}

	igt_info("Verifying initialisation...\n");
	for (i = 0; i < count; i++)
		check_bo(fd, handle[i], start_val[i]);

	igt_info("Cyclic blits, forward...\n");
	for (i = 0; i < count * 4; i++) {
		int src = i % count;
		int dst = (i + 1) % count;

		copy(fd, handle[dst], handle[src]);
		start_val[dst] = start_val[src];
	}
	for (i = 0; i < count; i++)
		check_bo(fd, handle[i], start_val[i]);

	igt_info("Cyclic blits, backward...\n");
	for (i = 0; i < count * 4; i++) {
		int src = (i + 1) % count;
		int dst = i % count;

		copy(fd, handle[dst], handle[src]);
		start_val[dst] = start_val[src];
	}
	for (i = 0; i < count; i++)
		check_bo(fd, handle[i], start_val[i]);

	igt_info("Random blits...\n");
	for (i = 0; i < count * 4; i++) {
		int src = random() % count;
		int dst = random() % count;

		if (src == dst)
			continue;

		copy(fd, handle[dst], handle[src]);
		start_val[dst] = start_val[src];
	}
	for (i = 0; i < count; i++)
		check_bo(fd, handle[i], start_val[i]);

	igt_exit();
}