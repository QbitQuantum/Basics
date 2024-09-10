void WorldSession::SendSetTimeZoneInformation()
{
    /// @todo: replace dummy values
    WorldPackets::System::SetTimeZoneInformation packet;
    packet.ServerTimeTZ = "Europe/Paris";
    packet.GameTimeTZ = "Europe/Paris";

    SendPacket(packet.Write());
}