void CCameraEngine::StartDirectViewFinderL(RWsSession& aSession,
                            CWsScreenDevice& aScreenDevice,
                            RWindowBase& aWindow,
                            TRect& aScreenRect,
                            TRect& aClipRect)
{
    if (iEngineState < EEngineIdle)
        User::Leave(KErrNotReady);

    if (0 == (iCameraInfo.iOptionsSupported & TCameraInfo::EViewFinderDirectSupported))
        User::Leave(KErrNotSupported);

    if (!iCamera->ViewFinderActive()) {
        // Viewfinder extent needs to be clipped according to the clip rect.
        // This is because the native camera framework does not support
        // clipping and starting viewfinder with bigger than the display(S60
        // 5.0 and older)/window(Symbian^3 and later) would cause viewfinder
        // starting to fail entirely. This causes shrinking effect in some
        // cases, but is better than not having the viewfinder at all.
        if (aScreenRect.Intersects(aClipRect))
            aScreenRect.Intersection(aClipRect);

        if (iCameraIndex != 0)
            iCamera->SetViewFinderMirrorL(true);
        if (aScreenRect.Width() > 0 && aScreenRect.Height() > 0) {
            iCamera->StartViewFinderDirectL(aSession, aScreenDevice, aWindow, aScreenRect);
        } else {
            if (iObserver)
                iObserver->MceoHandleError(EErrViewFinderReady, KErrArgument);
        }
    }
}