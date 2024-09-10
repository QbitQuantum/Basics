void LLFloaterSearchReplace::show(LLTextEditor* editor)
{
	if (!sInstance)
	{
		sInstance = new LLFloaterSearchReplace();
	}

	if ( (sInstance) && (editor) )
	{
		sInstance->mEditor = editor;

		LLFloater* newdependee, *olddependee = sInstance->getDependee();
		LLView* viewp = editor->getParent();
		while (viewp)
		{
			newdependee = dynamic_cast<LLFloater*>(viewp);
			if (newdependee)
			{
				if (newdependee != olddependee)
				{
					if (olddependee)
						olddependee->removeDependentFloater(sInstance);

					if (!newdependee->getHost())
						newdependee->addDependentFloater(sInstance);
					else
						newdependee->getHost()->addDependentFloater(sInstance);
				}
				break;
			}
			viewp = viewp->getParent();
		}

		sInstance->open();
	}
}