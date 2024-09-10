RCX_Result RCX_Link::Download(const UByte *data, int length, int chunk)
{
    PDEBUGVAR("RCX_Link::Download chunk", chunk);
    RCX_Cmd cmd;
    RCX_Result result;
    UShort seq;
    int remain = length;
    int n;

    seq = 1;
    while (remain > 0) {
        // Transfer the remaining bytes if what is left to send
        // is less than the current chunk size.
        if (remain <= chunk) {
            // TODO: I have no clear idea what gProgramMode is for, but
            // it is almost always true.
            if (!gQuiet || gProgramMode) {
                seq = 0;
            }
            n = remain;
        }
        else {
            n = chunk;
        }

        n = AdjustChunkSize(n, data, fTransport->GetComplementData());
        PDEBUGVAR("sending bytes", n);
        if (fVerbose) {
            printf("sending %d bytes\n", n);
        }

        result = Send(cmd.MakeDownload(seq++, data, (UShort)n),
            true, fDownloadWaitTime);
        if (RCX_ERROR(result))
            return result;

        remain -= n;
        data += n;
        if (!IncrementProgress(n)) {
            return kRCX_AbortError;
        }
    }

    return kRCX_OK;
}