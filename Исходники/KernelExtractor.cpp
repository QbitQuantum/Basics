CUresult util::KernelExtractorDriver::cuModuleLoad(CUmodule *module, const char *fname) {
	trace();	
	CUresult res = cudaDriver.cuModuleLoad(module, fname);
	if (enabled) {
		loadModule(res, *module, 0, fname);
	}
	RETURN( res );
}