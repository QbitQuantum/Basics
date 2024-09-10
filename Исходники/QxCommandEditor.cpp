QxCommandEditor::QxCommandEditor(QWidget* parent)
	: QxDialog(parent),
	  iconSelector_(new QxIconSelector(parent)),
	  command_(0)
{
	setWindowTitle(qApp->applicationName() + tr("- Edit Command"));
	
	QVBoxLayout* col = new QVBoxLayout;
	{
		QFormLayout* form = new QFormLayout;
		form->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
		{
			icon_ = new QToolButton(this);
			icon_->setText("...");
			icon_->setIconSize(QSize(24, 24));
			iconReset_ = new QToolButton(this);
			iconReset_->setText(tr("Reset"));
			connect(icon_, SIGNAL(clicked()), this, SLOT(loadIcon()));
			connect(iconReset_, SIGNAL(clicked()), this, SLOT(resetIcon()));
		
			QHBoxLayout* row = new QHBoxLayout;
			row->addWidget(icon_);
			row->addWidget(iconReset_);
			row->addStretch();
			form->addRow(tr("Icon"), row);
		}
		{
			noDescription_ = tr("<optional text>");
			description_ = new QLineEdit(this);
			description_->setText(noDescription_);
			form->addRow(tr("Description"), description_);
		}
		{
			modifier_ = new QComboBox(this);
			modifier_->addItem(tr("None"));
			modifier_->addItem(tr("Alt"), Qt::Key_Alt);
			modifier_->addItem(tr("Control"), Qt::Key_Control);
			modifier_->addItem(tr("Meta"), Qt::Key_Meta);
			keyGroup_ = new QComboBox(this);
			keyGroup_->addItem(tr("F1-F12"));
			keyGroup_->addItem(tr("0-9"));
			key_ = new QComboBox(this);
			connect(keyGroup_, SIGNAL(currentIndexChanged(int)), this, SLOT(updateKey(int)));
			updateKey(0);
			
			QHBoxLayout* row = new QHBoxLayout;
			row->addWidget(modifier_);
			row->addWidget(keyGroup_);
			row->addWidget(key_);
			row->addStretch();
			form->addRow(tr("Short key"), row);
		}
		{
			scriptLabel_ = new QLabel(tr("Script"), this);
			target_ = new QComboBox(this);
			target_->addItem(tr("Paste into current terminal"), QxCommand::ActiveTerminal);
			target_->addItem(tr("Paste into new terminal"), QxCommand::NewTerminal);
			// target_->addItem(tr("Paste into editor"), QxCommand::TextEditor);
			target_->addItem(tr("Open by default application"), QxCommand::WebBrowser);
			connect(target_, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTarget(int)));
			QHBoxLayout* row = new QHBoxLayout;
			row->addWidget(target_);
			row->addStretch();
			form->addRow(scriptLabel_, row);
		}
		{
			autoSaveFile_ = new QCheckBox(tr("Automatically save current file"), this);
			autoOpenNextLink_ = new QCheckBox(tr("Automatically open next link"), this);
			QVBoxLayout* col = new QVBoxLayout();
			col->addWidget(autoSaveFile_);
			col->addWidget(autoOpenNextLink_);
			form->addRow(tr("Options"), col);
		}
		col->addLayout(form);
	}
	{
		QFrame* frame = new QFrame(this);
		frame->setFrameStyle(QFrame::Sunken|QFrame::StyledPanel);
		
		script_ = new EditWidget(frame);
		script_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		
		QHBoxLayout* cell = new QHBoxLayout;
		cell->setSpacing(0);
		cell->setMargin(0);
		cell->addWidget(script_);
		frame->setLayout(cell);
		
		QMenu* editMenu = script_->edit()->contextMenu();
		editMenu->addSeparator();
		QMenu* substMenu = editMenu->addMenu(tr("Insert $SUBST"));
		const char* substNames[] = {
			"$DIRPATH", "$DIRNAME",
			"$FILEPATH", "$FILENAME", "$FILEID", "$FILEEXT",
			"$TEXT", "$WORD", "$CURSOR_LINE", "$CURSOR_COLUMN", "$OFFSET"
		};
		for (int i = 0, n = sizeof(substNames) / sizeof(const char*); i < n; ++i)
			substMenu->addAction(substNames[i]);
		connect(substMenu, SIGNAL(triggered(QAction*)), this, SLOT(substTriggered(QAction*)));
		
		col->addWidget(frame);
	}
	{
		QDialogButtonBox* box = new QDialogButtonBox(
			QDialogButtonBox::Ok | QDialogButtonBox::Cancel
		);
		connect(box, SIGNAL(accepted()), this, SLOT(accept()));
		connect(box, SIGNAL(rejected()), this, SLOT(reject()));
		col->addWidget(box);
	}
	setLayout(col);
	
	// design HACK
	resize(parent->size() * 1.2);
	
	connect(this, SIGNAL(accepted()), this, SLOT(updateCommand()));
}