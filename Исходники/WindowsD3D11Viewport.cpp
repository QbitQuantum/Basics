void FD3D11Viewport::ConditionalResetSwapChain(bool bIgnoreFocus)
{
	if(!bIsValid)
	{
		// Check if the viewport's window is focused before resetting the swap chain's fullscreen state.
		HWND FocusWindow = ::GetFocus();
		const bool bIsFocused = FocusWindow == WindowHandle;
		const bool bIsIconic = !!::IsIconic( WindowHandle );
		if(bIgnoreFocus || (bIsFocused && !bIsIconic) )
		{
			FlushRenderingCommands();

			// Store the current cursor clip rectangle as it can be lost when fullscreen is reset.
			RECT OriginalCursorRect;
			GetClipCursor(&OriginalCursorRect);

			HRESULT Result = SwapChain->SetFullscreenState(bIsFullscreen,NULL);
			if(SUCCEEDED(Result))
			{
				ClipCursor(&OriginalCursorRect);
				bIsValid = true;
			}
			else
			{
				// Even though the docs say SetFullscreenState always returns S_OK, that doesn't always seem to be the case.
				UE_LOG(LogD3D11RHI, Log, TEXT("IDXGISwapChain::SetFullscreenState returned %08x; waiting for the next frame to try again."),Result);
			}
		}
	}
}