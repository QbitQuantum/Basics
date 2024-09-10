/**
 * Show the on-screen keyboard (osk) associated with a given textbox
 * @param parent pointer to the Window where this keyboard originated from
 * @param button widget number of parent's textbox
 */
void ShowOnScreenKeyboard(Window *parent, int button)
{
	DeleteWindowById(WC_OSK, 0);

	GetKeyboardLayout();
	new OskWindow(&_osk_desc, parent, button);
}