	void DocumentExporter::saveParamClip()
	{
		int length = 0;
		
		MItDependencyNodes CharacterItr(MFn::kCharacter);
		for (int i1 = 0; !CharacterItr.isDone(); CharacterItr.next(), i1++)
		{
			MFnCharacter character;
			if (!character.setObject(CharacterItr.item())) continue;

			MPlugArray array;
			character.getMemberPlugs(array);

			length = array.length();
		}

		MIntArray  arrayChannelAttribute(length, 0);


		MItDependencyNodes clipItr(MFn::kClip);
		MFnClip clipFn;
		for (int i1 = 0; !clipItr.isDone(); clipItr.next(), i1++)
		{

			if (!clipFn.setObject(clipItr.item())) continue;

			// save original param
			MIntArray  arrayOriginalChannelAttribute(length);
			clipFn.getAbsoluteChannelSettings(arrayOriginalChannelAttribute);
			ParamClipVec.push_back(arrayOriginalChannelAttribute);

			// set relativeClip on
			clipFn.setAbsoluteChannelSettings(arrayChannelAttribute);
		}
	}