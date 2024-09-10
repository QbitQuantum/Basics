int BlsChildChannel::clean()
{
    log_error("process will exit, may be master process is freezed.");
    _exit(0);
}