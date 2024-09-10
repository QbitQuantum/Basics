/**
 * drag and drop whatever is in the cut-copy-paste buffer
 * - create a selection first using:
 *     Fl::copy(const char *stuff, int len, 0)
 */
bool Fl::dnd()
{
    DWORD dropEffect;
    ReleaseCapture();

    FLDataObject *fdo = new FLDataObject;
    fdo->AddRef();
    FLDropSource *fds = new FLDropSource;
    fds->AddRef();

    HRESULT ret = DoDragDrop( fdo, fds, DROPEFFECT_MOVE|DROPEFFECT_LINK|DROPEFFECT_COPY, &dropEffect );

    fdo->Release();
    fds->Release();

    // Windows handled the mouse release, remember that:
    pushed_ = 0;
    e_state &= ~FL_BUTTONS;

    return ret==DRAGDROP_S_DROP; // or DD_S_CANCEL
}