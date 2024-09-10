void *
vncDesktopThread::run_undetached(void *arg)
{
	//*******************************************************
	// INIT
	//*******************************************************
	capture=true;
	vnclog.Print(LL_INTERR, VNCLOG("Hook changed 1\n"));
	// Save the thread's "home" desktop, under NT (no effect under 9x)
	m_desktop->m_home_desktop = GetThreadDesktop(GetCurrentThreadId());
    vnclog.Print(LL_INTERR, VNCLOG("Hook changed 2\n"));
	// Attempt to initialise and return success or failure
	m_desktop->KillScreenSaver();
	{
		keybd_event(VK_CONTROL, 0, 0, 0);
        keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(500); //Give screen some time to kill screensaver
	}
    DWORD startup_error;
	if ((startup_error = m_desktop->Startup()) != 0)
	{
		//TAG14
		vncService::SelectHDESK(m_desktop->m_home_desktop);
		if (m_desktop->m_input_desktop)
			CloseDesktop(m_desktop->m_input_desktop);
		ReturnVal(startup_error);
		return NULL;
	}
	// Succeeded to initialise ok
	ReturnVal(0);

	// sf@2003 - Done here to take into account if the driver is actually activated
	m_desktop->InitHookSettings(); 

	// We set a flag inside the desktop handler here, to indicate it's now safe
	// to handle clipboard messages
	m_desktop->SetClipboardActive(TRUE);

	// All changes in the state of the display are stored in a local
	// UpdateTracker object, and are flushed to the vncServer whenever
	// client updates are about to be triggered
	rfb::SimpleUpdateTracker clipped_updates;
	rfb::ClippedUpdateTracker updates(clipped_updates, m_desktop->m_Cliprect);
	clipped_updates.enable_copyrect(true);
	rfb::Region2D rgncache;


	// Incoming update messages are collated into a single region cache
	// The region cache areas are checked for changes before an update
	// is triggered, and the changed areas are passed to the UpdateTracker
	rgncache = m_desktop->m_Cliprect;
	m_server->SetScreenOffset(m_desktop->m_ScreenOffsetx,m_desktop->m_ScreenOffsety,m_desktop->nr_monitors);

	// The previous cursor position is stored, to allow us to erase the
	// old instance whenever it moves.
	rfb::Point oldcursorpos;

	// The driver gives smaller rectangles to check
	// if Accuracy is 4 you eliminate pointer updates
	if (m_desktop->VideoBuffer() && m_desktop->m_hookdriver)
		m_desktop->m_buffer.SetAccuracy(4);

	//init vars
	m_desktop->m_SWSizeChanged=FALSE;
	m_desktop->m_SWtoDesktop=FALSE;
	m_desktop->m_SWmoved=FALSE;
	m_desktop->Hookdll_Changed = true;
	m_desktop->m_displaychanged=false;
	m_desktop->m_hookswitch=false;
	m_desktop->m_hookinited = FALSE;

	// Set driver cursor state
	XRichCursorEnabled= (FALSE != m_desktop->m_server->IsXRichCursorEnabled());
	if (!XRichCursorEnabled && m_desktop->m_videodriver) m_desktop->m_videodriver->HardwareCursor();
	if (XRichCursorEnabled && m_desktop->m_videodriver) m_desktop->m_videodriver->NoHardwareCursor();
	if (XRichCursorEnabled) m_server->UpdateCursorShape();

	InvalidateRect(NULL,NULL,TRUE);
	oldtick=timeGetTime();
	int fullpollcounter=0;
	//*******************************************************
	// END INIT
	//*******************************************************
	// START PROCESSING DESKTOP MESSAGES
	/////////////////////
	HANDLE threadHandle=NULL;
	stop_hookwatch=false;
	/////////////////////
	// We use a dynmiac value based on cpu usage
    //DWORD MIN_UPDATE_INTERVAL=33;
	/////////////////////
	bool looping=true;
	int waiting_update=0;
	SetEvent(m_desktop->restart_event);
	///
	Sleep(1000);
	rgncache.assign_union(rfb::Region2D(m_desktop->m_Cliprect));
	if (m_desktop->VideoBuffer() && m_desktop->m_hookdriver)
											{
												m_desktop->m_buffer.GrabRegion(rgncache,true,true);
											}
										else
											{
												m_desktop->m_buffer.GrabRegion(rgncache,false,true);
											}
	///
	while (looping && !fShutdownOrdered)
	{		
		DWORD result;
		newtick = timeGetTime();
		int waittime;
		waittime=100-(newtick-oldtick);
		if (m_desktop->VideoBuffer() && m_desktop->m_hookdriver) 
		{
			int fastcounter=0;
			POINT cursorpos;
			while (m_desktop->m_videodriver->oldaantal==m_desktop->pchanges_buf->counter)
			{
				Sleep(5);
				fastcounter++;
				if (fastcounter>20)
				{
					#ifdef _DEBUG
										char			szText[256];
										sprintf(szText,"fastcounter\n");
										OutputDebugString(szText);		
					#endif
					break;
				}
				if (GetCursorPos(&cursorpos) && 
										((cursorpos.x != oldcursorpos.x) ||
										(cursorpos.y != oldcursorpos.y))) break;
			}
			waittime=0;
		}
		else
		{
			waittime=waittime-(waiting_update*10);
		}
		if (waittime<0) waittime=0;
		if (waittime>100) waittime=100;

		result=WaitForMultipleObjects(6,m_desktop->trigger_events,FALSE,waittime);
		{
			//#ifdef _DEBUG
			//							char			szText[256];
			//							sprintf(szText,"WaitForMultipleObjects %i\n",result );
			//							OutputDebugString(szText);		
			//#endif

			// We need to wait until restart is done
			// else wait_timeout goes in to looping while sink window is not ready
			// if no window could be started in 10 seconds something went wrong, close
			// desktop thread.
			DWORD status=WaitForSingleObject(m_desktop->restart_event,10000);
			if (status==WAIT_TIMEOUT) looping=false;
			switch(result)
			{
				case WAIT_TIMEOUT:
				case WAIT_OBJECT_0:
				{
				waiting_update=0;
				ResetEvent(m_desktop->trigger_events[0]);
							{
								//measure current cpu usage of winvnc
								cpuUsage = usage.GetUsage();
								if (cpuUsage > m_server->MaxCpu()) 
									MIN_UPDATE_INTERVAL+=10;
								else MIN_UPDATE_INTERVAL-=10;
								if (MIN_UPDATE_INTERVAL<MIN_UPDATE_INTERVAL_MIN) MIN_UPDATE_INTERVAL=MIN_UPDATE_INTERVAL_MIN;
								if (MIN_UPDATE_INTERVAL>MIN_UPDATE_INTERVAL_MAX) MIN_UPDATE_INTERVAL=MIN_UPDATE_INTERVAL_MAX;


					//			vnclog.Print(LL_INTERR, VNCLOG("!PeekMessage \n"));
								// MAX 30fps
								newtick = timeGetTime(); // Better resolution than GetTickCount ;)
								if ((newtick-oldtick)<MIN_UPDATE_INTERVAL)
								{
									Sleep(MIN_UPDATE_INTERVAL-(newtick-oldtick));
									//continue;  Verify, this can cause screen lockup
									// We need another PeekMessage, but this is only done
									// by hookdll and viewer asking for new update
									// can cause a very long wait time
								}	
								
								#ifdef _DEBUG
										char			szText[256];
										sprintf(szText," cpu2: %d %i %i\n",cpuUsage,MIN_UPDATE_INTERVAL,newtick-oldtick);
										OutputDebugString(szText);		
								#endif
								oldtick=newtick;
								if (m_desktop->VideoBuffer() && m_desktop->m_hookdriver) handle_driver_changes(rgncache,updates);
								m_desktop->m_update_triggered = FALSE;
								g_update_triggered = FALSE;
								//if (m_desktop->m_timerid==NULL) m_desktop->m_timerid = SetTimer(m_desktop->m_hwnd, 1, 100, NULL);

								//*******************************************************
								// HOOKDLL START STOP need to be executed from the thread
								//*******************************************************
								if (m_desktop->Hookdll_Changed && !m_desktop->m_hookswitch)
								{
									vnclog.Print(LL_INTERR, VNCLOG("Hook changed \n"));
									m_desktop->StartStophookdll(m_desktop->On_Off_hookdll);
									if (m_desktop->On_Off_hookdll)
										m_desktop->m_hOldcursor = NULL; // Force mouse cursor grabbing if hookdll On
									// Todo: in case of hookdriver Off - Hoodll On -> hookdriver On - Hoodll Off
									// we must send an empty mouse cursor to the clients so they get rid of their local
									// mouse cursor bitmap
									m_desktop->Hookdll_Changed=false;
								}
								//*******************************************************
								// SCREEN DISPLAY HAS CHANGED, RESTART DRIVER (IF Used)
								//*******************************************************
								if (!m_server->IsThereFileTransBusy())
									if (!handle_display_change(threadHandle, rgncache, clipped_updates, updates))
									{
										//failed we need to quit thread
										looping=false;
										break;
									}
								//*******************************************************
								// END SCREEN DISPLAY HAS CHANGED
								//*******************************************************
					//			m_server->SetSWOffset(m_desktop->m_SWOffsetx,m_desktop->m_SWOffsety);
							
								//*******************************************************************
								// SINGLE WINDOW 
								// size SW changed
								// Position change -->change offsets
								//*******************************************************************
								bool SWSizeChanged=false;
								if (m_server->SingleWindow())
								{
									omni_mutex_lock l(m_desktop->m_update_lock);
									m_desktop->GetQuarterSize();
									m_server->SetSWOffset(m_desktop->m_SWOffsetx,m_desktop->m_SWOffsety);
									//SW size changed
									if (m_desktop->m_SWSizeChanged)
									{
										SWSizeChanged=true;
										m_desktop->m_SWSizeChanged=FALSE;
										m_desktop->GetQuarterSize();
										rgncache.assign_union(rfb::Region2D(m_desktop->m_Cliprect));
					//					vnclog.Print(LL_INTINFO, VNCLOG("4 %i %i %i %i \n"),m_desktop->m_Cliprect.br.x,m_desktop->m_Cliprect.br.y,m_desktop->m_Cliprect.tl.x,m_desktop->m_Cliprect.tl.y);
										updates.set_clip_region(m_desktop->m_Cliprect);
										m_server->SetSWOffset(m_desktop->m_SWOffsetx,m_desktop->m_SWOffsety);				
										m_desktop->m_buffer.ClearCache();
										m_desktop->m_buffer.BlackBack();
									}
									//SW position changed
									if (m_desktop->m_SWmoved)
									{
										m_desktop->m_SWmoved=FALSE;
										updates.set_clip_region(m_desktop->m_Cliprect);
										m_server->SetSWOffset(m_desktop->m_SWOffsetx,m_desktop->m_SWOffsety);				
										rgncache.assign_union(rfb::Region2D(m_desktop->m_Cliprect));
					//					vnclog.Print(LL_INTINFO, VNCLOG("5 %i %i %i %i \n"),m_desktop->m_Cliprect.br.x,m_desktop->m_Cliprect.br.y,m_desktop->m_Cliprect.tl.x,m_desktop->m_Cliprect.tl.y);
										m_desktop->m_buffer.ClearCache();
										m_desktop->m_buffer.BlackBack();
									}

								if (m_server->SingleWindow() && SWSizeChanged)
									{
										m_server->SetNewSWSize(m_desktop->m_SWWidth,m_desktop->m_SWHeight,FALSE);
										m_server->SetScreenOffset(m_desktop->m_ScreenOffsetx,m_desktop->m_ScreenOffsety,m_desktop->nr_monitors);
									}
								}// end update lock
								
								////////////////////////////////////////////////////////////////////////////////
								// END DYNAMIC CHANGES
								////////////////////////////////////////////////////////////////////////////////

								//Beep(1000,10);
								//
								// CALCULATE CHANGES
								m_desktop->m_UltraEncoder_used=m_desktop->m_server->IsThereAUltraEncodingClient();
					//			vnclog.Print(LL_INTERR, VNCLOG("UpdateWanted B\n"));
//#ifdef _DEBUG
////										char			szText[256];
//									sprintf(szText," m_desktop->m_server->UpdateWanted check\n");
//										OutputDebugString(szText);		
//#endif
								omni_mutex_lock l(m_desktop->m_update_lock);
								if (m_desktop->m_server->UpdateWanted())
								{
					//				vnclog.Print(LL_INTERR, VNCLOG("UpdateWanted N\n"));
									//TEST4
									// Re-render the mouse's old location if it's moved
									bool cursormoved = false;
									POINT cursorpos;
									if (GetCursorPos(&cursorpos) && 
										((cursorpos.x != oldcursorpos.x) ||
										(cursorpos.y != oldcursorpos.y)))
									{
					//					vnclog.Print(LL_INTERR, VNCLOG("UpdateWanted M %i %i %i %i\n"),cursorpos.x, oldcursorpos.x,cursorpos.y,oldcursorpos.y);
										cursormoved = TRUE;
										oldcursorpos = rfb::Point(cursorpos);
										// nyama/marscha - PointerPos. Inform clients about mouse move.
										m_desktop->m_server->UpdateMouse();
										if (MyGetCursorInfo)
										{
											MyCURSORINFO cinfo;
											cinfo.cbSize=sizeof(MyCURSORINFO);
											MyGetCursorInfo(&cinfo);
											m_desktop->SetCursor(cinfo.hCursor);
										}
									}
								
									//****************************************************************************
									//************* Polling ---- no driver
									//****************************************************************************
									if (!m_desktop->m_hookdriver || !m_desktop->can_be_hooked)
									{
										do_polling(threadHandle, rgncache, fullpollcounter, cursormoved);
									}
									//****************************************************************************
									//************* driver  No polling
									//****************************************************************************
									else 
									{
										// long lTime = timeGetTime();
										if (cursormoved)
										{
											// if (lTime - m_desktop->m_lLastMouseUpdateTime < 200)
											// 	continue;
											m_desktop->m_buffer.SetAccuracy(m_desktop->m_server->TurboMode() ? 2 : 1);
											// m_desktop->m_lLastMouseUpdateTime = lTime;
										}
										else
											// 4 is not that bad...but not perfect (especially with tree branchs display)
											m_desktop->m_buffer.SetAccuracy(m_desktop->m_server->TurboMode() ? 4 : 2); 
									}
									
									
									// PROCESS THE MOUSE POINTER
									// Some of the hard work is done in clients, some here
									// This code fetches the desktop under the old pointer position
									// but the client is responsible for actually encoding and sending
									// it when required.
									// This code also renders the pointer and saves the rendered position
									// Clients include this when rendering updates.
									// The code is complicated in this way because we wish to avoid 
									// rendering parts of the screen the mouse moved through between
									// client updates, since in practice they will probably not have changed.
								
									if (cursormoved && !m_desktop->m_hookdriver)
										{
											if (!m_desktop->m_cursorpos.is_empty())
											{
												// Cursor position seems to be outsite the bounding
												// When you make the screen smaller
												// add extra check
												rfb::Rect rect;
												int x = m_desktop->m_cursorpos.tl.x;
												int w = m_desktop->m_cursorpos.br.x-x;
												int y = m_desktop->m_cursorpos.tl.y;
												int h = m_desktop->m_cursorpos.br.y-y;
												if (ClipRect(&x, &y, &w, &h, m_desktop->m_bmrect.tl.x, m_desktop->m_bmrect.tl.y,
													m_desktop->m_bmrect.br.x-m_desktop->m_bmrect.tl.x, m_desktop->m_bmrect.br.y-m_desktop->m_bmrect.tl.y))
													{
														rect.tl.x = x;
														rect.br.x = x+w;
														rect.tl.y = y;
														rect.br.y = y+h;
														rgncache.assign_union(rect);
					//									vnclog.Print(LL_INTINFO, VNCLOG("6 %i %i %i %i \n"),m_desktop->m_cursorpos.br.x,m_desktop->m_cursorpos.br.y,m_desktop->m_cursorpos.tl.x,m_desktop->m_cursorpos.tl.y);
					//									vnclog.Print(LL_INTINFO, VNCLOG("6 %i %i %i %i \n"),rect.br.x,rect.br.y,rect.tl.x,rect.tl.y);
													}
											}

										}
									

									{
										// Prevent any clients from accessing the Buffer
										omni_mutex_lock l(m_desktop->m_update_lock);
										
										// CHECK FOR COPYRECTS
										// This actually just checks where the Foreground window is
										if (!m_desktop->m_hookdriver && !m_server->SingleWindow()) 
											m_desktop->CalcCopyRects(updates);
										
										// GRAB THE DISPLAY
										// Fetch data from the display to our display cache.
										// Update the scaled rects when using server side scaling
										// something wrong inithooking again
										// We make sure no updates are in the regions
										// sf@2002 - Added "&& m_desktop->m_hookdriver"
										// Otherwise we're still getting driver updates (from shared memory buffer)
										// after a m_hookdriver switching from on to off 
										// (and m_hookdll from off to on) that causes mouse cursor garbage,
										// or missing mouse cursor.
										if (m_desktop->VideoBuffer() && m_desktop->m_hookdriver)
											{
												m_desktop->m_buffer.GrabRegion(rgncache,true,capture);
											}
										else
											{
												m_desktop->m_buffer.GrabRegion(rgncache,false,capture);
											}
#ifdef _DEBUG
										char			szText[256];
										sprintf(szText," capture %i\n",capture);
										OutputDebugString(szText);		
#endif
										capture=true;
											
										// sf@2002 - v1.1.x - Mouse handling
										// If one client, send cursor shapes only when the cursor changes.
										// This is Disabled for now.
										if( !XRichCursorEnabled==m_desktop->m_server->IsXRichCursorEnabled())
											{
												XRichCursorEnabled= (FALSE != m_desktop->m_server->IsXRichCursorEnabled());
												if (m_desktop->m_videodriver)
														{
																if (!XRichCursorEnabled) m_desktop->m_videodriver->HardwareCursor();
																else m_desktop->m_videodriver->NoHardwareCursor();
														}

											}
										if (m_desktop->m_server->IsXRichCursorEnabled() && !m_desktop->m_UltraEncoder_used)
											{
												if (m_desktop->m_hcursor != m_desktop->m_hOldcursor || m_desktop->m_buffer.IsShapeCleared())
														{
																m_desktop->m_hOldcursor = m_desktop->m_hcursor;
																m_desktop->m_buffer.SetCursorPending(TRUE);
																if (!m_desktop->m_hookdriver) m_desktop->m_buffer.GrabMouse(); // Grab mouse cursor in all cases
																m_desktop->m_server->UpdateMouse();
																rfb::Rect rect;
																int x = m_desktop->m_cursorpos.tl.x;
																int w = m_desktop->m_cursorpos.br.x-x;
																int y = m_desktop->m_cursorpos.tl.y;
																int h = m_desktop->m_cursorpos.br.y-y;
																if (ClipRect(&x, &y, &w, &h, m_desktop->m_bmrect.tl.x, m_desktop->m_bmrect.tl.y,
																	m_desktop->m_bmrect.br.x-m_desktop->m_bmrect.tl.x, m_desktop->m_bmrect.br.y-m_desktop->m_bmrect.tl.y))
																		{
																			rect.tl.x = x;
																			rect.br.x = x+w;
																			rect.tl.y = y;
																			rect.br.y = y+h;
																			rgncache.assign_union(rect);
					//														vnclog.Print(LL_INTINFO, VNCLOG("7 %i %i %i %i \n"),m_desktop->m_cursorpos.br.x,m_desktop->m_cursorpos.br.y,m_desktop->m_cursorpos.tl.x,m_desktop->m_cursorpos.tl.y);
					//														vnclog.Print(LL_INTINFO, VNCLOG("6 %i %i %i %i \n"),rect.br.x,rect.br.y,rect.tl.x,rect.tl.y);
																		}
																m_server->UpdateCursorShape();
																}
											}
										else if (!m_desktop->m_hookdriver)// If several clients, send them all the mouse updates
											{												
												// Render the mouse
												//if (!m_desktop->VideoBuffer())
												m_desktop->m_buffer.GrabMouse();
												
												if (cursormoved /*&& !m_desktop->m_buffer.IsCursorUpdatePending()*/) 
															{
																// Inform clients that it has moved
																m_desktop->m_server->UpdateMouse();
																// Get the buffer to fetch the pointer bitmap
																if (!m_desktop->m_cursorpos.is_empty())
																{
																	rfb::Rect rect;
																int x = m_desktop->m_cursorpos.tl.x;
																int w = m_desktop->m_cursorpos.br.x-x;
																int y = m_desktop->m_cursorpos.tl.y;
																int h = m_desktop->m_cursorpos.br.y-y;
																if (ClipRect(&x, &y, &w, &h, m_desktop->m_bmrect.tl.x, m_desktop->m_bmrect.tl.y,
																	m_desktop->m_bmrect.br.x-m_desktop->m_bmrect.tl.x, m_desktop->m_bmrect.br.y-m_desktop->m_bmrect.tl.y))
																		{
																			rect.tl.x = x;
																			rect.br.x = x+w;
																			rect.tl.y = y;
																			rect.br.y = y+h;
																			rgncache.assign_union(rect);
																			vnclog.Print(LL_INTINFO, VNCLOG("8 %i %i %i %i \n"),m_desktop->m_cursorpos.br.x,m_desktop->m_cursorpos.br.y,m_desktop->m_cursorpos.tl.x,m_desktop->m_cursorpos.tl.y);
																			vnclog.Print(LL_INTINFO, VNCLOG("8 %i %i %i %i \n"),rect.br.x,rect.br.y,rect.tl.x,rect.tl.y);
																		}
																}

															}
												}	
										
											
										// SCAN THE CHANGED REGION FOR ACTUAL CHANGES
										// The hooks return hints as to areas that may have changed.
										// We check the suggested areas, and just send the ones that
										// have actually changed.
										// Note that we deliberately don't check the copyrect destination
										// here, to reduce the overhead & the likelihood of corrupting the
										// backbuffer contents.
										rfb::Region2D checkrgn;
										rfb::Region2D changedrgn;
										rfb::Region2D cachedrgn;

											
										//Update the backbuffer for the copyrect region
										if (!clipped_updates.get_copied_region().is_empty()) 
											{
												rfb::UpdateInfo update_info;
												rfb::RectVector::const_iterator i;
												clipped_updates.get_update(update_info);
												if (!update_info.copied.empty()) 
													{
														for (i=update_info.copied.begin(); i!=update_info.copied.end(); i++) 						
															m_desktop->m_buffer.CopyRect(*i, update_info.copy_delta);
													}
											}
										//Remove the copyrect region from the other updates					
										//checkrgn = rgncache.union_(clipped_updates.get_copied_region());	
										checkrgn = rgncache.subtract(clipped_updates.get_copied_region());	
										//make sure the copyrect is checked next update
										rgncache = clipped_updates.get_copied_region();
										//Check all regions for changed and cached parts
										//This is very cpu intensive, only check once for all viewers
										if (!checkrgn.is_empty())
											m_desktop->m_buffer.CheckRegion(changedrgn,cachedrgn, checkrgn);

										updates.add_changed(changedrgn);
										updates.add_cached(cachedrgn);
												
										clipped_updates.get_update(m_server->GetUpdateTracker());
									}  // end mutex lock

									// Clear the update tracker and region cache an solid
									clipped_updates.clear();
									// screen blanking
									if (m_desktop->OldPowerOffTimeout!=0)
										{
										if (!m_server->BlackAlphaBlending() || m_desktop->VideoBuffer())
											{
												if(OSversion()!=2)
												{
												SystemParametersInfo(SPI_SETPOWEROFFACTIVE, 1, NULL, 0);
												SendMessage(m_desktop->m_hwnd,WM_SYSCOMMAND,SC_MONITORPOWER,(LPARAM)2);
												}
					// don't block input here, this is the wrong thread!
											}
										}
					#ifdef AVILOG
									if (m_desktop->AviGen) m_desktop->AviGen->AddFrame((BYTE*)m_desktop->m_DIBbits);
					#endif
								}
								newtick = timeGetTime(); 
							}
						}
					break;

				case WAIT_OBJECT_0+1:
					ResetEvent(m_desktop->trigger_events[1]);
					m_desktop->lock_region_add=true;
					rgncache.assign_union(m_desktop->rgnpump);
					m_desktop->rgnpump.clear();
					m_desktop->lock_region_add=false;
					waiting_update++;
					break;
				case WAIT_OBJECT_0+2:
					ResetEvent(m_desktop->trigger_events[2]);
					break;
				case WAIT_OBJECT_0+3:
					if (MyGetCursorInfo)
					{
						MyCURSORINFO cinfo;
						cinfo.cbSize=sizeof(MyCURSORINFO);
						MyGetCursorInfo(&cinfo);
						m_desktop->SetCursor(cinfo.hCursor);
					}
					ResetEvent(m_desktop->trigger_events[3]);
					break;
				case WAIT_OBJECT_0+4:
					rgncache.assign_union(m_desktop->m_Cliprect);
					ResetEvent(m_desktop->trigger_events[4]);
					break;
				case WAIT_OBJECT_0+5:
					//break to close
					looping=false;
					ResetEvent(m_desktop->trigger_events[5]);
					break;
			}
		}
		
	}//while

	stop_hookwatch=true;
	if (threadHandle)
	{
		WaitForSingleObject( threadHandle, 5000 );
		CloseHandle(threadHandle);
	}
	
	m_desktop->SetClipboardActive(FALSE);
	vnclog.Print(LL_INTINFO, VNCLOG("quitting desktop server thread\n"));
	
	// Clear all the hooks and close windows, etc.
    m_desktop->SetBlockInputState(false);
	m_server->SingleWindow(false);
	vnclog.Print(LL_INTINFO, VNCLOG("quitting desktop server thread:SetBlockInputState\n"));
	
	// Clear the shift modifier keys, now that there are no remote clients
	vncKeymap::ClearShiftKeys();
	vnclog.Print(LL_INTINFO, VNCLOG("quitting desktop server thread:ClearShiftKeys\n"));
	
	// Switch back into our home desktop, under NT (no effect under 9x)
	//TAG14
	HWND mywin=FindWindow("blackscreen",NULL);
	if (mywin)SendMessage(mywin,WM_CLOSE, 0, 0);
	g_DesktopThread_running=false;
	vnclog.Print(LL_INTINFO, VNCLOG("quitting desktop server thread:g_DesktopThread_running=false\n"));
	m_desktop->Shutdown();
	vnclog.Print(LL_INTINFO, VNCLOG("quitting desktop server thread:m_desktop->Shutdown\n"));
	return NULL;
}