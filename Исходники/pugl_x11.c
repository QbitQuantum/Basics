void
puglDestroy(PuglView* view)
{
	if (!view) {
		return;
	}

	x_fib_close(view->impl->display);

	destroyContext(view);
	XDestroyWindow(view->impl->display, view->impl->win);
	XCloseDisplay(view->impl->display);
	free(view->impl);
	free(view);
}