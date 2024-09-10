PLUGIN_EXPORT void ExecuteBang(void* data, LPCWSTR args)
{
	ChildMeasure* child = (ChildMeasure*)data;
	ParentMeasure* parent = child->parent;

	// !CommandMeasure can only be used on the Parent measure.
	if (!parent || parent->ownerChild != child)
		return;

	// !CommandMeasure Clear
	if (_wcsicmp(args, L"Clear") == 0)
	{
		std::wstring currentData = parent->clipboard->GetIndex(0);

		// Clear contents of the Clipboard
		if (!parent->clipboard->DeleteClipboard())
		{
			RmLog(LOG_ERROR, L"Clipboard.dll: Unable to delete clipboard");
		}
		else
		{
			if (!currentData.empty())
			{
				// Clear index 0 of ALL instances (if equal to current index 0)
				clearIndex(currentData);
			}
		}

		return;
	}
	else
	{
		// Check for commands with args.
		LPCWSTR arg = wcschr(args, L' ');
		if (arg)
		{
			// Skip the space
			++arg;

			// !CommandMeasure ClearIndex n (where n represents an index)
			if (_wcsnicmp(args, L"ClearIndex", 10) == 0)
			{
				int index = _wtoi(arg);
				std::wstring currentData = parent->clipboard->GetIndex(index);

				if (!currentData.empty())
				{
					// Index 0 represents the Windows Clipboard. If deleting this index, other parent measure need to be modified.
					if (index == 0)
					{
						parent->clipboard->ClearClipboard();
						clearIndex(currentData);
					}
					else
					{
						if (!parent->clipboard->DeleteIndex(index))
						{
							std::wstring error = L"Clipboard.dll: Unable to delete index \"";
							error += index;
							error += L'"';
							RmLog(LOG_ERROR, error.c_str());
						}
					}
				}

				return;
			}
			// !CommandMeasure "CopyIndex n" (where n represents an index)
			else if (_wcsnicmp(args, L"CopyIndex", 9) == 0)
			{
				LPCWSTR text = parent->clipboard->GetIndex(_wtoi(arg));

				if (!parent->clipboard->SetClipboard(text))
				{
					RmLog(LOG_ERROR, L"Clipboard.dll: Unable to set clipboard");
				}

				return;
			}
			else
			{
				RmLog(LOG_ERROR, L"Clipboard.dll: Unknown args");
			}
		}
	}

	return;
}