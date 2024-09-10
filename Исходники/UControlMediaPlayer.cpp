/// PRIVATE SLOTS
void UControlMediaPlayer::emitClickedKey(int key)
{
    // Моделируем нажатие клавиши
    keybd_event(key, 0, 0, 0);

    // Моделируем возврат клавиши в не нажатое состояние
    keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
}