void LteRlcGraphDialog::mouseMoved(QMouseEvent *event)
{
    QCustomPlot *rp = ui->rlcPlot;
    Qt::CursorShape shape = Qt::ArrowCursor;

    // Set the cursor shape.
    if (event) {
        if (event->buttons().testFlag(Qt::LeftButton)) {
            if (mouse_drags_) {
                shape = Qt::ClosedHandCursor;
            } else {
                shape = Qt::CrossCursor;
            }
        } else if (rp->axisRect()->rect().contains(event->pos())) {
            if (mouse_drags_) {
                shape = Qt::OpenHandCursor;
            } else {
                shape = Qt::CrossCursor;
            }
        }
        rp->setCursor(QCursor(shape));
    }

    // Trying to let 'hint' grow efficiently.  Still pretty slow for a dense graph...
    QString hint;
    hint.reserve(128);
    hint = "<small><i>";

    if (mouse_drags_) {
        double tr_key = tracer_->position->key();
        struct rlc_segment *packet_seg = NULL;
        packet_num_ = 0;

        // XXX If we have multiple packets with the same timestamp tr_key
        // may not return the packet we want. It might be possible to fudge
        // unique keys using nextafter().
        if (event && tracer_->graph() && tracer_->position->axisRect()->rect().contains(event->pos())) {
            packet_seg = time_stamp_map_.value(tr_key, NULL);
        }

        if (!packet_seg) {
            tracer_->setVisible(false);
            hint += "Hover over the graph for details. </i></small>";
            ui->hintLabel->setText(hint);
            ui->rlcPlot->replot(QCustomPlot::rpQueued);
            return;
        }

        tracer_->setVisible(true);
        packet_num_ = packet_seg->num;
        hint += tr("%1 %2 (%3s seq %4 len %5)")
                .arg(cap_file_.capFile() ? tr("Click to select packet") : tr("Packet"))
                .arg(packet_num_)
                .arg(QString::number(packet_seg->rel_secs + packet_seg->rel_usecs / 1000000.0, 'g', 4))
                .arg(packet_seg->SN)
                .arg(packet_seg->pduLength);
        tracer_->setGraphKey(ui->rlcPlot->xAxis->pixelToCoord(event->pos().x()));
        // Redrawing the whole graph is making the update *very* slow!
        // TODO: Is there a way just to draw the parts that may have changed?
        // In the GTK version, we displayed the stored pixbuf and draw temporary items on top...
        rp->replot(QCustomPlot::rpQueued);

    } else {
        if (event && rubber_band_ && rubber_band_->isVisible()) {
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

    hint.append("</i></small>");
    ui->hintLabel->setText(hint);
}