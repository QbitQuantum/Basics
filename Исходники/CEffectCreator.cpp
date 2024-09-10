ALERROR IEffectPainter::ValidateClass (SLoadCtx &Ctx, const CString &sOriginalClass)

//	ValidateClass
//
//	Reads the class string. If the class does not match the current painter,
//	we read the old data and return ERR_FAIL.

	{
	if (Ctx.dwVersion >= 40)
		{
		CString sClass;
		sClass.ReadFromStream(Ctx.pStream);

		//	If the original class doesn't match the current one, then it means
		//	that the design changed. In that case, we load the painter using the
		//	old class.

		if (!strEquals(sClass, sOriginalClass))
			{
			//	If sClass is blank, then it means that the original did not have
			//	an effect painter (but the current design does)

			if (!sClass.IsBlank())
				{
				//	Get the original creator

				CEffectCreator *pOriginalCreator;
				if (CEffectCreator::CreateFromTag(sClass, &pOriginalCreator) != NOERROR)
					{
					kernelDebugLogMessage("Unable to find original effect creator: %s", sClass.GetASCIIZPointer());
					return ERR_FAIL;
					}

				//	Load the original painter

				IEffectPainter *pOriginalPainter = pOriginalCreator->CreatePainter();
				pOriginalPainter->ReadFromStream(Ctx);

				//	Discard

				pOriginalPainter->Delete();
				delete pOriginalCreator;
				}

			//	Done

			return ERR_FAIL;
			}
		}

	return NOERROR;
	}