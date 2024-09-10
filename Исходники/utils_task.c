void
grid_task_queue_destroy(struct grid_task_queue_s *gtq)
{
	if (!gtq)
		return;
	if (gtq->tasks) {
		_cleanup(gtq);
		g_array_free(gtq->tasks, TRUE);
		gtq->tasks = NULL;
	}
	if (gtq->name) {
		g_free(gtq->name);
		gtq->name = NULL;
	}
	g_free(gtq);
}