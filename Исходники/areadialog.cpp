AreaDialog::AreaDialog(Screenshot *screenshot) :
  QDialog(0), mScreenshot(screenshot), mMouseDown(false), mMouseMagnifier(false),
  mNewSelection(false),  mHandleSize(10), mMouseOverHandle(0), mIdleTimer(),
  mShowHelp(true), mGrabbing(false), mOverlayAlpha(1), mAutoclose(false),
  mTLHandle(0, 0, mHandleSize, mHandleSize), mTRHandle(0, 0, mHandleSize, mHandleSize),
  mBLHandle(0, 0, mHandleSize, mHandleSize), mBRHandle(0, 0, mHandleSize, mHandleSize),
  mLHandle(0, 0, mHandleSize, mHandleSize), mTHandle(0, 0, mHandleSize, mHandleSize),
  mRHandle(0, 0, mHandleSize, mHandleSize), mBHandle(0, 0, mHandleSize, mHandleSize)
{
  mHandles << &mTLHandle << &mTRHandle << &mBLHandle << &mBRHandle
           << &mLHandle << &mTHandle << &mRHandle << &mBHandle;

  mMouseOverHandle = 0;

  setMouseTracking(true);
  setWindowTitle(tr("Lightscreen Area Mode"));
  setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);

  setCursor(Qt::CrossCursor);

  connect(&mIdleTimer, SIGNAL(timeout()), this, SLOT(displayHelp()));
  mIdleTimer.start(2000);

  mAutoclose = ScreenshotManager::instance()->settings()->value("options/areaAutoclose").toBool();

  if (mAutoclose)
    return; // Avoid creating the accept widget if it's not going to get used.

  // Creating accept widget:
  mAcceptWidget = new QWidget(this);
  mAcceptWidget->resize(140, 70);
  mAcceptWidget->setWindowOpacity(0.4);
  mAcceptWidget->setStyleSheet("QWidget { background: rgba(255, 255, 255, 200); border: 4px solid #232323; padding: 0; } QPushButton { background: transparent; border: none; height: 50px; padding: 5px; } QPushButton:hover { cursor: hand; }");

  QPushButton *awAcceptButton = new QPushButton(QIcon(":/icons/yes.big"), "", this);
  connect(awAcceptButton, SIGNAL(clicked()), this, SLOT(grabRect()));
  awAcceptButton->setCursor(Qt::PointingHandCursor);
  awAcceptButton->setIconSize(QSize(48, 48));

  QPushButton *awRejectButton = new QPushButton(QIcon(":/icons/no.big"), "", this);
  connect(awRejectButton, SIGNAL(clicked()), this, SLOT(cancel()));
  awRejectButton->setCursor(Qt::PointingHandCursor);
  awRejectButton->setIconSize(QSize(48, 48));

  QHBoxLayout *awLayout = new QHBoxLayout(this);
  awLayout->addWidget(awAcceptButton);
  awLayout->addWidget(awRejectButton);
  awLayout->setMargin(0);
  awLayout->setSpacing(0);

  mAcceptWidget->setLayout(awLayout);
  mAcceptWidget->setVisible(false);
}