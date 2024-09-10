void
FreeKernel (void)
{
	UninitKernel (TRUE);
	UninitContexts ();

	UninitResourceSystem ();

	UninitPlayerInput ();

	DestroyDrawable (ReleaseDrawable (Screen));
	DestroyContext (ScreenContext);

	UninitVideoPlayer ();
	UninitSound ();
	UninitGraphics ();
}