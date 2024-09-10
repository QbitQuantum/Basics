void CPlayerSubresyncBar::UpdatePreview()
{
    if (m_mode == VOBSUB || m_mode == TEXTSUB) {
        if (0/*m_bUnlink*/) {
            for (int i = 0, j = (int)m_sts.GetCount(); i < j; i++) {
                bool bStartMod, bEndMod, bStartAdj, bEndAdj;
                GetCheck(i, bStartMod, bEndMod, bStartAdj, bEndAdj);
                m_sts[i].start = (bStartMod || bStartAdj) ? m_subtimes[i].newStart : m_subtimes[i].orgStart;
                m_sts[i].end = (bEndMod || bEndAdj) ? m_subtimes[i].newEnd : m_subtimes[i].orgEnd;
            }
        } else {
            CAtlArray<int> schk;

            for (int i = 0, j = (int)m_sts.GetCount(); i < j;) {
                schk.RemoveAll();

                int start = i, end;

                for (end = i; end < j; end++) {
                    int data = m_displayData[end].flags;
                    if ((data & TSEP) && end > i) {
                        break;
                    }
                    if (data & (TSMOD | TSADJ)) {
                        schk.Add(end);
                    }
                }

                if (schk.IsEmpty()) {
                    for (; start < end; start++) {
                        m_sts[start].start = m_subtimes[start].orgStart;
                        m_sts[start].end = m_subtimes[start].orgEnd;
                    }
                } else if (schk.GetCount() == 1) {
                    int k = schk[0];
                    int dt = m_subtimes[k].newStart - m_subtimes[k].orgStart;
                    for (; start < end; start++) {
                        m_sts[start].start = m_subtimes[start].orgStart + dt;
                        m_sts[start].end = (m_displayData[start].flags & TEMOD)
                                           ? m_subtimes[start].newEnd
                                           : (m_subtimes[start].orgEnd + dt);
                    }
                } else if (schk.GetCount() >= 2) {
                    int i0 = 0;
                    int i1 = 0;
                    int ti0 = 0;
                    int ds = 0;
                    double m = 0;

                    int k, l;
                    for (k = 0, l = (int)schk.GetCount() - 1; k < l; k++) {
                        i0 = schk[k];
                        i1 = schk[k + 1];

                        ti0 = m_subtimes[i0].orgStart;
                        ds = m_subtimes[i1].orgStart - ti0;

                        if (ds == 0) {
                            SetSTS0(start, i1, ti0);
                        } else {
                            m = double(m_subtimes[i1].newStart - m_subtimes[i0].newStart) / ds;
                            SetSTS1(start, i1, ti0, m, i0);
                        }

                    }

                    ASSERT(k > 0);
                    if (ds == 0) {
                        SetSTS0(start, end, ti0);
                    } else {
                        SetSTS1(start, end, ti0, m, i0);
                    }
                }

                i = end;
            }
        }

        m_sts.CreateSegments();

        for (size_t i = 0, j = m_sts.GetCount(); i < j; i++) {
            m_displayData[i].tPrevStart = m_sts[i].start;
            m_displayData[i].tPrevEnd = m_sts[i].end;
        }

        m_list.Invalidate();

        if (IsWindowVisible()) {
            SaveSubtitle();
        }
    }
}