// Forme englobante
QRectF Mur::boundingRect() const
{
    QRectF boite;

    switch(mur_)
    {
        case 0 :
            boite.setRect(scene()->width() - 50, 50, 1, scene()->height() - 100);
            break;

        case 1 :
            boite.setRect(50, scene()->height() - 50, scene()->width() - 100, 1);
            break;

        case 2 :
            boite.setRect(50, 50, 1, scene()->height() - 100);
            break;

        case 3 :
            boite.setRect(50, 50, scene()->width() - 100, 1);
            break;
    }

    return boite;
}