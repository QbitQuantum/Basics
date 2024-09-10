		bool putenv(const char *varName, const char *value)
		{
#if defined(_MSC_VER) && _MSC_VER >= 1400
			return _putenv_s(varName, value) == 0;
#else

#endif
		}