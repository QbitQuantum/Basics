int WinPlatform::keyCode(const QKeyEvent &event)
{
    const int key = event.key();

    // Some keys shouldn't be translated.
    if ( key == Qt::Key_Return
      || key == Qt::Key_Enter
      || key == Qt::Key_Escape
      || key == Qt::Key_Tab
      || key == Qt::Key_Backtab
      || key == Qt::Key_Backspace
         )
    {
        return key;
    }

    const quint32 vk = event.nativeVirtualKey();
    const UINT result = MapVirtualKeyW(vk, MAPVK_VK_TO_CHAR);
    if (result != 0)
        return result;

    return key;
}