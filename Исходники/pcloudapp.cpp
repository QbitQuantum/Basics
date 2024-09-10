void PCloudApp::incomingShares() // to del
{
    hideAllWindows();
    if (!incomingshareswin)
        incomingshareswin=new SharesWindow(this, 1);
    showWindow(incomingshareswin);
}