unsigned __stdcall ray_render_thread(void *arg)
{
	int							slice_idx;
	ray_scene_thread_type		*thread;
	ray_scene_type				*scene;

		// get the thread and scene

	thread=(ray_scene_thread_type*)arg;
	scene=thread->parent_scene;

		// set some flags

	thread->shutdown_done=FALSE;

		// these are worker threads so
		// they suspend until needed

	while (TRUE) {

		SuspendThread(thread->thread);

			// in case spurious wake-up

		if (scene->thread_mode==ray_thread_mode_suspend) continue;

			// in shutdown?

		if (scene->thread_mode==ray_thread_mode_shutdown) {
			thread->shutdown_done=TRUE;
			_endthreadex(0);
			return(0);
		}

			// render the next slice

		while (TRUE) {
			slice_idx=-1;

			EnterCriticalSection(&scene->render.scene_lock);
			if (scene->render.next_slice_idx<ray_global.settings.slice_count) {
				slice_idx=scene->render.next_slice_idx;
				scene->render.next_slice_idx++;
			}
			LeaveCriticalSection(&scene->render.scene_lock);

			if (slice_idx==-1) break;

			ray_render_slice_run(scene,&scene->render.slices[slice_idx]);
		}

			// add up thread done count
			
		EnterCriticalSection(&scene->render.scene_lock);
		scene->render.thread_done_count++;
		LeaveCriticalSection(&scene->render.scene_lock);
	}
}