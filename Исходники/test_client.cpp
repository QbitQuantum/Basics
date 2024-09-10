void ExecCmd(ClientConn *client_conn) {
    g_cmd_lock.Lock();
    if (g_cmd_string_vec.empty()) {
        g_cmd_lock.Unlock();
        return;
    }

    if (g_cmd_string_vec[0] == "login") {
        if (g_cmd_string_vec.size() == 3) {
            SendLoginRequest(client_conn, g_cmd_string_vec[1], g_cmd_string_vec[2]);
        } else {
            PrintHelp();
        }
    } else if (g_cmd_string_vec[0] == "logout") {
        SendLogoutRequest(client_conn);
    } else if (g_cmd_string_vec[0] == "send") {
        if (g_cmd_string_vec.size() == 3) {
            SendMessageRequest(client_conn, g_cmd_string_vec[1], g_cmd_string_vec[2]);
        } else {
            PrintHelp();
        }
    } else {
        PrintHelp();
    }
    g_cmd_string_vec.clear();
    g_cmd_lock.Unlock();
}