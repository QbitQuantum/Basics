void ChannelAgent::TabExpansion(void)
{
	/*
	 * Function purpose: Get the characters before the caret's current position,
	 *                   and update the fInput VTextControl with a relevant match
	 *                   from the ChannelAgent's NamesView
	 */

	int32 start, finish;
	static int32 lastindex;
	static BString lastNick;
	fInput->TextView()->GetSelection(&start, &finish);

	if (fInput->TextView()->TextLength() && start == finish &&
		start == fInput->TextView()->TextLength()) {
		const char* fInputText(fInput->TextView()->Text() + fInput->TextView()->TextLength());
		const char* place(fInputText);

		while (place > fInput->TextView()->Text()) {
			if (*(place - 1) == '\x20') break;

			--place;
		}

		if (fLastExpansion.Length() == 0 ||
			fLastExpansion.ICompare(place, fLastExpansion.Length()) != 0 || lastNick != place) {
			lastindex = 0;
			fLastExpansion = place;

			while (!fCompletionNicks.IsEmpty()) delete fCompletionNicks.RemoveItemAt(0L);

			int32 count(fNamesList->CountItems()), i(0);

			for (i = 0; i < count; i++) {
				BString* name(new BString(static_cast<NameItem*>(fNamesList->ItemAt(i))->Name()));
				if (!(name->ICompare(fLastExpansion.String(), strlen(fLastExpansion.String()))))
					fCompletionNicks.AddItem(name);
				else
					delete name;
			}
			// sort items alphabetically
			fCompletionNicks.SortItems(AlphaSortNames);

			count = fRecentNicks.CountItems();
			// parse recent nicks in reverse to ensure that they're pushed onto the completion
			// list in the correct order
			for (i = 0; i < count; i++) {
				BString* name(new BString(*fRecentNicks.ItemAt(i)));
				if (!(name->ICompare(fLastExpansion.String(), strlen(fLastExpansion.String())))) {
					// parse through list and nuke duplicate if present
					for (int32 j = fCompletionNicks.CountItems() - 1; j >= 0; j--) {
						if (!(name->ICompare(*fCompletionNicks.ItemAt(j)))) {
							delete fCompletionNicks.RemoveItemAt(j);
							break;
						}
					}
					fCompletionNicks.AddItem(name, 0);
				} else
					delete name;
			}
		}

		// We first check if what the user typed matches the channel
		// If that doesn't match, we check the names
		BString insertion;

		if (!fId.ICompare(place, strlen(place)))
			insertion = fId;
		else {
			int32 count = fCompletionNicks.CountItems();
			if (count > 0) {
				insertion = *(fCompletionNicks.ItemAt(lastindex++));

				if (lastindex == count) lastindex = 0;
				lastNick = insertion;
			}
		}

		if (insertion.Length()) {
// check if we are at the beginning of a line
// (ignoring whitespace). if we are, prepend a colon to the nick being
// inserted
#if 0
      const char *place2 = place;
      while (place2 > fInput->TextView()->Text())
      {
        --place2;
        if (*place2 != 0x20)
          break;
      }
      if (place2 == fInput->TextView()->Text())
	insertion += ": ";
#endif
			fInput->TextView()->Delete(place - fInput->TextView()->Text(),
									   fInput->TextView()->TextLength());

			fInput->TextView()->Insert(insertion.String());
			fInput->TextView()->Select(fInput->TextView()->TextLength(),
									   fInput->TextView()->TextLength());
		}
	}
}