//---------------------------------------------------------------------------------
void LLIMWellWindow::RowPanel::onChicletSizeChanged(LLChiclet* ctrl, const LLSD& param)
{
	LLTextBox* text = getChild<LLTextBox>("contact_name");
	S32 new_text_left = mChiclet->getRect().mRight + CHICLET_HPAD;
	LLRect text_rect = text->getRect(); 
	text_rect.mLeft = new_text_left;
	text->setRect(text_rect);
}