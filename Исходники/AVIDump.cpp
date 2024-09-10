bool AVIDump::SetCompressionOptions()
{
	memset(&s_options, 0, sizeof(s_options));
	s_array_options[0] = &s_options;

	if (SConfig::GetInstance().m_DumpFramesSilent)
	{
		s_options.fccType = streamtypeVIDEO;
		s_options.fccHandler = mmioFOURCC('D', 'I', 'B', ' ');  // Uncompressed
		return true;
	}
	else
	{
		return (AVISaveOptions(s_emu_wnd, 0, 1, &s_stream, s_array_options) != 0);
	}
}