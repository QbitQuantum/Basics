void LabyrinthParser::mouseMoveEvent(QMouseEvent * e) {
    __carring = section(__mouse);
    switch (__carring) {
    case Qt::BottomSection: case Qt::TopSection:
        this->setCursor(QCursor(Qt::SizeVerCursor));
        break;
    case Qt::LeftSection: case Qt::RightSection:
        this->setCursor(QCursor(Qt::SizeHorCursor));
        break;
    case Qt::BottomLeftSection: case Qt::TopRightSection:
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
        break;
    case Qt::TopLeftSection: case Qt::BottomRightSection:
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
        break;
    case Qt::TitleBarArea:
        this->setCursor(QCursor(Qt::SizeAllCursor));
        break;
    case Qt::NoSection: default:
        this->setCursor(QCursor(Qt::ArrowCursor));
        break;
    }

    const QPoint delta(e->pos() - __mouse);
    __mouse = e->pos();
    if (e->buttons() & Qt::LeftButton) {
        switch (__carring) {
        case Qt::LeftSection:
            __rect.setLeft(__rect.left() + delta.x());
            break;
        case Qt::RightSection:
            __rect.setRight(__rect.right() + delta.x());
            break;
        case Qt::TopSection:
            __rect.setTop(__rect.top() + delta.y());
            break;
        case Qt::BottomSection:
            __rect.setBottom(__rect.bottom() + delta.y());
            break;
        case Qt::TopLeftSection:
            __rect.setTopLeft(__rect.topLeft() + delta);
            break;
        case Qt::TopRightSection:
            __rect.setTopRight(__rect.topRight() + delta);
            break;
        case Qt::BottomLeftSection:
            __rect.setBottomLeft(__rect.bottomLeft() + delta);
            break;
        case Qt::BottomRightSection:
            __rect.setBottomRight(__rect.bottomRight() + delta);
            break;
        case Qt::TitleBarArea:
            __rect.moveTo(__rect.topLeft() + delta);
            break;
        default:
            break;
        }
        __rect = __rect.normalized();
        this->repaint();

        const Labyrinth currentLabyrint(Labyrinth::fromImage(__labyrint.copy(roundedRect())));
        if (currentLabyrint.size() != QSize()) {
            emit newLabyrinthAppeared(currentLabyrint);
        }
    }
}