// put the driver through its paces to make sure it's there and active
static void DiagRDPMC(void)
{    
    HANDLE hDriver;
    unsigned __int64 i;

    // Try opening a static device driver. 
    hDriver = LoadDriver();
    if (hDriver != (INVALID_HANDLE_VALUE)) {
	printf("Ready to execute RDPMC from user space...\n");
    i = __readpmc(0);
    printf("We have successfully executed RDPMC from user space: 0x%x!\n", i);
	CloseHandle(hDriver);
    }
}