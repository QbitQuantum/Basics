static int
test_offset64(void){
	struct stat sta;
	int fd,ret = -1;
	// FIXME off_t off;

	if((fd = OpenCreat(TESTFILE,O_RDWR | O_CREAT,755)) < 0){
		goto done;
	}
	if(Fstat(fd,&sta)){
		goto done;
	}
	// FIXME what is to be done with this?
	//off = 0x1ffffffffLL;
	ret = 0;

done:
	if(fd >= 0){
		ret |= Close(fd);
	}
	Unlink(TESTFILE);
	return ret;
}