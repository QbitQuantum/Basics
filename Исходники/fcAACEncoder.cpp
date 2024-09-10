fcAACEncoder::~fcAACEncoder()
{
    if (!loadModule()) { return; }

    faacEncClose_imp(m_handle);
    m_handle = nullptr;
}