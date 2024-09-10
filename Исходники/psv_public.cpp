void PSV_Public::printMes(const QVariant &mes, const QString &frefix)
{    
    QString message;
    int type = mes.type();
    switch(type)
    {
    case QVariant::Bool :
        message = mes.toBool() ? "true":"false";
        break;
    case QVariant::Color :
    {
        QColor color = mes.value<QColor>();
        message = QObject::tr("colorname:%1,r=%2,g=%3,b=%4")
                .arg(color.name())
                .arg(color.red())
                .arg(color.green())
                .arg(color.blue());
    }
        break;
    case QVariant::Date:
        message = mes.toDate().toString("yyyy-MM-dd");
        break;
    case QVariant::DateTime:
        message = mes.toDateTime().toString("yyyy-MM-dd hh:mm:ss");
        break;
    case QVariant::Double:
        message = QString::number(mes.toDouble());
        break;
    case QVariant::UInt:
    case QVariant::Int:
        message = QString::number(mes.toInt());
        break;
    case QVariant::ULongLong:
    case QVariant::LongLong:
        message = QString::number(mes.toLongLong());
        break;
    case QVariant::Line:
    {
        QLine line = mes.toLine();
        message = QObject::tr("Line x1=%1,y1=%2,x2=%3,y2=%4")
                .arg(line.x1()).arg(line.y1()).arg(line.x2()).arg(line.y2());
    }
        break;
    case QVariant::LineF:
    {
        QLineF lineF = mes.toLineF();
        message = QObject::tr("LineF x1=%1,y1=%2,x2=%3,y2=%4")
                .arg(lineF.x1()).arg(lineF.y1()).arg(lineF.x2()).arg(lineF.y2());
    }
        break;
    case QVariant::Point:
    {
        QPoint point = mes.toPoint();
        message = QObject::tr("point x=%1,y=%2")
                .arg(point.x()).arg(point.y());
    }
        break;
    case QVariant::PointF:
    {
        QPointF pointF = mes.toPointF();
        message = QObject::tr("pointF x=%1,y=%2")
                .arg(pointF.x()).arg(pointF.y());
    }
        break;
    case QVariant::Rect:
    {
        QRect rect = mes.toRect();
        message = QObject::tr("rect x=%1,y=%2,width=%3,height=%4")
                .arg(rect.x()).arg(rect.y()).arg(rect.width()).arg(rect.height());
    }
        break;
    case QVariant::RectF:
    {
        QRectF rectF = mes.toRect();
        message = QObject::tr("rectF x=%1,y=%2,width=%3,height=%4")
                .arg(rectF.x()).arg(rectF.y()).arg(rectF.width()).arg(rectF.height());
    }
        break;

    default:
        message = QObject::tr("type = %1,<%2>").arg(type).arg(mes.toString());
        break;
    }
    QString outMes = QObject::tr("%1 %2").arg(frefix).arg(message);

    qDebug()<<QObject::tr("PSV_LIB:<%1>%2").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(outMes);
}