int numBytesForPacketHeaderGivenPacketType(PacketType type) {
    return (int) ceilf((float)type / 255)
    + numHashBytesInPacketHeaderGivenPacketType(type)
    + NUM_STATIC_HEADER_BYTES;
}