void
SystemTaskWrapper::Process(
    void
    )
{
    // Call the function, and figure out how long it took.
	i64 counter = __rdtsc();
    pSystemTask->Update( deltaTime );
	counter = __rdtsc() - counter;

	// Log this job's time in instrumentation.
	Singletons::Instrumentation.CaptureJobCounterTicks( pSystemTask->GetSystemType(), counter );
}