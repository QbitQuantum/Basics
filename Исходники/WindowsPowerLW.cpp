////////////////////////////////////////////////////////////
///
/// @brief 获取当前Windows是否有修改电源使用方案的权限
///
/// @param __out bool* cuwpsFlag           - 权限标志
///
/// @return HRESULT
///
/// @retval S_OK 正常返回
/// @retval 通过GetLastError()返回
///
////////////////////////////////////////////////////////////
HRESULT WindowsPowerLW::CanUserWritePowerScheme(
    __out bool* cuwpsFlag
    )
{
    DEBUG_XCOVER_MARK_LINE;
    *cuwpsFlag = true;
    if (!CanUserWritePwrScheme())
    {
        *cuwpsFlag = false;
    }
    DEBUG_XCOVER_MARK_LINE;
    return S_OK;
}