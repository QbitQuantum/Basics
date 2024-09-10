QVariant QWindowsIntegration::styleHint(QPlatformIntegration::StyleHint hint) const
{
    switch (hint) {
    case QPlatformIntegration::CursorFlashTime:
        if (const unsigned timeMS = GetCaretBlinkTime())
            return QVariant(int(timeMS) * 2);
        break;
#ifdef SPI_GETKEYBOARDSPEED
    case KeyboardAutoRepeatRate:
        return QVariant(keyBoardAutoRepeatRateMS());
#endif
    case QPlatformIntegration::StartDragTime:
    case QPlatformIntegration::StartDragDistance:
    case QPlatformIntegration::KeyboardInputInterval:
    case QPlatformIntegration::ShowIsFullScreen:
    case QPlatformIntegration::PasswordMaskDelay:
    case QPlatformIntegration::StartDragVelocity:
        break; // Not implemented
    case QPlatformIntegration::FontSmoothingGamma:
        return QVariant(QWindowsFontDatabase::fontSmoothingGamma());
    case QPlatformIntegration::MouseDoubleClickInterval:
        if (const int ms = GetDoubleClickTime())
            return QVariant(ms);
        break;
    case QPlatformIntegration::UseRtlExtensions:
        return QVariant(d->m_context.useRTLExtensions());
    case QPlatformIntegration::SynthesizeMouseFromTouchEvents:
#ifdef Q_OS_WINCE
        // We do not want Qt to synthesize mouse events as Windows also does that.
       return false;
#else // Q_OS_WINCE
       return QVariant(bool(d->m_options & DontPassOsMouseEventsSynthesizedFromTouch));
#endif // !Q_OS_WINCE
    default:
        break;
    }
    return QPlatformIntegration::styleHint(hint);
}