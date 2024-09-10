 void ReplicationCoordinatorExternalStateImpl::shutdown() {
     _syncSourceFeedback.shutdown();
     BackgroundSync* bgsync = BackgroundSync::get();
     bgsync->shutdown();
     _syncSourceFeedbackThread->join();
     _backgroundSyncThread->join();
     _producerThread->join();
 }