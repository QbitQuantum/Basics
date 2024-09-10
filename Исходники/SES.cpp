CGMainWindow::CGMainWindow (QWidget* parent, Qt::WindowFlags flags)
: QMainWindow (parent, flags) {
	resize (604, 614);

	// Create a nice frame to put around the OpenGL widget
	QFrame* f = new QFrame (this);
	f->setFrameStyle(QFrame::Sunken | QFrame::Panel);
	f->setLineWidth(2);

	// Create our OpenGL widget
	ogl = new CGView (this,f);

	// Create a menu
	QMenu *file = new QMenu("&File",this);
	file->addAction ("Quit", this, SLOT(close()), Qt::CTRL+Qt::Key_Q);

	menuBar()->addMenu(file);

    QAction *action;
	// Create a 'View' menu
	QMenu *show = new QMenu("&Show",this);
	action = show->addAction("show sphere", ogl, SLOT(toggleSphere()), Qt::Key_C);
	action->setCheckable(true);
	menuBar()->addMenu(show);

	// Put the GL widget inside the frame
	QHBoxLayout* layout = new QHBoxLayout();
	layout->addWidget(ogl);
	layout->setMargin(0);
	f->setLayout(layout);

	setCentralWidget(f);

	statusBar()->showMessage("Ready",1000);
}