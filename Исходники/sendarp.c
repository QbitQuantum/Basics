int main(int argc, char **argv)
{
	char *srcdev = NULL;
	char *dstdev = NULL;
	int opt;

	while ((opt = getopt(argc, argv, "s:d:")) != -1) {
		switch (opt) {
		case 's': 
			srcdev = (char *)strdup(optarg);
			break;
		case 'd':
			dstdev = (char *)strdup(optarg);
			break;
		}
	}

    if ((srcdev == NULL) || (dstdev == NULL)) {
        show_usage();
        return 0;
    }

    /* send gratutious ARP packet with srcdev's IP and hardware address to dstdev */
    sendArp(srcdev, dstdev);

	return EXIT_SUCCESS;
}