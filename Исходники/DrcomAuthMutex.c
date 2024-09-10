int main(int argc, char const *argv[])
{
	CreateMutexA(0,0,"Dr.COM_AUTH_SERVICE_MUTEX");
	if (GetLastError()==ERROR_ALREADY_EXISTS){
		printf("%s\n", "Drcom auth service is running!");
	}
	return 0;
}