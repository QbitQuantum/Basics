void TopWindow::Open()
{
	GuiLock __; 
	Open(GetActiveWindow());
}