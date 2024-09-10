/*initalizes all needed objects for opencl
OCLHandle - Datastructure containg the opencl objects
*/
bool SetupOpenCLEnvironment( OpenCLData * OCLHandle)
{
	InitializePlatform(OCLHandle);
	InitializeDevice(OCLHandle);
	InitializeContext(OCLHandle);
	InitializeProgram(OCLHandle);
	InitializeKernels(OCLHandle);
	InitializeQueue(OCLHandle);

	return true;
}