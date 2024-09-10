void
WIN_CheckClipboardUpdate(struct SDL_VideoData * data)
{
    const DWORD count = GetClipboardSequenceNumber();
    if (count != data->clipboard_count) {
        if (data->clipboard_count) {
            SDL_SendClipboardUpdate();
        }
        data->clipboard_count = count;
    }
}