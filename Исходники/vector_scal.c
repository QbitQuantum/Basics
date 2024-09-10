static int approximately_equal(float a, float b)
{
#ifdef STARPU_HAVE_NEARBYINTF
	int ai = (int) nearbyintf(a * 1000.0);
	int bi = (int) nearbyintf(b * 1000.0);
#elif defined(STARPU_HAVE_RINTF)
	int ai = (int) rintf(a * 1000.0);
	int bi = (int) rintf(b * 1000.0);
#else
#error "Please define either nearbyintf or rintf."
#endif
	return ai == bi;
}