	void CWeatherChartsCtrl::Update()
	{
		string ID;
		CWVariablesCounter varCounts;
		bool bHourly = false;

		if (m_pStation)
		{
			ID = m_pStation->m_ID;
			varCounts = m_pStation->GetVariablesCount();
			//variables &= varCounts.GetVariables();
			for (size_t i = H_FIRST_VAR; i < NB_VAR_H; i++)
				if (m_variables.any() && !m_variables[i])
					varCounts[i] = CCountPeriod();

			bHourly = m_pStation->IsHourly();
		}



		CGraphVector chartsDefine = GetCharts(varCounts, bHourly);
		bool bValidPeriod = m_period.Begin() <= m_period.End();

		if (ID != m_lastStationID ||
			m_TM != m_lastTM ||
			m_stat != m_lastStat ||
			chartsDefine != m_lastChartsDefine ||
			((m_period != m_lastPeriod) && bValidPeriod) ||
			m_zoom != m_lastZoom)
		{


			m_lastStationID = ID;
			m_lastTM = m_TM;
			m_lastStat = m_stat;
			m_lastPeriod = m_period;

			m_charts.clear();
			m_splitters.clear();
			m_scrollHelper->ScrollToOrigin(true, true);

			if (m_pStation != NULL && !ID.empty())
			{


				CWaitCursor waitCursor;
				CRegistry registry("Charts");

				//pre-compute total graphics height 
				int totalHeight = 0;
				for (CGraphVector::iterator it1 = chartsDefine.begin(); it1 != chartsDefine.end(); it1++)
					totalHeight += max(50, min(800, registry.GetValue<int>("height" + to_string(it1->m_series.front().m_variable), 150)));

				CRect rect;
				GetClientRectSB(this, rect);
				if (totalHeight > rect.Height())//if they have a scrollbar, remove width of crolbar
					rect.right -= ::GetSystemMetrics(SM_CXVSCROLL);





				CTPeriod entirePeriod = m_pStation->GetEntireTPeriod(m_TM);
				CTPeriod period = entirePeriod;
				if (m_bPeriodEnable && m_period.IsInit())
				{
					period = m_period;
					period.Transform(m_TM);
				}
				else
				{
					int MAX_DATA_SIZE = registry.GetValue<int>("MaxDataSize", 10000);
					if (period.GetNbRef() > MAX_DATA_SIZE)
						period.End() = period.Begin() + MAX_DATA_SIZE;
				}



				int width = int(rect.Width()*m_zoom);// -10;
				int height = 0;


				int top = 0;
				for (CGraphVector::iterator it1 = chartsDefine.begin(); it1 != chartsDefine.end(); it1++)
				{
					int firstVar = it1->m_series.front().m_variable;
					int height = max(50, min(800, registry.GetValue<int>("height" + to_string(firstVar), 150)));

					CChartCtrlPtr pChart;
					pChart.reset(new CChartCtrl);
					//pChart->Create(this, CRect(-m_scrollHelper->GetScrollPos().cx, top, -m_scrollHelper->GetScrollPos().cx + width, top + height), CHART_BASE_ID + firstVar, WS_CHILD | WS_VISIBLE);
					pChart->Create(this, CRect(0, top, width, top + height), CHART_BASE_ID + firstVar, WS_CHILD | WS_VISIBLE);
					top += height;

					pChart->EnableRefresh(false);

					TChartString title = ToUTF16(it1->m_title);
					pChart->GetTitle()->SetVisible(title.empty());
					if (!title.empty())
						pChart->GetTitle()->AddString(title);

					pChart->GetLegend()->SetVisible(it1->m_bShowLegend);
					pChart->GetLegend()->DockLegend(CChartLegend::dsDockBottomLeft);
					pChart->GetLegend()->EnableShadow(false);
					pChart->GetLegend()->EnableBorder(false);
					pChart->GetLegend()->SetTransparent(true);

					pChart->SetPanEnabled(false);
					pChart->SetZoomEnabled(false);
					pChart->SetBackGradient(RGB(250, 250, 250), RGB(200, 200, 200), gtVertical);
					pChart->SetLineInfoEnabled(true);

					//****************
					//X

					CChartTRefAxis* pAxisX = (CChartTRefAxis*)pChart->GetAxis(CChartCtrl::BottomAxis);
					if (pAxisX == NULL)
					{
						pAxisX = new CChartTRefAxis;
						pAxisX->SetMinMax(period.Begin().GetRef(), period.End().GetRef());
						pAxisX->SetReferenceTick(period.Begin());

						pAxisX->SetPanZoomEnabled(false);
						pAxisX->EnableScrollBar(false);
						pAxisX->SetAutoHideScrollBar(false);
						pAxisX->GetGrid()->SetBackColor(gtAlternate2, RGB(235, 235, 255), RGB(245, 245, 255));
						pChart->AttachCustomAxis(pAxisX, CChartCtrl::BottomAxis);
						TChartString lable = ToUTF16(it1->m_Xtitle);
						if (!lable.empty())
							pAxisX->GetLabel()->SetText(lable);
					}

					ENSURE(pAxisX);

					for (CGraphSerieVector::iterator it2 = it1->m_series.begin(); it2 != it1->m_series.end(); it2++)
					{
						//****************
						//Y
						CChartCtrl::EAxisPos axis = it2->m_YAxis == 0 ? CChartCtrl::LeftAxis : CChartCtrl::RightAxis;
						CChartAxis* pAxisY = pChart->GetAxis(axis);
						if (pAxisY == NULL)
						{
							pAxisY = pChart->CreateStandardAxis(axis);
							pAxisY->SetAutomatic(true);
							pAxisY->SetPanZoomEnabled(false);
							pAxisY->EnableScrollBar(false);
							pAxisY->SetAutoHideScrollBar(false);
							TChartString lable = ToUTF16((it2->m_YAxis == 0) ? it1->m_Ytitle1 : it1->m_Ytitle2);
							pAxisY->GetLabel()->SetText(lable);

							//if (it2->m_YAxis == 1)
								//pAxisY->GetGrid()->SetVisible(false);
						}

						ENSURE(pAxisY);

						//****************
						//Series
						CChartXYSerie * pTheSerie = NULL;
						if (it2->m_type == CGraph::XY)
						{
							CChartPointsExSerie* pSerie = new CChartPointsExSerie(pChart.get());
							pChart->AttachCustomSerie(pSerie, false, it2->m_YAxis != 0);

							//general
							TChartString varName = WBSF::convert(GetVariableName(it2->m_variable));
							pSerie->SetName(varName);
							pSerie->EnableShadow(it2->m_bEnableShadow);
							pSerie->SetShadowDepth(it2->m_shadowDepth);
							pSerie->SetShadowColor(it2->m_shadowColor);

							//point
							pSerie->SetPointType((CChartPointsExSerie::PointType)it2->m_symbolType);
							pSerie->SetPointSize(it2->m_symbolWidth, it2->m_symbolHeight);
							pSerie->SetColor(it2->m_symbolColor);
							pSerie->SetFillPoint(it2->m_bSymbolFilled);
							pSerie->SetPointFillColor(it2->m_symbolFillColor);
							//line
							pSerie->SetLineStyle((CChartPointsExSerie::LineType)it2->m_lineStyle);
							pSerie->SetLineWidth(it2->m_lineWidth);
							pSerie->SetLineColor(it2->m_lineColor);
							pSerie->SetLineSmooth(it2->m_bLineSmoothed);
							//surface
							pSerie->SetSurfaceFillStyle((CChartPointsExSerie::FillStyle)it2->m_fillStyle);
							pSerie->SetSurfaceFillColor(it2->m_fillColor);
							pSerie->EnableTooltip(true);

							pTheSerie = pSerie;
						}
						else if (it2->m_type == CGraph::HISTOGRAM)
						{
							CChartBarSerie* pSerie = new CChartBarSerie(pChart.get());
							pChart->AttachCustomSerie(pSerie, false, it2->m_YAxis != 0);

							//general
							TChartString varName = WBSF::convert(GetVariableName(it2->m_variable));
							pSerie->SetName(varName);

							//histogram
							pSerie->SetHorizontal(it2->m_histDirection == CGraphSerie::HIST_HORIZONTAL);
							pSerie->SetBarWidth(it2->m_histBarWidth);
							pSerie->SetColor(it2->m_histBarColor);
							pSerie->SetBorderWidth(it2->m_histBorderWidth);
							pSerie->SetBorderColor(it2->m_histBorderColor);
							pSerie->EnableTooltip(true);

							pTheSerie = pSerie;
						}
						else if (it2->m_type == CGraph::CANDLE_STICK)
						{
							CChartCandlestickSerie* pSeries = new CChartCandlestickSerie(pChart.get());
						}
						else if (it2->m_type == CGraph::BOX_PLOT)
						{
							assert(false); //todo
						}



						if (it2->m_type == CGraph::XY || it2->m_type == CGraph::HISTOGRAM)
						{
							TVarH var = TVarH(it2->m_variable);

							SChartXYPoint* pPoints = new SChartXYPoint[period.size()];
							bool bIsFirstMissing = false;

							int ii = 0;
							for (CTRef TRef = period.Begin(); TRef <= period.End() /*&& ii < numberPoints*/; TRef++)
							{
								bool bInside = entirePeriod.IsInside(TRef);
								bool bIsInit = bInside && (*m_pStation)[TRef][var].IsInit();//don't access data to not create over data

								double x = bIsInit ? TRef.GetRef() : CHART_MISSING_VALUE;
								double y = bIsInit ? (*m_pStation)[TRef][var][m_stat] : CHART_MISSING_VALUE;
								//it2->m_statistic
								if (bIsInit || bIsFirstMissing)
								{
									pPoints[ii].X = x;
									pPoints[ii].Y = y;
									ii++;

									bIsFirstMissing = bIsInit;
								}
							}

							pTheSerie->SetSeriesOrdering(poNoOrdering);
							pTheSerie->SetPoints(pPoints, (int)ii);

							delete pPoints;
						}
						else
						{

						}
					}

					m_charts.push_back(pChart);


					//add splitter
					CSplitterControlPtr pSplitter(new CSplitterControl);
					pSplitter->Create(WS_CHILD | WS_VISIBLE, CRect(-m_scrollHelper->GetScrollPos().cx, top, -m_scrollHelper->GetScrollPos().cx + width, top + STD_GAP), this, SPLITTER_BASE_ID + firstVar, SPS_HORIZONTAL | SPS_DELTA_NOTIFY | SPS_DOWN_MOVE);
					m_splitters.push_back(pSplitter);
					top += STD_GAP;
				}

				ASSERT(m_splitters.size() == m_charts.size());
				for (int i = 0; i < m_splitters.size(); i++)
				{
					m_splitters[i]->RegisterLinkedWindow(SPLS_LINKED_UP, m_charts[i].get());

					for (int j = i + 1; j < m_charts.size(); j++)
					{
						m_splitters[i]->RegisterLinkedWindow(SPLS_LINKED_DOWN, m_charts[j].get());
						m_splitters[i]->RegisterLinkedWindow(SPLS_LINKED_DOWN, m_splitters[j].get());
					}
				}

				UpdateScrollHelper();

				//enable char redraw
				CWaitCursor cursor;
				//#pragma omp parrallel for
				for (CChartCtrlMap::iterator it = m_charts.begin(); it != m_charts.end(); it++)
				{
					(*it)->EnableRefresh(true);
				}
			}
		}
	}