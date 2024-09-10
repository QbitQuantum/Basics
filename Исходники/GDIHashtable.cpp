void GDIHashtable::BatchDestructionManager::update() {

    if (get_free_system_resources != NULL) {

        CriticalSection::Lock l(m_managerLock);

        if (m_nCounter < 0) {
            UINT nFreeResources = (*get_free_system_resources)(GFSR_GDIRESOURCES);
            /*
             * If m_bBatchingEnabled is FALSE there is no need
             * to flush since we have been destroying all
             * GDI resources as soon as they were released.
             */
            if (m_bBatchingEnabled) {
                if (nFreeResources < m_nFirstThreshold) {
                    flushAll();
                    nFreeResources = (*get_free_system_resources)(GFSR_GDIRESOURCES);
                }
            }
            if (nFreeResources < m_nSecondThreshold) {
                m_bBatchingEnabled = FALSE;
                m_nCounter = m_nDestroyPeriod;
            } else {
                m_bBatchingEnabled = TRUE;
                /*
                 * The frequency of checks must depend on the currect amount
                 * of free space in GDI heaps. Otherwise we can run into the
                 * Resource Meter warning dialog when GDI resources are low.
                 * This is a heuristic rule that provides this dependency.
                 * These numbers have been chosen because:
                 * Resource Meter posts a warning dialog when less than 10%
                 * of GDI resources are free.
                 * 5 pens/brushes take 1%. So 3 is the upper bound.
                 * When changing this rule you should check that performance
                 * isn't affected (with Caffeine Mark and JMark).
                 */
                m_nCounter = (nFreeResources - 10) * 3;
            }
        }
    }
}