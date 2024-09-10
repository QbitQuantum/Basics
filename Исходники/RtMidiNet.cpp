RtMidiOutNet :: ~RtMidiOutNet()
{
    // Close a connection if it exists.
    closePort();
    // Cleanup.
    NetworkMidiData *data = (NetworkMidiData *) apiData_;
    delete data;
}