void CVodesIntegrator::integrate(double tout)
{
    if (tout == m_time) {
        return;
    }
    int flag = CVode(m_cvode_mem, tout, m_y, &m_time, CV_NORMAL);
    if (flag != CV_SUCCESS) {
        throw CanteraError("CVodesIntegrator::integrate",
            "CVodes error encountered. Error code: {}\n{}\n"
            "Components with largest weighted error estimates:\n{}",
            flag, m_error_message, getErrorInfo(10));
    }
    m_sens_ok = false;
}