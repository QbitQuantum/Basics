coor xaeBlockScene::collisionCheck(HTEXTURE hTex, int x, int y, int w, int h)
{
    if(!m_bClothes[y / h][x / w]) return coor(-1, -1);

    int nTexWidth = m_pHGE->Texture_GetWidth(hTex);
    DWORD* pPix = m_pHGE->Texture_Lock(hTex);
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            /** 某一个点不透明 */
            if((y + i) * nTexWidth + x + j >= nTexWidth * 600) break;
            if(pPix[(y + i) * nTexWidth + x + j] != 0xffff00ff)
            {
                /** 在圆的半径里 */
                if(DISTANCE(x + j, y + i, m_fBallX, m_fBallY) < (g_Setting.Block.m_nBallLength / 2))
                {
                    m_pHGE->Texture_Unlock(hTex);
                    return coor(x + j, y + i);
                }
            }
        }
    }

    m_pHGE->Texture_Unlock(hTex);
    return coor(-1, -1);
}