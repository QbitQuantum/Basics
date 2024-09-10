void SequenceDialog::mouseMoved(QMouseEvent *event)
{
    QCustomPlot *sp = ui->sequencePlot;
    Qt::CursorShape shape = Qt::ArrowCursor;
    if (event) {
        if (event->buttons().testFlag(Qt::LeftButton)) {
            shape = Qt::ClosedHandCursor;
        } else {
            if (sp->axisRect()->rect().contains(event->pos())) {
                shape = Qt::OpenHandCursor;
            }
        }
    }
    sp->setCursor(QCursor(shape));

    packet_num_ = 0;
    QString hint;
    if (event) {
        seq_analysis_item_t *sai = seq_diagram_->itemForPosY(event->pos().y());
        if (sai) {
            packet_num_ = sai->fd->num;
            hint = QString("Packet %1: %2").arg(packet_num_).arg(sai->comment);
        }
    }

    if (hint.isEmpty()) {
        hint += tr("%Ln node(s)", "", seq_analysis_.num_nodes) + QString(", ")
                + tr("%Ln item(s)", "", num_items_);
    }

    hint.prepend("<small><i>");
    hint.append("</i></small>");
    ui->hintLabel->setText(hint);
}