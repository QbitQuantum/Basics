static bool
TryConnect(Port &port, char *user_data, size_t max_user_data,
           OperationEnvironment &env)
{
    port.Write('\x02');         // send IO Mode command

    unsigned user_size = 0;
    bool started = false;

    PeriodClock clock;
    clock.Update();

    int i;
    while ((i = port.GetChar()) != EOF && !clock.Check(8000) &&
            !env.IsCancelled()) {
        char ch = (char)i;

        if (!started && ch == '-')
            started = true;

        if (started) {
            if (ch == 0x13) {
                port.Write('\x16');
                user_data[user_size] = 0;
                // found end of file
                return true;
            } else {
                if (user_size < max_user_data - 1) {
                    user_data[user_size] = ch;
                    user_size++;
                }
            }
        }
    }

    return false;
}