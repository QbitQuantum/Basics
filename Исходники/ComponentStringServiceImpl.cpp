		IERServiceStringConverter *CharsetDetector::detect(const char *str)
		{
			const char *name;
			if((str[0] != '\0' && str[0] == '\xFF') && (str[1] != '\0' && str[1] == '\xFE'))
				name = "UTF-16LE";
			else if((str[0] != '\0' && str[0] == '\xFE') && (str[1] != '\0' && str[1] == '\xFF'))
				name = "UTF-16BE";
			else
			{
				UErrorCode err = U_ZERO_ERROR;
				ucsdet_setText(cd, str, -1, &err);
				if(U_FAILURE(err))
					return nullptr;
				const UCharsetMatch *cm = ucsdet_detect(cd, &err);
				if(U_FAILURE(err))
					return nullptr;
				name = ucsdet_getName(cm, &err);
				if(U_FAILURE(err))
					return nullptr;
			}

			StringCharsetConverter *c = new StringCharsetConverter();
			if(!c->setCharset(name))
			{
				delete c;
				return nullptr;
			}

			return ServicePointerManager::instance().append<IERServiceStringConverter>(c);
		}