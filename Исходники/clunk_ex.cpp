void clunk::IOException::add_custom_message() {
	char buf[1024];
	memset(buf, 0, sizeof(buf));

#ifdef _MSC_VER
	strncpy(buf, _strerror(NULL), sizeof(buf));
#else 
	strncpy(buf, strerror(errno), sizeof(buf));
//	if (strerror_r(errno, buf, sizeof(buf)-1) != 0) perror("strerror");
#endif
	add_message(buf);
}