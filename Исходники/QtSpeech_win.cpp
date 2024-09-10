// implementation
QtSpeech::QtSpeech(QObject * parent)
    :QObject(parent), d(new Private)
{
    CoInitialize(NULL);
    SysCall( d->voice.CoCreateInstance( CLSID_SpVoice ), InitError);

    VoiceName n;
    WCHAR * w_id = 0L;
    WCHAR * w_name = 0L;
    CComPtr<ISpObjectToken> voice;
    SysCall( d->voice->GetVoice(&voice), InitError);
    SysCall( SpGetDescription(voice, &w_name), InitError);
    SysCall( voice->GetId(&w_id), InitError);
    n.name = QString::fromWCharArray(w_name);
    n.id = QString::fromWCharArray(w_id);
    voice.Release();

    if (n.id.isEmpty())
        throw InitError(Where+"No default voice in system");

    d->name = n;
    d->ptrs << this;
}