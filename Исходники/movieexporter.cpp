/** Runs the specified command (should be ffmpeg), and lets
 *  writeFrame pipe data into it 1 frame at a time.
 *
 *  @param[in]  strCmd A string containing the command to execute and
 *              all of its arguments
 *  @param[out] progress A function that takes one float argument
 *              (the percentage of the ffmpeg operation complete) and
 *              may display the output to the user in any way it
 *              sees fit.
 *  @param[in]  writeFrame A function that takes two arguments, a
 *              process (the ffmpeg process) and an integer
 *              (frames processed or -1, see full description).
 *              This function should write a single frame to the
 *              process. The function returns true value if it
 *              actually wrote a frame.
 *
 *  This function operates generally as follows:
 *  1. Spawn process with the command from strCmd
 *  2. Check ffmpeg's output for a progress update.
 *  3. Add frames with writeFrame until it returns false.
 *  4. Repeat from step 2 until all frames have been written.
 *
 *  The idea is that there are two forms of processing occuring
 *  simultaneously, generating frames to send to ffmpeg, and ffmpeg
 *  encoding those frames. Whether these this actually occur
 *  concurrently or one after another appears to depend on the environment.
 *
 *  The writeFrame function deserves a bit of extra details. It does
 *  not only return false when there is an error in generating or
 *  writing a frame, it also does it when it wants to "return control"
 *  to the rest of the executeFFMpegPipe function for the purposes of
 *  reading updates from ffmpeg's output. This should be done every
 *  once in a while if possible, but with some formats (specifically gif),
 *  all frames must be loaded before any processing can continue, so
 *  there is no point returning false for it until all frames have
 *  been written. writeFrame is also responsible for closing the writeChannel
 *  of the process when it has finished writing all frames. This indicates
 *  to executeFFMpegPipe that it no longer needs to call writeFrame.
 *
 *  @return Returns Status::OK if everything went well, and Status::FAIL
 *  and error is detected (usually a non-zero exit code for ffmpeg).
 */
Status MovieExporter::executeFFMpegPipe(QString strCmd, std::function<void(float)> progress, std::function<bool(QProcess&, int)> writeFrame)
{
    qDebug() << strCmd;

    QProcess ffmpeg;
    ffmpeg.setReadChannel(QProcess::StandardOutput);
    // FFmpeg writes to stderr only for some reason, so we just read both channels together
    ffmpeg.setProcessChannelMode(QProcess::MergedChannels);
    ffmpeg.start(strCmd);
    if (ffmpeg.waitForStarted())
    {
        int framesGenerated = 0;
        int lastFrameProcessed = 0;
        const int frameStart = mDesc.startFrame;
        const int frameEnd = mDesc.endFrame;
        while(ffmpeg.state() == QProcess::Running)
        {
            if (mCanceled)
            {
                ffmpeg.terminate();
                return Status::CANCELED;
            }

            // Check FFmpeg progress

            int framesProcessed = -1;
            if(ffmpeg.waitForReadyRead(10))
            {
                QString output(ffmpeg.readAll());
                QStringList sList = output.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
                for (const QString& s : sList)
                {
                    qDebug() << "[ffmpeg]" << s;
                }
                if(output.startsWith("frame="))
                {
                    lastFrameProcessed = framesProcessed = output.mid(6, output.indexOf(' ')).toInt();
                }
            }

            if(!ffmpeg.isWritable())
            {
                continue;
            }

            while(writeFrame(ffmpeg, framesProcessed))
            {
                framesGenerated++;

                const float percentGenerated = framesGenerated / static_cast<float>(frameEnd - frameStart);
                const float percentConverted = lastFrameProcessed / static_cast<float>(frameEnd - frameStart);
                progress((percentGenerated + percentConverted) / 2);
            }
            const float percentGenerated = framesGenerated / static_cast<float>(frameEnd - frameStart);
            const float percentConverted = lastFrameProcessed / static_cast<float>(frameEnd - frameStart);
            progress((percentGenerated + percentConverted) / 2);
        }

        QString output(ffmpeg.readAll());
        QStringList sList = output.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
        for (const QString& s : sList)
        {
            qDebug() << "[ffmpeg]" << s;
        }

        if(ffmpeg.exitStatus() != QProcess::NormalExit)
        {
            qDebug() << "ERROR: FFmpeg crashed";
            return Status::FAIL;
        }
    }
    else
    {
        qDebug() << "ERROR: Could not start FFmpeg.";
        return Status::FAIL;
    }

    return Status::OK;
}