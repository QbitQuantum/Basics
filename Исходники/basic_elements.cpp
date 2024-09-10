Time64 convert_time64(const Clock::time_point& tp)
{
    using namespace std::chrono;
    return duration_cast<microseconds>(tp.time_since_epoch()).count();
}