EndpointInfo::EndpointInfo(int32 id)
    : m_id(id), m_icon(NULL)
{
    BMidiRoster* roster = BMidiRoster::MidiRoster();
    if (roster) {
        BMidiEndpoint* endpoint = roster->FindEndpoint(id);
        if (endpoint) {
            printf("endpoint %ld = %p\n", id, endpoint);
            BMessage msg;
            if (endpoint->GetProperties(&msg) == B_OK) {
                m_icon = CreateIcon(&msg, DISPLAY_ICON_SIZE);
            }
            endpoint->Release();
        }
    }
}