int main(void){
	get_symbol("/tmp/proftpd.so", "pr_version_get_str");
	printf("Using proftpd.so version: %s\n", getversion());
	print_map();
	return 0;
}