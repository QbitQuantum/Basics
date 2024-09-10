		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader instance;

			if (NEResult::hasError(instance.isValid()))
			{
				instance.getName() = "XAudio2OGGDecoder";
				instance.getDeveloper() = "kniz";
				instance.setRevision(1);
				instance.getVersion() = "0.0.1a";
				instance.getReleaseDate() = "2015-05-07";
				instance.getComment() =
					".ogg 파일을 읽는 Module 입니다.\n"
					"XAudio2Player에 사용됩니다.";
				instance.getArgumentsComments() = SuperClass::getHeader().getArgumentsComments();
			}

			return instance;
		}