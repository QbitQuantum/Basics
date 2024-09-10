void population::draw(QPainter *painter, float GLscale, float viewX, float viewY, int width, int height, QImage image, drawStyle style)
{
    float scale = GLscale/200.0;

    this->setupTrans(GLscale, viewX, viewY, width, height);

    if (this->isSpikeSource) {
        style = spikeSourceDrawStyle;
    }

    switch (style) {
    case microcircuitDrawStyle:
    {
        // draw circle
        QPen oldPen = painter->pen();
        QPen pen = painter->pen();
        pen.setWidthF((pen.widthF()+1.0)*2*scale);
        painter->setPen(pen);
        painter->drawEllipse(transformPoint(QPointF(this->x, this->y)),0.5*GLscale/2.0,0.5*GLscale/2.0);
        painter->setPen(oldPen);
        QFont oldFont = painter->font();
        QFont font = painter->font();
        font.setPointSizeF(GLscale/10.0);
        painter->setFont(font);
        // print label
        QStringList text = this->name.split(" ");
        if (text.size()>0) {
            QString title = text.at(0);
            if (title.size() > 5)
                title.resize(5);
            painter->drawText(QRectF(transformPoint(QPointF(this->x-0.5, this->y-0.2)),transformPoint(QPointF(this->x+0.5, this->y+0.2))), Qt::AlignCenter, title);
            painter->setFont(oldFont);
        }
        return;
    }
    case layersDrawStyle:
    {
        return;
    }
    case spikeSourceDrawStyle:
    {
        // draw circle
        QPen oldPen = painter->pen();
        QPen pen = painter->pen();
        pen.setWidthF((pen.widthF()+1.0));//*GLscale/100.0
        pen.setColor(QColor(200,200,200,0));
        painter->setPen(pen);
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        QColor col(this->colour);
        col.setAlpha(100);
        brush.setColor(col);
        QBrush oldBrush = painter->brush();
        painter->setBrush(brush);
        painter->drawEllipse(transformPoint(QPointF(this->x, this->y)),0.5*GLscale/2.0,0.5*GLscale/2.0);
        QFont oldFont = painter->font();
        QFont font = painter->font();
        font.setPointSizeF(GLscale/10.0);
        painter->setFont(font);
        // print label
        pen.setColor(QColor(0,0,0,255));
        painter->setPen(pen);
        //painter->drawText(QRectF(transformPoint(QPointF(this->x-0.5, this->y-0.2)),transformPoint(QPointF(this->x+0.5, this->y+0.2))), Qt::AlignCenter, "SS");
        painter->setFont(oldFont);
        painter->setBrush(oldBrush);
        painter->setPen(oldPen);
        QImage ssimage(":/images/ssBig.png");
        QRectF imRect(transformPoint(QPointF(this->x, this->y))-QPointF(0.4*GLscale/2.0,0.4*GLscale/2.0),QSizeF(0.4*GLscale,0.4*GLscale));
        painter->drawImage(imRect, ssimage);
        return;
        break;
    }
    case standardDrawStyle:
    case standardDrawStyleExcitatory:
    case saveNetworkImageDrawStyle:
    default:
        // do nothing here, break out into the code below.
        break;
    }

    // transform the co-ordinates manually (using the qt transformation leads to blurry fonts!)
    float left = ((this->left+viewX)*GLscale+float(width))/2;
    float right = ((this->right+viewX)*GLscale+float(width))/2;
    float top = ((-this->top+viewY)*GLscale+float(height))/2;
    float bottom = ((-this->bottom+viewY)*GLscale+float(height))/2;

    QRectF rectangle(left, top, right-left, bottom-top);

    QRectF rectangleInner(left+2*scale, top+2*scale, right-left-8*scale, bottom-top-4*scale);

    QColor col(this->colour);
    col.setAlpha(100);
    QPainterPath path;
    path.addRoundedRect(rectangle,0.05*GLscale,0.05*GLscale);

    painter->fillPath(path, col);

    painter->drawImage(rectangle, image);

    // Draw a dark grey border around the population
    painter->setPen(QColor(200,200,200,255));
    painter->drawRoundedRect(rectangle,0.05*GLscale,0.05*GLscale);
    painter->setPen(QColor(0,0,0,255));

    QString displayed_name = this->name;

    if (displayed_name.size() > 13) {
        displayed_name.resize(10);
        displayed_name = displayed_name + "...";
    }

    QString displayed_comp_name = this->neuronType->component->name;

    if (displayed_comp_name.size() > 14) {
        displayed_comp_name.resize(11);
        displayed_comp_name = displayed_comp_name + "...";
    }

    QFont oldFont = painter->font();
    QFont font = painter->font();

    QString text = displayed_name + "\n" + QString::number(this->numNeurons);// + "\n" + displayed_comp_name;
    font.setPointSizeF(1.5*GLscale/20.0);
    painter->setFont(font);
    painter->drawText(rectangleInner, Qt::AlignRight|Qt::AlignTop, text);

    font.setPointSizeF(1.3*GLscale/20.0);
    painter->setFont(font);
    painter->setPen(QColor(60,60,60,255));
    painter->drawText(rectangleInner, Qt::AlignRight|Qt::AlignBottom, displayed_comp_name);

    painter->setFont(oldFont);
}