//------------------------------------------------------------------------------------------------
void RshError::PrintErrorDebug(U32 error, wchar_t* message, bool includeSystemErrorInfo)
{
		
		#if defined(RSH_MSWINDOWS)
		_wsetlocale( LC_ALL, L"Russian" );	
		#elif defined(RSH_LINUX)
          setlocale( LC_ALL, "ru_RU.utf8" );
		#endif
		RSH_LANGUAGE language = RSH_LANGUAGE_ENGLISH;

		if(error != RSH_API_SUCCESS)
		{
			
			std::wcout<<std::endl<<rshUTF16("--ERROR[0x");

			wchar_t bufferRshApi[4096];
            U32 res = RshError::GetErrorDescriptionUTF16(error & ~0xffff, bufferRshApi,4096,language);
			if(res == RSH_API_SUCCESS)
			{
				std::wcout << std::hex
				<< (error & 0xffff0000) << rshUTF16("]-- ");
				if(message)
					std::wcout<<message;
				else
					std::wcout<<rshUTF16("~~!wchar_t* message points to NULL!~~");
				std::wcout<<rshUTF16(": ")<< bufferRshApi<<std::endl ;
			}
			else
			{
				std::wcout <<rshUTF16("Couldn't format error message - GetErrorDescriptionUTF16 failed with code 0x")<<std::hex<<res;
			}

			
			
			if(includeSystemErrorInfo && (error & 0xffff) )
			{
				wchar_t buffer[4096];

                U32 res = RshError::GetSystemErrorDescriptionUTF16( error & 0xffff, buffer, 4096 );
				if(res == RSH_API_SUCCESS)
				{
					std::wcout<<std::endl<<rshUTF16("System error [");
					std::wcout<<std::dec<< (error & 0xffff)<<rshUTF16("]: ");                          
                                std::wcout<< buffer<<std::endl;
				}
				else
				{
					std::wcout <<rshUTF16("Couldn't format error message - GetSystemErrorDescriptionUTF16 failed with code 0x")<<std::hex<<res;
				}
			}
			
		}
		else
		{
			std::wcout<<std::endl<< rshUTF16("--SUCCESS-- ")<<message<<std::endl;		
		}
}