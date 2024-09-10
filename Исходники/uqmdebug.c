// Show the contexts on the screen.
// Must be called from the main thread.
void
debugContexts (void)
{
	static volatile bool inDebugContexts = false;
			// Prevent this function from being called from within itself.
	
	CONTEXT orgContext;
	CONTEXT debugDrawContext;
			// We're going to use this context to draw in.
	FRAME debugDrawFrame;
	double hueIncrement;
	size_t visibleContextI;
	CONTEXT context;
	size_t contextCount;
	FRAME savedScreen;

	// Prevent this function from being called from within itself.
	if (inDebugContexts)
		return;
	inDebugContexts = true;

	contextCount = countVisibleContexts ();
	if (contextCount == 0)
	{
		goto out;
	}
	
	savedScreen = getScreen ();
	FlushGraphics ();
			// Make sure that the screen has actually been captured,
			// before we use the frame.

	// Create a new frame to draw on.
	debugDrawContext = CreateContext ("debugDrawContext");
	// New work frame is a copy of the original.
	debugDrawFrame = CaptureDrawable (CloneFrame (savedScreen));
	orgContext = SetContext (debugDrawContext);
	SetContextFGFrame (debugDrawFrame);

	hueIncrement = 360.0 / contextCount;

	visibleContextI = 0;
	for (context = GetFirstContext (); context != NULL;
			context = GetNextContext (context))
	{
		if (context == debugDrawContext) {
			// Skip our own context.
			continue;
		}
	
		if (isContextVisible (context))
		{
			// Only draw the visible contexts.
			drawContext (context, visibleContextI * hueIncrement);
			visibleContextI++;
		}

		describeContext (stderr, context);
	}

	// Blit the final debugging frame to the screen.
	putScreen (debugDrawFrame);

	// Wait for a key:
	{
		WAIT_STATE state;
		state.InputFunc = waitForKey;
		DoInput(&state, TRUE);
	}

	SetContext (orgContext);

	// Destroy the debugging frame and context.
	DestroyContext (debugDrawContext);
			// This does nothing with the drawable set with
			// SetContextFGFrame().
	DestroyDrawable (ReleaseDrawable (debugDrawFrame));
	
	putScreen (savedScreen);

	DestroyDrawable (ReleaseDrawable (savedScreen));

out:
	inDebugContexts = false;
}