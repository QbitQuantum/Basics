void ColorPickerForm::makeColor()
{
    QSize size = ui->label_color->size();
    QImage img = QImage(size, QImage::Format_ARGB32);

    int div = size.height() / 6;
    for (int i = 0; i < size.height(); i++)
    {
        QColor col = QColor(0, 0, 0);
        switch (i / div)
        {
            case 0:
                col.setRedF(1);
                col.setBlueF(1.0 - (float)(div - (i - div * 0)) / div);
                break;
            case 1:
                col.setBlueF(1);
                col.setRedF((float)(div - (i - div * 1)) / div);
                break;
            case 2:
                col.setBlueF(1);
                col.setGreenF(1.0 - (float)(div - (i - div * 2)) / div);
                break;
            case 3:
                col.setGreenF(1);
                col.setBlueF((float)(div - (i - div * 3)) / div);
                break;
            case 4:
                col.setGreenF(1);
                col.setRedF(1.0 - (float)(div - (i - div * 4)) / div);
                break;
            case 5:
                col.setRedF(1);
                col.setGreenF((float)(div - (i - div * 5)) / div);
                break;
        }
        for (int j = 0; j < size.width(); j++)
        {
            img.setPixel(j, i, col.rgba());
        }
    }
    ui->label_color->setPixmap(QPixmap::fromImage(img));
}