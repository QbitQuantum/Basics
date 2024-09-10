struct ff_arch_fiber *ff_arch_fiber_initialize()
{
	main_fiber.handle = ConvertThreadToFiber((LPVOID) NULL);
	ff_assert(main_fiber.handle != NULL);

	return &main_fiber;
}