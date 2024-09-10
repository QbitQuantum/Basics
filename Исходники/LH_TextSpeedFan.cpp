int LH_TextSpeedFan::notify(int n,void* p)
{
    if( !n || n&LH_NOTE_SECOND )
    {
        HANDLE filemap = OpenFileMappingA(FILE_MAP_READ, FALSE, "SFSharedMemory_ALM");
        if( filemap != NULL )
        {
            SFMemory* sfmemory = (SFMemory*)MapViewOfFile(filemap, FILE_MAP_READ, 0, 0, sizeof(SFMemory));
            if( sfmemory )
            {
                QString outText = setup_template_->value();
                QRegExp rx("%(t|f|v)(n|[0-9]+)");
                int pos = 0;
                while ((pos = rx.indexIn(outText, pos)) != -1) {
                    QString repVal;
                    if(rx.cap(1) == "t") {
                        if (rx.cap(2) == "n")
                            repVal = QString("%1").arg(sfmemory->NumTemps);
                        else
                            repVal = QString("%1\260C").arg(sfmemory->temps[rx.cap(2).toInt()]/100);
                    }
                    if(rx.cap(1) == "f") {
                        if (rx.cap(2) == "n")
                            repVal = QString("%1").arg(sfmemory->NumFans);
                        else
                            repVal = QString("%1").arg(sfmemory->fans[rx.cap(2).toInt()]);
                    }
                    if(rx.cap(1) == "v") {
                        if (rx.cap(2) == "n")
                            repVal = QString("%1").arg(sfmemory->NumVolts);
                        else
                            repVal = QString("%1V").arg(float(sfmemory->volts[rx.cap(2).toInt()])/100);
                    }
                    outText.replace(rx.cap(0),repVal);
                    pos += rx.matchedLength();
                }
                if( setText( outText ) )
                    callback(lh_cb_render,NULL); // only render if the text changed
            }
            else
            {
                if( setText( "Failed to open shared memory." ) )
                    callback(lh_cb_render,NULL); // only render if the text changed
            }
            // Close the handles we opened.
            CloseHandle(filemap);
        }
        else
            if( setText( "N/A" ) ) callback(lh_cb_render,NULL);
    }
    return LH_Text::notify(n,p) | LH_NOTE_SECOND;
};