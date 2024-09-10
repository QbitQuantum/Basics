int TestFreeRDPCodecProgressive(int argc, char* argv[])
{
	char* ms_sample_path;

	ms_sample_path = _strdup("/tmp/EGFX_PROGRESSIVE_MS_SAMPLE");

	if (PathFileExistsA(ms_sample_path))
		return test_progressive_ms_sample(ms_sample_path);

	free(ms_sample_path);

	return 0;
}