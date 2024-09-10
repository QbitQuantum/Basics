QtBarcodeReader::QtBarcodeReader(QObject *parent,QWidget *viewer) :
    QObject(parent)
{
    qRegisterMetaType<cv::Mat>("cv::Mat");
    converter.setProcessAll(false);    
    cvcapture= new CVCapture();
    converter.connect(cvcapture, SIGNAL(matReady(cv::Mat)), SLOT(processFrame(cv::Mat)));
    BarcodeDecoder.connect(&converter, SIGNAL(imageReady(QImage)), SLOT(decodeImage(QImage)));
    connect(&BarcodeDecoder,SIGNAL(BarcodeDecodeStatus(BARCODESTATUS,QString)),this, SLOT(NewBarcodeDecodeStatus(BARCODESTATUS,QString)));

    if (viewer!=0) {
        viewer->connect(&converter, SIGNAL(imageReady(QImage)), SLOT(setImage(QImage)));
    }



}