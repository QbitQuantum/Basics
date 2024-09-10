    void operator()(T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4)
    {
        using std::abs;

        t1 = adapted_pow(abs(t2), -beta1/(m_steps + 1)) *
            adapted_pow(abs(t3), -beta2/(m_steps + 1)) *
            adapted_pow(abs(t4), -beta3/(m_steps + 1)) *
            adapted_pow(abs(dt1/dt2), -alpha1/(m_steps + 1))*
            adapted_pow(abs(dt2/dt3), -alpha2/(m_steps + 1));

        t1 = 1/t1;
    };