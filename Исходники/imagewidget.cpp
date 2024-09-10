void ImageWidget::makeTransformation(Transform d)
{
    qDebug() << "make transformation:" << d;

    QTransform transformation;
    QSize f = pixmap.size();

    switch (d) {
        case toLeft:
            transformation.rotate(-90);
            pixmap = pixmap.transformed(transformation);
            imageLabel->setPixmap(pixmap);
            f.transpose();
            imageLabel->resize(f);
            this->adjustSize();
            emit picSizeChanged();
            break;
        case toRight:
            transformation.rotate(90);
            pixmap = pixmap.transformed(transformation);
            imageLabel->setPixmap(pixmap);
            f.transpose();
            imageLabel->resize(f);
            this->adjustSize();
            emit picSizeChanged();
            break;
        case horizontally:
            transformation.scale(-1, 1);
            pixmap = pixmap.transformed(transformation);
            imageLabel->setPixmap(pixmap);
            break;
        case vertically:
            transformation.scale(1, -1);
            pixmap = pixmap.transformed(transformation);
            imageLabel->setPixmap(pixmap);
            break;
    }

    emit pixmapChanged();

    if (scaleFactor != 1) {
        imageLabel->resize(pixmap.size() * scaleFactor);
        this->resize((pixmap.size() + bugSize) * scaleFactor);
    }

}