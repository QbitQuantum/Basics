/**
 * @see pomp_timer_destroy.
 */
static int pomp_timer_win32_destroy(struct pomp_timer *timer)
{
	struct pomp_fd *pfd = NULL;
	POMP_RETURN_ERR_IF_FAILED(timer != NULL, -EINVAL);

	/* Free resources */
	if (timer->htimer != NULL) {
		/* Wait for cancellation */
		DeleteTimerQueueTimer(NULL, timer->htimer,
				INVALID_HANDLE_VALUE);
	}
	if (timer->hevt != NULL) {
		pfd = pomp_loop_win32_find_pfd_by_hevt(
				timer->loop, timer->hevt);
		if (pfd == NULL) {
			POMP_LOGW("hevt %p not found in loop %p",
					timer->hevt, timer->loop);
		} else {
			pomp_loop_remove_pfd(timer->loop, pfd);
			free(pfd);
		}
		CloseHandle(timer->hevt);
	}
	free(timer);
	return 0;
}