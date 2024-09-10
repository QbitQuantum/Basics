InfoBar::InfoBar( QWidget *parent )
	: QWidget( parent )
{
	setBackgroundColor();
	createLayout();
	createIcon();
	createLabel();
	createCloseButton();
}