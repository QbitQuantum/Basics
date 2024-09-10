void ThresholdDialog::updatePreview(){

    if(_previewBox->isChecked()){
        Binarization_t<GrayscaleImage::depth_t>* algo;
        if(doubleThreshold()) {
            algo = new Binarization_t<GrayscaleImage::depth_t>(_spinbox1->value(), _spinbox2->value(), !_blackButton->isChecked());
        }
        else {
            algo = new Binarization_t<GrayscaleImage::depth_t>(_spinbox1->value());
        }
        _previewImage = algo->operator()(_image);
        _preview->setImage(_previewImage);
        delete algo;
        delete _previewImage;
        _preview->repaint();
    }


 }