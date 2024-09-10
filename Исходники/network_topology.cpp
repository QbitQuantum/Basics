void NetworkTopology::advance_time(Clock::duration t)
{
    const Clock::duration max_step = std::chrono::milliseconds(500);
    do {
        const auto step = std::min(t, max_step);
        now += step;
        t -= step;
        // update timestamp for every router
        for (auto& host : hosts) {
            Runtime& runtime = host.second->runtime;
            runtime.trigger(now);
            Router& router = host.second->router;
            LongPositionVector lpv = router.get_local_position_vector();
            lpv.timestamp = now;
            router.update(lpv);
        }
        dispatch();
    } while (t.count() > 0);
}