bool Sentinel::discover_master(pair<string, int>& addr, string& url)
{
    bool succ = false;
    for (vector<string>::iterator it = urls_.begin(); it != urls_.end(); ++it)
    {
        url = *it;
        Connection conn;
        if (conn.connect(url))
        {
            if (get_master_address(conn, addr))
            {
                succ = true;
                // give priority to the replying Sentinel
                urls_.erase(it);
                urls_.insert(urls_.begin(), url);
                break;
            }
        }
    }

    return succ;
}