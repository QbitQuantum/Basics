//
/// Sends the MCI command to the device if it's not busy.
//
uint32
TMci::SendCommand(uint msg, uint32 command, uint32 param)
{
  if (IsBusy())
    return MCI_NOTIFY_ABORTED;

  return SendCommand(GetDeviceId(), msg, command, param);
}