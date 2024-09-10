bool TextSubtitleParser::LoadSubtitles(const QString &fileName,
                                       TextSubtitles &target)
{
    demux_sputext_t sub_data;
    RemoteFile rfile(fileName, false, false, 0);

    LOG(VB_VBI, LOG_INFO,
        QString("Preparing to load subtitle file (%1)").arg(fileName));
    if (!rfile.Open())
    {
        LOG(VB_VBI, LOG_INFO,
            QString("Failed to load subtitle file (%1)").arg(fileName));
        return false;
    }
    target.SetHasSubtitles(true);
    target.SetFilename(fileName);

    // Only reload if rfile.GetRealFileSize() has changed.
    off_t new_len = rfile.GetFileSize();
    if (target.GetByteCount() == new_len)
    {
        LOG(VB_VBI, LOG_INFO,
            QString("Filesize unchanged (%1), not reloading subs (%2)")
            .arg(new_len).arg(fileName));
        target.SetLastLoaded();
        return new_len;
    }
    LOG(VB_VBI, LOG_INFO,
        QString("Preparing to read %1 subtitle bytes from %2")
        .arg(new_len).arg(fileName));
    target.SetByteCount(new_len);
    sub_data.rbuffer_len = new_len;
    sub_data.rbuffer_text = new char[sub_data.rbuffer_len + 1];
    sub_data.rbuffer_cur = 0;
    sub_data.errs = 0;
    int numread = rfile.Read(sub_data.rbuffer_text, sub_data.rbuffer_len);
    LOG(VB_VBI, LOG_INFO,
        QString("Finished reading %1 subtitle bytes (requested %2)")
        .arg(numread).arg(new_len));
    subtitle_t *loaded_subs = sub_read_file(&sub_data);
    if (!loaded_subs)
    {
        delete sub_data.rbuffer_text;
        return false;
    }

    target.SetFrameBasedTiming(!sub_data.uses_time);
    target.Clear();

    QTextCodec *textCodec = NULL;
    QString codec = gCoreContext->GetSetting("SubtitleCodec", "");
    if (!codec.isEmpty())
        textCodec = QTextCodec::codecForName(codec.toLatin1());
    if (!textCodec)
        textCodec = QTextCodec::codecForName("utf-8");
    if (!textCodec)
    {
        delete sub_data.rbuffer_text;
        return false;
    }

    QTextDecoder *dec = textCodec->makeDecoder();

    // convert the subtitles to our own format and free the original structures
    for (int sub_i = 0; sub_i < sub_data.num; ++sub_i)
    {
        const subtitle_t *sub = &loaded_subs[sub_i];
        text_subtitle_t newsub(sub->start, sub->end);

        if (!target.IsFrameBasedTiming())
        {
            newsub.start *= 10; // convert from csec to msec
            newsub.end *= 10;
        }

        for (int line = 0; line < sub->lines; ++line)
        {
            const char *subLine = sub->text[line];
            QString str = dec->toUnicode(subLine, strlen(subLine));
            newsub.textLines.push_back(str);

            free(sub->text[line]);
        }
        target.AddSubtitle(newsub);
    }

    delete dec;
    // textCodec object is managed by Qt, do not delete...

    free(loaded_subs);
    delete sub_data.rbuffer_text;

    target.SetLastLoaded();

    return true;
}