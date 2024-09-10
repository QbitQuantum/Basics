void DeInitContinuations()
{
    LwipUpTimeCompletion.Abort();
    InterruptTaskContinuation.Abort();
}