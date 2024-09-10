AntennaId User::get_smoothed_antenna(time_duration time)
{
    unsigned next_event_minute = to_minutes(time);

    float smoothed_lat = 0;
    float smoothed_lon = 0;
    float weight_sum = 0;
    for(unsigned i = 0; i < events.size(); i++) {
        Event* event = events.at(i);
        unsigned event_minute = to_minutes(event->time.time_of_day());
        Antenna* antenna = AntennaModel::find_antenna_by_id(event->antenna_id);

        int diff = abs(event_minute - next_event_minute);
        if (diff > 12 * 60) {
            diff = 24 * 60 - diff;
        }
        float weight = pdf(normal(0, AntennaModel::timestep), diff);
        weight_sum += weight;
        smoothed_lat += weight * antenna->get_latitude();
        smoothed_lon += weight * antenna->get_longitude();
    }
    smoothed_lat /= weight_sum;
    smoothed_lon /= weight_sum;

    return AntennaModel::find_nearest_antenna(smoothed_lat,
        smoothed_lon)->get_id();
}