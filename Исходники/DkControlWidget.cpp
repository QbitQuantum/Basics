void DkControlWidget::init() {

	// debug: show invisible widgets
	setFocusPolicy(Qt::StrongFocus);
	setFocus(Qt::TabFocusReason);
	setMouseTracking(true);

	// connect widgets with their settings
	mFilePreview->setDisplaySettings(&Settings::param().app().showFilePreview);
	mMetaDataInfo->setDisplaySettings(&Settings::param().app().showMetaData);
	mFileInfoLabel->setDisplaySettings(&Settings::param().app().showFileInfoLabel);
	mPlayer->setDisplaySettings(&Settings::param().app().showPlayer);
	mHistogram->setDisplaySettings(&Settings::param().app().showHistogram);
	mCommentWidget->setDisplaySettings(&Settings::param().app().showComment);
	mZoomWidget->setDisplaySettings(&Settings::param().app().showOverview);
	mFolderScroll->setDisplaySettings(&Settings::param().app().showScroller);

	// some adjustments
	mBottomLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	mBottomLeftLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	mRatingLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	mZoomWidget->setContentsMargins(10, 10, 0, 0);
	mCropWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	mCommentWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

	// register actions
	DkActionManager& am = DkActionManager::instance();
	mFilePreview->registerAction(am.action(DkActionManager::menu_panel_preview));
	mMetaDataInfo->registerAction(am.action(DkActionManager::menu_panel_exif));
	mPlayer->registerAction(am.action(DkActionManager::menu_panel_player));
	mCropWidget->registerAction(am.action(DkActionManager::menu_edit_crop));
	mFileInfoLabel->registerAction(am.action(DkActionManager::menu_panel_info));
	mHistogram->registerAction(am.action(DkActionManager::menu_panel_histogram));
	mCommentWidget->registerAction(am.action(DkActionManager::menu_panel_comment));
	mFolderScroll->registerAction(am.action(DkActionManager::menu_panel_scroller));

	// dummy - needed for three equal columns @markus: do not delete!
	QWidget* dw = new QWidget(this);
	dw->setMouseTracking(true);
	QBoxLayout* dLayout = new QBoxLayout(QBoxLayout::LeftToRight, dw);
	dLayout->setContentsMargins(0,0,0,0);
	dLayout->addWidget(mBottomLabel);
	dLayout->addStretch();

	// zoom widget
	QWidget* bw = new QWidget(this);
	bw->setMouseTracking(true);
	//bw->setMinimumHeight(40);
	//bw->setMaximumHeight(80);
	QVBoxLayout* zLayout = new QVBoxLayout(bw);
	zLayout->setAlignment(Qt::AlignBottom);
	zLayout->setContentsMargins(0,0,0,20);
	zLayout->setSpacing(0);
	zLayout->addWidget(mBottomLabel);
	zLayout->addWidget(mBottomLeftLabel);
	zLayout->addWidget(mCommentWidget);

	// left column widget
	QWidget* leftWidget = new QWidget(this);
	leftWidget->setMouseTracking(true);
	QBoxLayout* ulLayout = new QBoxLayout(QBoxLayout::TopToBottom, leftWidget);
	ulLayout->setContentsMargins(0,0,0,0);
	ulLayout->setSpacing(0);
	ulLayout->addWidget(mZoomWidget);
	ulLayout->addStretch();
	ulLayout->addWidget(bw);
	ulLayout->addWidget(dw);

	// center column
	QWidget* center = new QWidget(this);
	center->setMouseTracking(true);
	QVBoxLayout* cLayout = new QVBoxLayout(center);
	cLayout->setContentsMargins(0,0,0,0);
	cLayout->setAlignment(Qt::AlignBottom);
	cLayout->addWidget(mPlayer);
	
	// rating widget
	QWidget* rw = new QWidget(this);
	rw->setMouseTracking(true);
	rw->setMinimumSize(0,0);
	QBoxLayout* rLayout = new QBoxLayout(QBoxLayout::RightToLeft, rw);
	rLayout->setContentsMargins(0,0,0,17);
	rLayout->addWidget(mRatingLabel);
	rLayout->addStretch();

	// file info
	QWidget* fw = new QWidget(this);
	fw->setContentsMargins(0,0,0,30);
	fw->setMouseTracking(true);
	fw->setMinimumSize(0,0);
	QBoxLayout* rwLayout = new QBoxLayout(QBoxLayout::RightToLeft, fw);
	rwLayout->setContentsMargins(0,0,0,0);
	rwLayout->addWidget(mFileInfoLabel);
	rwLayout->addStretch();

	// right column
	QWidget* hw = new QWidget(this);
	hw->setContentsMargins(0,10,10,0);
	hw->setMouseTracking(true);
	QBoxLayout* hwLayout = new QBoxLayout(QBoxLayout::RightToLeft, hw);
	hwLayout->setContentsMargins(0,0,0,0);
	hwLayout->addWidget(mHistogram);
	hwLayout->addStretch();

	// right column
	QWidget* rightWidget = new QWidget(this);
	rightWidget->setMouseTracking(true);
	QBoxLayout* lrLayout = new QBoxLayout(QBoxLayout::TopToBottom, rightWidget);
	lrLayout->setContentsMargins(0,0,0,0);
	lrLayout->addWidget(hw);
	lrLayout->addStretch();
	lrLayout->addWidget(fw);
	lrLayout->addWidget(rw);
	
	// init main widgets
	mWidgets.resize(widget_end);
	mWidgets[hud_widget] = new QWidget(this);
	mWidgets[crop_widget] = mCropWidget;

	// global controller layout
	mHudLayout = new QGridLayout(mWidgets[hud_widget]);
	mHudLayout->setContentsMargins(0,0,0,0);
	mHudLayout->setSpacing(0);

	//hudLayout->addWidget(thumbWidget, 0, 0);

	// add elements
	changeThumbNailPosition(mFilePreview->getWindowPosition());
	changeMetaDataPosition(mMetaDataInfo->getWindowPosition());
	//hudLayout->addWidget(filePreview, top_thumbs, left_thumbs, 1, hor_pos_end);
	mHudLayout->addWidget(leftWidget, ver_center, left, 1, 1);
	mHudLayout->addWidget(center, ver_center, hor_center, 1, 1);
	mHudLayout->addWidget(rightWidget, ver_center, right, 1, 1);
	mHudLayout->addWidget(mFolderScroll, top_scroll, left_thumbs, 1, hor_pos_end);

	//// we need to put everything into extra widgets (which are exclusive) in order to handle the mouse events correctly
	//QHBoxLayout* editLayout = new QHBoxLayout(widgets[crop_widget]);
	//editLayout->setContentsMargins(0,0,0,0);
	//editLayout->addWidget(cropWidget);

	mLayout = new QStackedLayout(this);
	mLayout->setContentsMargins(0,0,0,0);
	
	for (int idx = 0; idx < mWidgets.size(); idx++)
		mLayout->addWidget(mWidgets[idx]);

	//// debug code...
	//centerLabel->setText("ich bin richtig...", -1);
	//bottomLeftLabel->setText("topLeft label...", -1);
	//spinnerLabel->show();
	
	show();
	//thumbWidget->setVisible(true);
}