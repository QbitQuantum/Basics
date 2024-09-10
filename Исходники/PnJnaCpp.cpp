extern "C" void shutdown(){
	printf("C shutdown()\n");
	context.Shutdown();
}