int main(void)
{
    int nThreads = 10;
    std::vector<std::thread> threads;
    for (int i = 1; i <= nThreads; i++) {
        threads.push_back(std::thread([=]() {
            printf("Thread th%02d: ThreadID=%ld\n", i, getCurrentThreadID());
            printf("Thread th%02d: ThreadID=%ld\n", i, getCurrentThreadID());
        }));
    }
    for (std::thread& th : threads) {
        th.join();
    }

    printf("Thread main: ThreadID=%ld\n", getCurrentThreadID());
    printf("Thread main: ThreadID=%ld\n", getCurrentThreadID());
    return 0;
}