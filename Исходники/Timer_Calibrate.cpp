void Timer_Calibrate::OnTimer(UINT nIDEvent)
{

    UpdateData(true);
    Read_Multi(g_tstat_id,machine_time,200,8,3);
    if(machine_time[1]<10)
        m_machine_time.Format(_T("   %d/%d/%d0%d %d:%d:%d"),machine_time[2],machine_time[4],machine_time[0],machine_time[1],machine_time[5],machine_time[6],machine_time[7]);
    else
        m_machine_time.Format(_T("   %d/%d/%d%d %d:%d:%d"),machine_time[2],machine_time[4],machine_time[0],machine_time[1],machine_time[5],machine_time[6],machine_time[7]);
    if(machine_time[5]>12)
        m_machine_time+=_T(" PM");
    else
        m_machine_time+=_T(" AM");
    if(had_select==false)

        m_NCDateCtrl.SetDate(machine_time[0]*100+machine_time[1],machine_time[2],machine_time[4]);
    m_NCTimeCtrl.SetTime(machine_time[5],machine_time[6],machine_time[7]);

    m_time_time=m_time_time.GetCurrentTime();

    TIME_ZONE_INFORMATION temp;
    GetTimeZoneInformation(&temp);
    m_time_zone_str=temp.StandardName;
    int i_temp=read_one(g_tstat_id,11);
    if(temp.Bias>0)
    {
        m_time_zone=_T("-");
        CString t;
        t.Format(_T("%d"),temp.Bias/60);
        m_time_zone=m_time_zone+t;
        if(i_temp==255)
        {
            m_building_time_zone.SetCurSel(12-temp.Bias/60);
            write_one(g_tstat_id,11,short(12-temp.Bias/60));
        }
        else if(i_temp>=0)
            m_building_time_zone.SetCurSel(i_temp);
    }
    else
    {
        m_time_zone=_T("+");
        CString t;
        t.Format(_T("%d"),temp.Bias/-60);
        m_time_zone=m_time_zone+t;
        if(i_temp==255)
        {
            m_building_time_zone.SetCurSel(12-temp.Bias/60);
            write_one(g_tstat_id,11,(short)(12-temp.Bias/60));
        }
        else if(i_temp>=0)
            m_building_time_zone.SetCurSel(i_temp);
    }
    UpdateData(false);


    /*
    m_time_time=m_time_time.GetCurrentTime();
    UpdateData(false);
    */

    CDialog::OnTimer(nIDEvent);
}