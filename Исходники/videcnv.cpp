//===================>>> vedTextEditor::TextMouseDown <<<====================
  void vedTextEditor::TextMouseDown(int row, int col, int button)
  {
    static int clicks = 0;
    int btn = (GetFileType() == gccError || GetFileType() == bccError)
	 ? 1 : button;

    long oldLine = GetCurLine();		// remember current position
    int oldCol = getColPos();
    
    vTextEditor::TextMouseDown(row, col, btn);	// translate to left

    if (button == 1 && oldLine == GetCurLine() && oldCol == getColPos()) // double click...
      {
	++clicks;
	if (clicks > 3)
	    clicks = 1;
	setSelection(clicks);
      }
    else
      {
	clicks = 0;
      }

  }