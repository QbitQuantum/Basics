/* exit from url loop */
void url_exit(void)
{
    QEventLoop loop;
    loop.exit();

    foreach (QSocketNotifier *notifier, gReadNotifiers) {
        delete notifier;
    }
    foreach (QSocketNotifier *notifier, gWriteNotifiers) {
        delete notifier;
    }
    QApplication::quit();
}