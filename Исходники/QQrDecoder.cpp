QQrDecoder::QQrDecoder(QWidget *parent): QMainWindow(parent), decoder(this)
{
    ui.setupUi(this);
    connect(ui.centralwidget, SIGNAL(imageCaptured(QImage)), this, SLOT(decodeImage(QImage)));
    connect(&decoder, SIGNAL(tagFound(QString)), this, SLOT(reportTagFound(QString)));
	
	//by default all decoders available are enabled
    //decoder.setDecoder( QZXing::DecoderFormat_DATA_MATRIX);
    //decoder.setDecoder( QZXing::DecoderFormat_Aztec );
}