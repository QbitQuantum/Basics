FileSelectWidget::FileSelectWidget(QWidget *parent) : QWidget(parent), CommonMyWidgetWrapper(this)
{
	QFrame *frameTextAndButton = new QFrame;
	QHBoxLayout *layoutTextAndButton = new QHBoxLayout;
	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(2);
	layoutTextAndButton->setContentsMargins(0, 0, 0, 0);
	layoutTextAndButton->setSpacing(2);
	lineEdit = new QLineEdit;
	button = new QPushButton;
	labelImage = new QLabel;
	labelImage->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
	labelImage->setContentsMargins(0, 0, 0, 0);
	labelImage->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	labelImage->setMaximumHeight(150);
	labelImage->setMaximumWidth(300);
	labelImage->setStyleSheet(
		"QLabel { color: red; font-weight: bold; border: 1px solid black;"
		"background-color: white; padding: 1px; }");
	QIcon iconFolder = QIcon::fromTheme("folder", QIcon(":/system/icons/folder.svg"));
	button->setIcon(iconFolder);
	layoutTextAndButton->addWidget(lineEdit);
	layoutTextAndButton->addWidget(button);
	frameTextAndButton->setLayout(layoutTextAndButton);

	layout->addWidget(frameTextAndButton);
	layout->addWidget(labelImage);

	defaultValue = "";
	connect(button, SIGNAL(clicked()), this, SLOT(slotSelectFile()));
	connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(slotChangedFile()));
}