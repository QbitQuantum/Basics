// File format:
// name<newline>
// name<newline>
// etc...
bool InitDvarTable(const char *File)
{
	FILE *dvarList = nullptr;

	// Open file
	fopen_s(&dvarList, File, "r");

	// Check for file opening errors, if there were any, exit
	if (!dvarList)
		return false;

	// Get the input file size
	fseek(dvarList, 0, SEEK_END);
	long fileSize = ftell(dvarList);
	fseek(dvarList, 0, SEEK_SET);

	// Allocate memory
	DvarFileMemory = (char *)VirtualAlloc(nullptr, fileSize, MEM_COMMIT, PAGE_READWRITE);

	if (!DvarFileMemory)
		return false;

	// Read the file
	fread_s(DvarFileMemory, fileSize, 1, fileSize, dvarList);

	// Close it
	fclose(dvarList);

	return true;
}