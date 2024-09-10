/* _al_win_thread_exit:
 *  Shuts down COM interface for the calling thread.
 */
void _al_win_thread_exit(void)
{
   CoUninitialize();
}