int main(int argc, const char *argv[])
{
	int ret = 0;
	KonohaContext* konoha = CreateContext();
	test_gc(konoha);
	DeleteContext(konoha);
	assert(__Free__ == __Init__);
	fprintf(stderr, "alloced_object_count = %d, freed_object_count=%d\n", __Init__, __Free__);
	test_bitops();
	return ret;
}