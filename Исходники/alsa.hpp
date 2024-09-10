Alsa::~Alsa()
{
    // Close a connection if it exists.
    closePort();

    // Cleanup.
    if ( _apiData->vport >= 0 ) snd_seq_delete_port( _apiData->seq, _apiData->vport );
    if ( _apiData->coder ) snd_midi_event_free( _apiData->coder );
    if ( _apiData->buffer ) free( _apiData->buffer );
    snd_seq_close( _apiData->seq );
    delete _apiData;
}