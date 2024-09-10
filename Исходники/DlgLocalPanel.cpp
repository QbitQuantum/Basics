void CDlgLocalPanel::UpdateComponents()
{
    CRect	rcClient;
    GetClientRect(&rcClient);
    if (rcClient.IsRectEmpty())		return;

    CRect	rcPushAddr, rcEdtAddr;

    CRect	rcVideo;
    rcVideo.SetRect(rcClient.left+VIDEO_WINDOW_BORDER_WIDTH, 0,
                    rcClient.right-VIDEO_WINDOW_BORDER_WIDTH, rcClient.bottom-VIDEO_WINDOW_BORDER_WIDTH);

    __MOVE_WINDOW(pDlgVideo, rcVideo);
}