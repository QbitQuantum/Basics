void FollowStreamDialog::addText(QString text, gboolean is_from_server, guint32 packet_num)
{
    if (save_as_ == true)
    {
        size_t nwritten;
        int FileDescriptor = file_.handle();
        int fd_new = ws_dup(FileDescriptor);
        if (fd_new == -1)
            return;
        FILE* fh = ws_fdopen(fd_new, "wb");
        if (show_type_ == SHOW_RAW) {
            QByteArray binstream = QByteArray::fromHex(text.toUtf8());
            nwritten = fwrite(binstream.constData(), binstream.length(), 1, fh);
        } else {
            nwritten = fwrite(text.toUtf8().constData(), text.length(), 1, fh);
        }
        fclose(fh);
        if ((int)nwritten != text.length()) {
#if 0
            report_an_error_maybe();
#endif
        }
        return;
    }

    if (truncated_) {
        return;
    }

    int char_count = ui->teStreamContent->document()->characterCount();
    if (char_count + text.length() > max_document_length_) {
        text.truncate(max_document_length_ - char_count);
        truncated_ = true;
    }

    setUpdatesEnabled(false);
    int cur_pos = ui->teStreamContent->verticalScrollBar()->value();
    ui->teStreamContent->moveCursor(QTextCursor::End);
    QTextCharFormat tcf = ui->teStreamContent->currentCharFormat();
    if (is_from_server) {
        tcf.setForeground(ColorUtils::fromColorT(prefs.st_server_fg));
        tcf.setBackground(ColorUtils::fromColorT(prefs.st_server_bg));
    } else {
        tcf.setForeground(ColorUtils::fromColorT(prefs.st_client_fg));
        tcf.setBackground(ColorUtils::fromColorT(prefs.st_client_bg));
    }
    ui->teStreamContent->setCurrentCharFormat(tcf);

    ui->teStreamContent->insertPlainText(text);
    text_pos_to_packet_[ui->teStreamContent->textCursor().anchor()] = packet_num;

    if (truncated_) {
        tcf = ui->teStreamContent->currentCharFormat();
        tcf.setBackground(palette().window().color());
        tcf.setForeground(palette().windowText().color());
        ui->teStreamContent->insertPlainText("\n" + tr("[Stream output truncated]"));
        ui->teStreamContent->moveCursor(QTextCursor::End);
    } else {
        ui->teStreamContent->verticalScrollBar()->setValue(cur_pos);
    }
    setUpdatesEnabled(true);
}