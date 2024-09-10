	void seh_exception::initialize()
	{
#pragma warning(push)
#pragma warning(disable: 4535)
		_set_se_translator(trans_func);
#pragma warning(pop)
	}