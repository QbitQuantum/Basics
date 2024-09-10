void test_repositoryCreateDestroy()
{
	Repository repo;
	repository_init(&repo, "repoTests.txt");

	assert(_msize(repo.objects) == sizeof(Vector));

	assert(vector_getLen(repo.objects) == 10);

	// Test 2 elements
	// #1
	assert(storeObject_GetID(vector_getAt(repo.objects, 1)) == 2);
	assert(!strcmp(product_GetType(storeObject_GetProduct(vector_getAt(repo.objects, 1))), "Laptop"));
	assert(!strcmp(product_GetModel(storeObject_GetProduct(vector_getAt(repo.objects, 1))), "v3.2"));
	assert(!strcmp(product_GetManufacturer(storeObject_GetProduct(vector_getAt(repo.objects, 1))), "Lenovo"));
	assert(storeObject_GetPrice(vector_getAt(repo.objects, 1)) == 5200);
	assert(storeObject_GetQuantity(vector_getAt(repo.objects, 1)) == 69);

	// #2
	assert(storeObject_GetID(vector_getAt(repo.objects, 9)) == 10);
	assert(!strcmp(product_GetType(storeObject_GetProduct(vector_getAt(repo.objects, 9))), "Laptop"));
	assert(!strcmp(product_GetModel(storeObject_GetProduct(vector_getAt(repo.objects, 9))), "v12.3"));
	assert(!strcmp(product_GetManufacturer(storeObject_GetProduct(vector_getAt(repo.objects, 9))), "HP"));
	assert(storeObject_GetPrice(vector_getAt(repo.objects, 9)) == 2200);
	assert(storeObject_GetQuantity(vector_getAt(repo.objects, 9)) == 69);


	repository_destroy(&repo);
	//assert(_msize(repo.objects) == -1);
	//assert(_msize(repo.fileName) == -1);
}