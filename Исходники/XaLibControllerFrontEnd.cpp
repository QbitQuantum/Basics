void XaLibControllerFrontEnd::OnStart(const string& ConfFile) {

    try {

        LoadXmlConfFile(ConfFile);
        StartLog();

        LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"########################### STARTING FRONT END ACTION LOG ############################");

        //StartDb();
        StartHttp();

        //GetServerInfo();
        //GetClientInfo();
        SESSION.FrontEndIp=HTTP.GetServerIpAddress();
        SESSION.ClientIp=HTTP.GetClientIpAddress();
        GetLayout();

        LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"IP Address Client-> "+SESSION.ClientIp);
        LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Ip Address Front End Server -> "+SESSION.FrontEndIp);
        LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Read HttpString -> " + REQUEST.HeadersString);
        LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Request Language -> "+REQUEST.Language);
//		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Request Device -> "+REQUEST.Device);

        //RESPONSE.ResponseType=REQUEST.ResponseType;

    } catch (int e) {

        throw;
    }
};