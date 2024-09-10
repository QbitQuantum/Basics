void QueryServer::runQuery(const string &s, const TcpConnectionPtr &conn)
{
    string word = s;
    if(word.substr(word.size()-2, 2) == "\r\n")
    {
        word.erase(word.size()-1);
        word.erase(word.size()-1);
    }
    string res = final_.runLCS(word);
    conn->send(res + "\r\n");
}