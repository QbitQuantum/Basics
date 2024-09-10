subMainWindow::subMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    createMenu();
    subImageLabel = new QLabel;
    subImageLabel->setBackgroundRole(QPalette::NoRole);
    subImageLabel->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    subImageLabel->setScaledContents(true); //选择自动适应框的变化，就是无论将对话框，缩小放大都不影响像素，作用在看图片的时候，图片的像素会跟着相框调整

    subScrollArea = new QScrollArea;       //滚动区域
    subScrollArea->setBackgroundRole(QPalette::Dark);
    subScrollArea->setWidget(subImageLabel);

    backImage = QImage();


    setCentralWidget(subScrollArea);
    setWindowTitle(tr("处理后的图片"));
    resize(600,500);
}