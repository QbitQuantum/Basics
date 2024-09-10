// Setting mouseTracking on our streamPlot may not be as reliable
// as we need. If it's not we might want to poll the mouse position
// using a QTimer instead.
void TCPStreamDialog::mouseMoved(QMouseEvent *event)
{
    QCustomPlot *sp = ui->streamPlot;
    Qt::CursorShape shape = Qt::ArrowCursor;
    if (event) {
        if (event->buttons().testFlag(Qt::LeftButton)) {
            if (mouse_drags_) {
                shape = Qt::ClosedHandCursor;
            } else {
                shape = Qt::CrossCursor;
            }
        } else {
            if (sp->axisRect()->rect().contains(event->pos())) {
                if (mouse_drags_) {
                    shape = Qt::OpenHandCursor;
                } else {
                    shape = Qt::CrossCursor;
                }
            }
        }
    }
    sp->setCursor(QCursor(shape));

    QString hint = "<small><i>";
    if (mouse_drags_) {
        double tr_key = tracer_->position->key();
        struct segment *packet_seg = NULL;
        packet_num_ = 0;

        // XXX If we have multiple packets with the same timestamp tr_key
        // may not return the packet we want. It might be possible to fudge
        // unique keys using nextafter().
        if (event && tracer_->graph() && tracer_->position->axisRect()->rect().contains(event->pos())) {
            switch (graph_.type) {
            case GRAPH_TSEQ_STEVENS:
            case GRAPH_TSEQ_TCPTRACE:
            case GRAPH_THROUGHPUT:
            case GRAPH_WSCALE:
                packet_seg = time_stamp_map_.value(tr_key, NULL);
                break;
            case GRAPH_RTT:
                packet_seg = sequence_num_map_.value(tr_key, NULL);
            default:
                break;
            }
        }

        if (!packet_seg) {
            tracer_->setVisible(false);
            hint += "Hover over the graph for details. " + stream_desc_ + "</i></small>";
            ui->hintLabel->setText(hint);
            ui->streamPlot->replot();
            return;
        }

        tracer_->setVisible(true);
        packet_num_ = packet_seg->num;
        hint += tr("%1 %2 (%3s len %4 seq %5 ack %6 win %7)")
                .arg(cap_file_ ? tr("Click to select packet") : tr("Packet"))
                .arg(packet_num_)
                .arg(QString::number(packet_seg->rel_secs + packet_seg->rel_usecs / 1000000.0, 'g', 4))
                .arg(packet_seg->th_seglen)
                .arg(packet_seg->th_seq)
                .arg(packet_seg->th_ack)
                .arg(packet_seg->th_win);
        tracer_->setGraphKey(ui->streamPlot->xAxis->pixelToCoord(event->pos().x()));
        sp->replot();
    } else {
        if (rubber_band_ && rubber_band_->isVisible() && event) {
            rubber_band_->setGeometry(QRect(rb_origin_, event->pos()).normalized());
            QRectF zoom_ranges = getZoomRanges(QRect(rb_origin_, event->pos()));
            if (zoom_ranges.width() > 0.0 && zoom_ranges.height() > 0.0) {
                hint += tr("Release to zoom, x = %1 to %2, y = %3 to %4")
                        .arg(zoom_ranges.x())
                        .arg(zoom_ranges.x() + zoom_ranges.width())
                        .arg(zoom_ranges.y())
                        .arg(zoom_ranges.y() + zoom_ranges.height());
            } else {
                hint += tr("Unable to select range.");
            }
        } else {
            hint += tr("Click to select a portion of the graph.");
        }
    }
    hint += " " + stream_desc_ + "</i></small>";
    ui->hintLabel->setText(hint);
}