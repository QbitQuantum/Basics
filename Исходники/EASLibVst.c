/*----------------------------------------------------------------------------
 * HeapCheck()
 *----------------------------------------------------------------------------
 * Check heap status
 *----------------------------------------------------------------------------
*/
void HeapCheck (void)
{
    int heapStatus;

    /* Check heap status */
    heapStatus = _heapchk();
    if ((heapStatus == _HEAPOK) || (heapStatus == _HEAPEMPTY))
        return;

    EAS_ReportX(_EAS_SEVERITY_FATAL, "Heap corrupt\n" );
}