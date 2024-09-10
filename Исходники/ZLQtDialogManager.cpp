void ZLQtDialogManager::wait(const ZLResourceKey &key, ZLRunnable &runnable) const {
    ZLQtWaitMessage waitMessage(waitMessageText(key));
    runnable.run();
}