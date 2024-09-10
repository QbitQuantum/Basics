void Simulator::xMODR()
{
    GET_P1; GET_P2; GET_P3;
    p1->m_type = ValueType::REAL;
    p1->m_real = fmod(p2->m_real, p3->m_real);
}