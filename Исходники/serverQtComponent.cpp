void serverQtComponent::EventWriteQSlot(int newValue)
{
    mtsInt payload;
    payload.Data = newValue;
    EventWrite(payload);
}