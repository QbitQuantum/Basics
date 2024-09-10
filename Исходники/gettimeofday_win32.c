PHP_COUCHBASE_LOCAL
void usleep(unsigned long usec)
{
	Sleep(usec / 1000);
}