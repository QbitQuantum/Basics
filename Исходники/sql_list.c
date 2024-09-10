int
main()
{
	list *l = list_create(NULL);

	printf("0 list_length %d\n", list_length(l));
	list_append_string(l, _STRDUP("niels"));
	printf("1 list_length %d\n", list_length(l));
	list_append_string(l, _STRDUP("nes"));
	printf("1 list_length %d\n", list_length(l));
	list_append_string(l, _STRDUP("lilian"));
	printf("1 list_length %d\n", list_length(l));
	list_append_string(l, _STRDUP("nes"));
	printf("1 list_length %d\n", list_length(l));
	list_append_string(l, _STRDUP("max"));
	printf("1 list_length %d\n", list_length(l));
	list_append_string(l, _STRDUP("nes"));
	printf("1 list_length %d\n", list_length(l));
	list_traverse(l, print_data, NULL);
	printf("\n");

	list_traverse(l, destroy_data, NULL);
	list_destroy(l);
}