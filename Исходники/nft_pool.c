/*------------------------------------------------------------------------------
 * pool_thread_cleanup	- Function for use with pthread_cleanup_push/pop.
 *
 * This cleanup handler is used by pool threads, which cannot be cancelled,
 * but which may call pthread_exit from the work function.
 *------------------------------------------------------------------------------
 */
static void
pool_thread_cleanup(void * arg)
{
    nft_pool * pool = nft_pool_cast(arg); assert(pool);

    int rc = pthread_mutex_lock(&pool->queue.mutex); assert(rc == 0);

    // If the pool is shutting down and we are the last pool thread
    // to finish, signal the thread that is waiting in nft_pool_shutdown.
    if (--pool->num_threads == 0 && SHUTDOWN(pool))
	pthread_cond_signal(&pool->queue.cond);

    rc = pthread_mutex_unlock(&pool->queue.mutex); assert(0 == rc);

    // The nft_pool_thread holds a pool reference, which we must discard.
    nft_pool_discard(pool);
}