ActionLineEditButton::ActionLineEditButton( QWidget *parent )
		: QAbstractButton(parent), action_(0), popup_(0)
{
	setCursor(Qt::PointingHandCursor);
}