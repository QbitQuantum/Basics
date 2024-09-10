void CAhx::Decode(CArcFile* pclArc, LPBYTE ahx_buf, DWORD ahx_buf_len)
{
	// Convert AHX to WAV
	DWORD wav_buf_len = pclArc->ConvEndian(*(LPDWORD)&ahx_buf[12]) * 2;
	YCMemory<BYTE> wav_buf(wav_buf_len + 1152 * 16); // Advance //+ 1152 * 2); // margen = layer-2 frame size
	wav_buf_len = Decompress(&wav_buf[0], ahx_buf, ahx_buf_len);

	// Output
	CWav wav;
	wav.Init(pclArc, wav_buf_len, pclArc->ConvEndian(*(LPDWORD)&ahx_buf[8]), ahx_buf[7], 16);
	wav.Write(&wav_buf[0]);
}