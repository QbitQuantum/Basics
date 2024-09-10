void cond_variable_wait(cond_variable * c, mutex * m)
{
	/* add thread to cond_variable queue */
	enque(c->q, getPid());
	/* sleep thread and release lock atomically */

	release_lock_and_sleep(m);
	/* re-aquire lock */
	mutex_lock(m);
}