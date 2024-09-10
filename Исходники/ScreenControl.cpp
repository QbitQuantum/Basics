/*
 * デフォルトカラー設定メソッド。
 * @return なし
 */
void ScreenControl::setDefaultColor(void)
{
    SetConsoleTextAttribute(mHandle, mInitColor);
    return;
}