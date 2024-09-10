// uButton Class
uButton::uButton()
{
	kxuRegisterWindowClass(KXU_BUTTON_CLASSNAME);
	SETRECT(LmpRect, 0, 0, 0, 0);
}