// --------------------- websocket interface -----------------------
void RestServ::websocketSend(mg_connection& nc, WebsocketMessage ws) 
{
    //process here
    std::stringstream sout;
    try{
        ws.data_to_arg();
        tinychain::commands cmd{ws.vargv(), node_};
        Json::Value ret;
        cmd.exec(ret);

        sout<<ret.toStyledString();

    } catch(std::exception& e) {
        sout << e.what();
    }

    websocketSend(&nc, sout.str().c_str(), sout.str().size());
}