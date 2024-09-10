void AdvancedImageWidget::drawResized(QPainter &painter)
{
    //qDebug("AdvancedImageWidget::drawResized():called");
    if (mImage.isNull())
    {
        qDebug("AdvancedImageWidget::drawResized():image is null");

        painter.drawText(0,0, this->width(), this->height(), Qt::AlignHCenter | Qt::AlignVCenter, QString("NO ACTIVE IMAGE"));
        return;
    }

    if (mUi->rotationComboBox->currentIndex() == 0)
    {
        painter.drawImage(mOutputRect, *mImage, mInputRect);
        return;
    }

//    qDebug() << "Input"  << mInputRect;
//    qDebug() << "Output" << mOutputRect;


    Matrix33 matrix = currentTransformMatrix();
//    cout << "Transfrom Matrix:\n" << matrix << std::endl << std::flush;
    QTransform transform = Core2Qt::QTransformFromMatrix(matrix);
//    qDebug() << "QTransfrom" << transform;



    QTransform old = painter.transform();
    painter.setTransform(transform, false);

    painter.drawImage(mOutputRect.topLeft(), *mImage, mImage->rect());

#if 0
    painter.setPen(Qt::red);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            painter.drawPoint(i * 64, j * 48);
        }
    }
#endif

    painter.setTransform(old);

}