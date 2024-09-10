void ScatterCtrl::AddKeyBehavior(bool ctrl, bool alt, bool shift, int key, bool isVirtualKey, ScatterAction action)
{
    if (!isVirtualKey) {
#if defined(PLATFORM_WIN32) || defined (PLATFORM_WIN64)
        HKL hKeyboardLayout = ::GetKeyboardLayout(0);
        key = VkKeyScanExW(key, hKeyboardLayout) + K_DELTA;
    }
#else
        key = key + K_DELTA;//GetKeyCodeX(key);
    }