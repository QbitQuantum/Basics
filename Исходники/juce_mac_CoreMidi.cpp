void MidiOutput::sendMessageNow (const MidiMessage& message)
{
    CoreMidiHelpers::MidiPortAndEndpoint* const mpe = static_cast<CoreMidiHelpers::MidiPortAndEndpoint*> (internal);

    if (message.isSysEx())
    {
        const int maxPacketSize = 256;
        int pos = 0, bytesLeft = message.getRawDataSize();
        const int numPackets = (bytesLeft + maxPacketSize - 1) / maxPacketSize;
        HeapBlock <MIDIPacketList> packets;
        packets.malloc (32 * numPackets + message.getRawDataSize(), 1);
        packets->numPackets = numPackets;

        MIDIPacket* p = packets->packet;

        for (int i = 0; i < numPackets; ++i)
        {
            p->timeStamp = 0;
            p->length = jmin (maxPacketSize, bytesLeft);
            memcpy (p->data, message.getRawData() + pos, p->length);
            pos += p->length;
            bytesLeft -= p->length;
            p = MIDIPacketNext (p);
        }

        mpe->send (packets);
    }
    else
    {
        MIDIPacketList packets;
        packets.numPackets = 1;
        packets.packet[0].timeStamp = 0;
        packets.packet[0].length = message.getRawDataSize();
        *(int*) (packets.packet[0].data) = *(const int*) message.getRawData();

        mpe->send (&packets);
    }
}