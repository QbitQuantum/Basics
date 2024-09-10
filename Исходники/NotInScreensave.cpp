void SimulateKeyboard()
{
    INPUT inputKeyboard = {0};
    inputKeyboard.type = INPUT_KEYBOARD;
    inputKeyboard.ki.wVk = VK_F24;//键盘上没有的按键
    SendInput(1, &inputKeyboard, sizeof(inputKeyboard));
}