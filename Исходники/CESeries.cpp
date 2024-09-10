//析构函数
CCESeries::~CCESeries()
{
    if (m_bOpened)
    {
        //关闭串口
        ClosePort();
    }
}