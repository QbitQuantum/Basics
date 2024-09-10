//----------
// Tool::Bar
//----------
Bar::Bar (Win::Dow::Handle winParent,
		  int toolbarId,
		  int bitmapId,
		  int buttonWidth,
		  Cmd::Vector const & cmdVector,
		  Tool::Item const * buttonItems,
		  Win::Style const & barStyle)
	: _buttonImages (winParent.GetInstance (), bitmapId, buttonWidth),
	  _cmdVector (cmdVector),
	  _buttonItems (buttonItems)
{
	Tool::Maker maker (winParent, toolbarId);
	maker.Style () << barStyle;
	Reset (maker.Create ());
	int width, height;
	_buttonImages.GetImageSize (width, height);
	SetButtonSize (width, height);
	SetImageList (_buttonImages);

	// Map button id to command id and cmd id to button item index
	for (unsigned i = 0; _buttonItems [i].buttonId != Item::idEnd; ++i)
	{
		int buttonId = _buttonItems [i].buttonId;
		if (buttonId != Item::idSeparator)
		{
			int cmdId = _cmdVector.Cmd2Id (_buttonItems [i].cmdName);
			Assert (cmdId != -1);
			_buttonId2CmdId [buttonId] = cmdId;
			_cmdId2ButtonIdx [cmdId] = i;
		}
	}
}