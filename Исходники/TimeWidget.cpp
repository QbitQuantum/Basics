void ezTimeWidget::UpdateStats()
{
  if (!isVisible())
    return;

  if (!ezTelemetry::IsConnectedToServer())
  {
    ListClocks->setEnabled(false);
    return;
  }

  ListClocks->setEnabled(true);

  if (m_bClocksChanged)
  {
    m_bClocksChanged = false;

    ListClocks->blockSignals(true);
    ListClocks->clear();

    for (ezMap<ezString, ezTimeWidget::ClockData>::Iterator it = m_ClockData.GetIterator(); it.IsValid(); ++it)
    {
      ListClocks->addItem(it.Key().GetData());

      QListWidgetItem* pItem = ListClocks->item(ListClocks->count() - 1);
      pItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable);
      pItem->setCheckState (it.Value().m_bDisplay ? Qt::Checked : Qt::Unchecked);
      pItem->setData(Qt::UserRole, QString(it.Key().GetData()));

      pItem->setTextColor(s_Colors[it.Value().m_iColor % s_uiMaxColors]);

      it.Value().m_pListItem = pItem;
    }

    ListClocks->blockSignals(false);
  }

  QPainterPath pp[s_uiMaxColors];

  ezTime tMin = ezTime::Seconds(100.0);
  ezTime tMax = ezTime::Seconds(0.0);

  for (ezMap<ezString, ClockData>::Iterator it = s_pWidget->m_ClockData.GetIterator(); it.IsValid(); ++it)
  {
    if (it.Value().m_TimeSamples.IsEmpty() || !it.Value().m_bDisplay)
      continue;

    const ezUInt32 uiColorPath = it.Value().m_iColor % s_uiMaxColors;
    ClockData& Clock = it.Value();
    const ezDeque<TimeSample>& Samples = Clock.m_TimeSamples;

    ezUInt32 uiFirstSample = 0;

    while ((uiFirstSample < Samples.GetCount()) && (m_MaxGlobalTime - Samples[uiFirstSample].m_AtGlobalTime > m_DisplayInterval))
      ++uiFirstSample;

    if (uiFirstSample < Samples.GetCount())
    {
      pp[uiColorPath].moveTo (QPointF((Samples[uiFirstSample].m_AtGlobalTime - m_MaxGlobalTime).GetSeconds(), Samples[uiFirstSample].m_Timestep.GetSeconds()));

      for (ezUInt32 i = uiFirstSample + 1; i < Samples.GetCount(); ++i)
      {
        pp[uiColorPath].lineTo (QPointF ((Samples[i].m_AtGlobalTime - m_MaxGlobalTime).GetSeconds(), Samples[i].m_Timestep.GetSeconds()));

        tMin = ezMath::Min(tMin, Samples[i].m_Timestep);
        tMax = ezMath::Max(tMax, Samples[i].m_Timestep);
      }
    }
  }

  for (ezUInt32 i = 0; i < s_uiMaxColors; ++i)
    m_pPath[i]->setPath(pp[i]);

  // render the helper lines for time values
  {
    QPainterPath pMax;

    for (ezUInt32 i = 1; i < 10; ++i)
    {
      pMax.moveTo(QPointF (-m_DisplayInterval.GetSeconds(), ezTime::Milliseconds(10.0 * i).GetSeconds()));
      pMax.lineTo(QPointF (0, ezTime::Milliseconds(10.0 * i).GetSeconds()));
    }

    m_pPathMax->setPath(pMax);
  }

  ezTime tShowMax = ezTime::Seconds(1.0 / 10.0);

  for (ezUInt32 t = 25; t < 100; t += 25)
  {
    tShowMax = ezTime::Milliseconds(1) * t;

    if (tMax < tShowMax)
      break;
  }

  {
    TimeView->setSceneRect (QRectF (-m_DisplayInterval.GetSeconds(), 0, m_DisplayInterval.GetSeconds(), tShowMax.GetSeconds()));
    TimeView->fitInView    (QRectF (-m_DisplayInterval.GetSeconds(), 0, m_DisplayInterval.GetSeconds(), tShowMax.GetSeconds()));
  }

  // once a second update the display of the clocks in the list
  if (ezTime::Now() - m_LastUpdatedClockList > ezTime::Seconds(1))
  {
    m_LastUpdatedClockList = ezTime::Now();

    ezStringBuilder s;
    s.Format("Max: %.0fms", tShowMax.GetMilliseconds());
    LabelMaxTime->setText(s.GetData());

    for (ezMap<ezString, ezTimeWidget::ClockData>::Iterator it = m_ClockData.GetIterator(); it.IsValid(); ++it)
    {
      const ezTimeWidget::ClockData& Clock = it.Value();

      if (!Clock.m_pListItem || Clock.m_TimeSamples.IsEmpty())
        continue;

      ezStringBuilder sTooltip;
      sTooltip.Format("<p>Clock: %s<br>Max Time Step: <b>%.2fms</b><br>Min Time Step: <b>%.2fms</b><br></p>",
        it.Key().GetData(), Clock.m_MaxTimestep.GetMilliseconds(), Clock.m_MinTimestep.GetMilliseconds());

      Clock.m_pListItem->setToolTip(sTooltip.GetData());
    }
  }
}