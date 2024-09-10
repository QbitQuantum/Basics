void XsiExp::WriteConfig()
{
	TSTR filename = GetCfgFilename();
	FILE* cfgStream;

	cfgStream = fopen(filename, "wb");
	if (!cfgStream)
  {
		return;
  }

	// Write CFG version
	_putw(CFG_VERSION,				cfgStream);

	fputc(GetIncludeAnim(),			cfgStream);
	fputc(GetIncludeVertexColors(),	cfgStream);

	fputc(GetAlwaysSample(),		cfgStream);
	_putw(GetMeshFrameStep(),		cfgStream);
	_putw(GetKeyFrameStep(),		cfgStream);

  _putw(GetPrecision(),			cfgStream);

	fclose(cfgStream);
}