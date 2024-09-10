void ValueSlider::
        setOrientation( Qt::Orientation orientation )
{
    if (orientation != this->orientation())
    {
        QSize sz = slider_->size ();
        slider_->setOrientation ( orientation );
        sz.transpose ();
        slider_->resize (sz);
    }
}