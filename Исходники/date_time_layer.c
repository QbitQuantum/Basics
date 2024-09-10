void date_time_layer_format_time(
    char* buffer, size_t buffer_length, struct tm* now, bool is_24h
) {
    strftime(buffer, buffer_length, is_24h ? "%H:%M" : "%I:%M", now);
}