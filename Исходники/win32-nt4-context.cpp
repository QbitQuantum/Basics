/*
 * implementation for context_init
 */
void context_init() {
  PVOID pTopFiber = (top_context == NULL || top_context != current_context)? NULL: top_context->pFiber;
  context_deinit();

  /*
   * there is strange but fibers always exist
   * PVOID pCurrentFiber = GetCurrentFiber();
   * if (pCurrentFiber != NULL) DeleteFiber(pCurrentFiber);
   */

  current_context = top_context = context_alloc();
  if (top_context != NULL) top_context->pFiber = (pTopFiber == NULL)? ConvertThreadToFiber(NULL): pTopFiber;
  return;
}