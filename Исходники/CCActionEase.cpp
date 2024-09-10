void CCEaseSineOut::update(float time)
{
    m_pOther->update(sinf(time * (float)M_PI_2));
}