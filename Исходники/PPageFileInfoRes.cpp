CPPageFileInfoRes::~CPPageFileInfoRes()
{
    if (m_hIcon) {
        DestroyIcon(m_hIcon);
    }
}