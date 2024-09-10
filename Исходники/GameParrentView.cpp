//获取界面
bool CGameParrentView::GetGameViewImage(CImage & ImageBuffer, int nXPos, int nYPos, int nWidth, int nHeight)
{
    ASSERT(ImageBuffer.IsNull()==false);
    ASSERT(m_ImageBuffer.IsNull()==false);
    if (m_ImageBuffer.IsNull()==false)
    {
        m_ImageBuffer.BitBlt(ImageBuffer.GetDC(),nXPos,nYPos,nWidth,nHeight,nXPos,nYPos);
        ImageBuffer.ReleaseDC();
        return true;
    }
    return false;
}