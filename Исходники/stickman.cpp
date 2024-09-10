//#include <QTime>
void StickMan::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
  /*  static int frames = 0;
    static QTime time;
    if (frames++ % 100 == 0) {
        frames = 1;
        time.restart();
    }

    if (time.elapsed() > 0) {
        painter->setPen(Qt::white);
        painter->drawText(0, 0, QString::number(frames / (time.elapsed() / 1000.0)));
    }*/

    stabilize();
    if (m_sticks) {
        painter->setPen(Qt::white);
        for (int i=0; i<BoneCount; ++i) {
            int n1 = Bones[i * 2];
            int n2 = Bones[i * 2 + 1];

            Node *node1 = m_nodes[n1];
            Node *node2 = m_nodes[n2];

            painter->drawLine(node1->pos(), node2->pos());
        }
    } else {
        // first bone is neck and will be used for head

        QPainterPath path;
        path.moveTo(posFor(0));
        path.lineTo(posFor(1));

        // right arm
        path.lineTo(posFor(2));
        path.lineTo(posFor(6));
        path.lineTo(posFor(7));

        // left arm
        path.moveTo(posFor(3));
        path.lineTo(posFor(8));
        path.lineTo(posFor(9));

        // body
        path.moveTo(posFor(2));
        path.lineTo(posFor(4));
        path.lineTo(posFor(10));
        path.lineTo(posFor(11));
        path.lineTo(posFor(5));
        path.lineTo(posFor(3));
        path.lineTo(posFor(1));

        // right leg
        path.moveTo(posFor(10));
        path.lineTo(posFor(12));
        path.lineTo(posFor(13));

        // left leg
        path.moveTo(posFor(11));
        path.lineTo(posFor(14));
        path.lineTo(posFor(15));

        painter->setPen(QPen(m_penColor, 5.0, Qt::SolidLine, Qt::RoundCap));
        painter->drawPath(path);

        {
            int n1 = Bones[0];
            int n2 = Bones[1];
            Node *node1 = m_nodes[n1];
            Node *node2 = m_nodes[n2];

            QPointF dist = node2->pos() - node1->pos();

            qreal sinAngle = dist.x() / sqrt(pow(dist.x(), 2) + pow(dist.y(), 2));
            qreal angle = asin(sinAngle) * 180.0 / M_PI;

            QPointF headPos = node1->pos();
            painter->translate(headPos);
            painter->rotate(-angle);

            painter->setBrush(m_fillColor);
            painter->drawEllipse(QPointF(0,0), 50.0, 50.0);

            painter->setBrush(m_penColor);
            painter->setPen(QPen(m_penColor, 2.5, Qt::SolidLine, Qt::RoundCap));

            // eyes
            if (m_isDead) {
                painter->drawLine(-30.0, -30.0, -20.0, -20.0);
                painter->drawLine(-20.0, -30.0, -30.0, -20.0);

                painter->drawLine(20.0, -30.0, 30.0, -20.0);
                painter->drawLine(30.0, -30.0, 20.0, -20.0);
            } else {
                painter->drawChord(QRectF(-30.0, -30.0, 25.0, 70.0), 30.0*16, 120.0*16);
                painter->drawChord(QRectF(5.0, -30.0, 25.0, 70.0), 30.0*16, 120.0*16);
            }

            // mouth
            if (m_isDead) {
                painter->drawLine(-28.0, 2.0, 29.0, 2.0);
            } else {
                painter->setBrush(QColor(128, 0, 64 ));
                painter->drawChord(QRectF(-28.0, 2.0-55.0/2.0, 57.0, 55.0), 0.0, -180.0*16);
            }

            // pupils
            if (!m_isDead) {
                painter->setPen(QPen(m_fillColor, 1.0, Qt::SolidLine, Qt::RoundCap));
                painter->setBrush(m_fillColor);
                painter->drawEllipse(QPointF(-12.0, -25.0), 5.0, 5.0);
                painter->drawEllipse(QPointF(22.0, -25.0), 5.0, 5.0);
            }
        }
    }
}