void GSDrawScanlineCodeGenerator::ReadTexel(const Xmm& dst, const Xmm& addr, const Xmm& temp1, const Xmm& temp2)
{
    if(m_cpu.has(util::Cpu::tSSE41))
    {
        ReadTexel(dst, addr, 0);
        ReadTexel(dst, addr, 1);
        ReadTexel(dst, addr, 2);
        ReadTexel(dst, addr, 3);
    }
    else
    {
        ReadTexel(dst, addr, 0);
        psrldq(addr, 4); // shuffle instead? (1 2 3 0 ~ rotation)
        ReadTexel(temp1, addr, 0);
        psrldq(addr, 4);
        punpckldq(dst, temp1);

        ReadTexel(temp1, addr, 0);
        psrldq(addr, 4);
        ReadTexel(temp2, addr, 0);
        // psrldq(addr, 4);
        punpckldq(temp1, temp2);

        punpcklqdq(dst, temp1);
    }
}