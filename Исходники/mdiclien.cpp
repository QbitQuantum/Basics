//
/// Preprocess messages in order to translate MDI accelerator keys
///
/// If the specified msg is one of WM_KEYDOWN or WM_SYSKEYDOWN, then the keyboard
/// accelerators are translated for the MDI client.
//
bool
TMDIClient::PreProcessMsg(MSG& msg)
{
  if (msg.message == WM_KEYDOWN || msg.message == WM_SYSKEYDOWN)
    return TranslateMDISysAccel(GetHandle(), &msg);

  else
    return false;
}