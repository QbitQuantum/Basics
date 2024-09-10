/**
 * Unregister all sessions launched from the given connection
 */
void DaemonCore::releaseConnectionSessions( DaemonConnection& connection ) {
    CRASH_REPORT_BEGIN;
    CVMWA_LOG("Debug", "Releasing connection sessions");
    std::map<int, CVMWebAPISession* >::iterator it = sessions.begin();
    for (; it != sessions.end(); ++it) {
        CVMWebAPISession* sess = (*it).second;
        if (&sess->connection == &connection) {

            // Dispose
            sess->abort();
            delete sess;
            
            // Remove from list
            sessions.erase( it );

            // And break if we are done
            if (sessions.empty()) break;
            
            // Rewind iterator
            it = sessions.begin();

        }
    }

    CRASH_REPORT_END;
}