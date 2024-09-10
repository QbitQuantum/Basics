void GStopWatch::stopTimer( ) {
    QueryPerformanceCounter(&timer.stop);
}