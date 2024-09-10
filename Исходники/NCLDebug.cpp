void NCLDebug::DrawTextWsNDT(const Vector3& pos, const float font_size, const TextAlignment alignment, const Vector4 colour, const string text, ...)
{
	va_list args;
	va_start(args, text);

	char buf[1024];
	int needed = vsnprintf_s(buf, 1023, _TRUNCATE, text.c_str(), args);
	va_end(args);

	int length = (needed < 0) ? 1024 : needed;

	std::string formatted_text = std::string(buf, (size_t)length);

	Vector4 cs_pos = m_ProjViewMtx * Vector4(pos.x, pos.y, pos.z, 1.0f);
	cs_pos.z = 1.0f * cs_pos.w;
	DrawTextCs(cs_pos, font_size, formatted_text, alignment, colour);
}