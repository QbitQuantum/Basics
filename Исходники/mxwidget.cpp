bool
mxWidget::isEnabled () const
{
	return (IsWindowEnabled (d_this->d_hwnd) == TRUE);
}