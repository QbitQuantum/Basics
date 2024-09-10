void Element::RemoveElement(Element *pChild)
	{
	// child removed: forward to parent
	if (pParent)
		pParent->RemoveElement(pChild);
	else if (this != Screen::GetScreenS())
		// always ensure removal from screen!
		if (Screen::GetScreenS())
			// but not if this is the context menu, to avoid endless flip-flop!
			if (!IsMenu())
				Screen::GetScreenS()->RemoveElement(pChild);
	}