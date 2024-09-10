static void CreateShaderCacheDirectory()
{
	const char* shaderCacheDirectory = "ShaderCache";
#if _WIN32
	if (!PathIsDirectoryA(shaderCacheDirectory))
	{
		CreateDirectoryA(shaderCacheDirectory, NULL);
	}
#else
	mkdir(shaderCacheDirectory,
		S_IRUSR | S_IWUSR | S_IXUSR |
		S_IRGRP | S_IWGRP | S_IXGRP |
		S_IROTH | S_IXOTH | S_IXOTH);
#endif
}