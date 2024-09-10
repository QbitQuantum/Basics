void ThresholdOp::operator()(const imagein::Image* image, const std::map<const imagein::Image*, std::string>&) {
    const GrayscaleImage* img = dynamic_cast<const GrayscaleImage*>(image);
    bool convert = (img == NULL);

    if(convert) {
        img = Converter<GrayscaleImage>::convert(*image);
    }

    ThresholdDialog* dialog = new ThresholdDialog(img, convert);


    if(_test && _testotsu){
      dialog->otsu();
    }
    else if(_test){
      dialog->setSpinBox1(_testThreshold1);
      if(_testThreshold2!=-1){
        dialog->doubleThreshold(true);
        dialog->setSpinBox2(_testThreshold2);

      }
    }
    else{
        QDialog::DialogCode code = static_cast<QDialog::DialogCode>(dialog->exec());
        if(code!=QDialog::Accepted) {
            return;
        }
    }




    Binarization_t<GrayscaleImage::depth_t>* algo;
    if(dialog->doubleThreshold()) {
        algo = new Binarization_t<GrayscaleImage::depth_t>(dialog->threshold1(),dialog->threshold2(), dialog->blackBand());
    }
    else {
        algo = new Binarization_t<GrayscaleImage::depth_t>(dialog->threshold1());
    }

    GrayscaleImage* resImg = algo->operator()(img);
    delete algo;
    this->outImage(resImg);
}