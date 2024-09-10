void MkFixedFPUSetter::Restore(void)
{
	if (m_ControlWord.GetSize() == 1)
	{
		unsigned int cw;
		m_ControlWord.Pop(cw);
		_controlfp_s(&cw, _CW_DEFAULT, MCW_PC);
	}
}