bool DXPlayerStatisticsData::LoadTraceStatisticsOnTheFly(const std::string& traceFilename, dxplugin::DXIntPluginManager& plugman)
{
  bool problems = false;

  if (!m_graph)
  {
    return false;
  }

  ClearOnTheFly();
  m_graph->ResetAll();

  NotifyBegin("Loading");

  //////////////////////////////////////////////////////////////////////////////
  // Open the trace file

  DXTraceManager traceman;
  if (!traceman.OpenRead(traceFilename))
  {
    NotifyEnded();
    return false;
  }
  
  //////////////////////////////////////////////////////////////////////////////
  // Load all the statistics from the trace
  
  plugman.BeginExperiment();

  DXStatisticPtr statistic = new DXStatistic();
  if (!plugman.GetStatisticsLegend(statistic))
  {
    plugman.EndExperiment();
    NotifyEnded();
    return false;
  }
  
  if (!AddStatisticOnTheFly(statistic))
  {
    plugman.EndExperiment();
    NotifyEnded();
    return false;
  }
  
  for (unsigned int i=0; i < traceman.GetMethodCallCount(); ++i)
  {
    NotifyProgress("Loading", (unsigned int) (i*100.0 / traceman.GetMethodCallCount()));

    DXMethodCallPtr call = NULL;
    if (!traceman.ReadMethodCall(&call, i))
    {
      problems = true;
      break;
    }
    else
    {
      plugman.ProcessCall(call);
      
      if (call->GetToken() == DXMethodCallHelper::TOK_IDirect3DDevice9_Present ||
          call->GetToken() == DXMethodCallHelper::TOK_IDirect3DSwapChain9_Present)
      {
        DXStatisticPtr statistic = new DXStatistic();
        if (!plugman.GetStatisticsFrame(statistic))
        {
          problems = true;
          break;
        }

        if (!AddStatisticOnTheFly(statistic))
        {
          problems = true;
          break;
        }
      }
    }
  }

  plugman.EndExperiment();
  
  if (problems || (GetCounterCount() == 0) || (GetStatisticsCount() == 0))
  {
    Clear();
    m_graph->ResetAll();
    NotifyEnded();
    return false;
  } 
  
  //////////////////////////////////////////////////////////////////////////////
  // Link new data series to the graph

  if (!FillPointBuffers())
  {
    Clear();
    m_graph->ResetAll();
    NotifyEnded();
    return false;
  }
  
  for (unsigned int i=0; i < GetCounterCount(); ++i)
  {
    TDataPoint* pointBuffer = NULL;
    if (GetPointBuffer(i, &pointBuffer) && pointBuffer)
    {
      m_graph->SetData(pointBuffer, GetStatisticsCount(), i);
      m_graph->GetCurve(i).SetLabel(GetLegendName(i));
    }
    else
    {
      problems = true;
      break;
    }
  }

  if (problems)
  {
    Clear();
    m_graph->ResetAll();
    NotifyEnded();
    return false;
  }

  //////////////////////////////////////////////////////////////////////////////
  // Setup graph axis

  m_graph->GetXAxis(0).SetLabel(_T("Frame"));
  m_graph->GetYAxis(0).SetLabel(_T(""));
  m_graph->GetXAxis(0).SetDisplayFmt(_T("%5.0f"));
  m_graph->GetYAxis(0).SetDisplayFmt(_T("%5.0f"));
  
  //////////////////////////////////////////////////////////////////////////////

  NotifyEnded();

  return true;
}