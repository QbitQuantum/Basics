int IsKernelEntry(const GptEntry *e)
{
	static Guid chromeos_kernel = GPT_ENT_TYPE_CHROMEOS_KERNEL;
	return !Memcmp(&e->type, &chromeos_kernel, sizeof(Guid));
}