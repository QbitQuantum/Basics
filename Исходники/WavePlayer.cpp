unsigned int WavePlayer::PlayThreadProcImpl()
{
	/// 定义为寄存器变量，因为它将会被高频率的使用，用于编译器优化
	register    ThreadMsg       tmsg = TMSG_ALIVE;

	/// 线程循环
	while (tmsg)
	{
		// 每次循环后，交出CPU控制权，放在此处，因为下面有continue语句
		Sleep(10);

		/// 首先检查线程消息
		EnterCriticalSection(&m_cs);
		tmsg = m_msgPlayThread;
		LeaveCriticalSection(&m_cs);
		// 线程要结束，退出线程循环
		if (!tmsg)   break;

		// 如果设备为空，表示还没有打开设备，需要打开设备
		if (m_hWaveoutDev == NULL)
		{
			EnterCriticalSection(&m_cs);
			MMRESULT mmres = waveOutOpen(&m_hWaveoutDev, WAVE_MAPPER, &m_waveData.wfmtx, (DWORD_PTR)WaveOutProc, (DWORD_PTR)this, CALLBACK_FUNCTION);
			LeaveCriticalSection(&m_cs);
			if (mmres != MMSYSERR_NOERROR)
			{
				// failed, try again.
				continue;
			}
		}

		// 检查空闲缓存块
		EnterCriticalSection(&m_cs);
		int free = m_wBlock.wfreeblock;
		LeaveCriticalSection(&m_cs);

		// 如果没有空闲的缓存了，等待...
		if (free < BP_TURN)
		{
			continue;
		}

		/////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////
		///                       < 播放主循环 >                              ///
		/////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////

		WAVEHDR     *current = NULL;

		/// BP_TURN为每次写入播放队列的块数
		for (unsigned int m = 0; m < BP_TURN; m++)
		{
			/// 当前空闲播放缓存块
			current = &m_wBlock.pWaveHdr[m_wBlock.wcurrblock];

			// 首先需要检查有没有被Unprepare掉
			if (current->dwFlags & WHDR_PREPARED)
			{
				waveOutUnprepareHeader(m_hWaveoutDev, current, sizeof(WAVEHDR));
			}

			/// 计算剩余需要播放的数据
			EnterCriticalSection(&m_cs);
			unsigned long left = m_waveData.dwSize - m_wBlock.wpos;
			unsigned int bDecodeFinished = m_waveData.bDecodeFinished;
			LeaveCriticalSection(&m_cs);
			unsigned long chunk = 0;

			if (left >= BLOCK_SIZE)
			{
				chunk = BLOCK_SIZE;
			}
			else if (!bDecodeFinished)
			{
				// 如果解码还没有结束，现有的数据量有不足以填满一个缓存块，先不写入缓存
				break;
			}
			else if (left && left < BLOCK_SIZE)
			{
				chunk = left;
			}
			else
			{
				//////////////////////////////////////////////////////////////////////
				///                 < 播放完成>                                    ///
				//////////////////////////////////////////////////////////////////////

				/// 获取空闲缓存块数量
				EnterCriticalSection(&m_cs);
				int free = m_wBlock.wfreeblock;
				LeaveCriticalSection(&m_cs);

				/// 当所有的缓存块都播放完了，才意味着播放真正完成
				if (free == BLOCK_COUNT)
				{
					/// Unprepare缓存块
					for (int j = 0; j < m_wBlock.wfreeblock; j++)
					{
						if (m_wBlock.pWaveHdr[j].dwFlags & WHDR_PREPARED)
						{
							waveOutUnprepareHeader(m_hWaveoutDev, &m_wBlock.pWaveHdr[j], sizeof(WAVEHDR));
						}
					}

					// 此时，才算真正的播放完成，关闭线程
					tmsg = TMSG_CLOSE;
					// 处理播放完成事件
					OnPlayFinished();
				}

				// 此break仅跳出该循环，没有跳出线程循环
				break;
			}

			/// prepare current wave data block header
			EnterCriticalSection(&m_cs);
			memcpy(current->lpData, &m_waveData.pData[m_wBlock.wpos], chunk);
			LeaveCriticalSection(&m_cs);

			current->dwBufferLength = chunk;   // sizeof block
			m_wBlock.wpos += chunk;   // update position

			/// prepare for playback
			waveOutPrepareHeader(m_hWaveoutDev, current, sizeof(WAVEHDR));

			/// push to the queue
			waveOutWrite(m_hWaveoutDev, current, sizeof(WAVEHDR));

			/// 减小空闲块计数
			EnterCriticalSection(&m_cs);
			m_wBlock.wfreeblock--;
			LeaveCriticalSection(&m_cs);

			/// 使当前空闲块指向下一个
			m_wBlock.wcurrblock++;
			m_wBlock.wcurrblock %= BLOCK_COUNT;
		}

	}/// thread

	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	///
	///            < force to close device which are still playing > 
	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	if (m_hWaveoutDev)
	{
		waveOutReset(m_hWaveoutDev);

		/// unprepare any blocks that are still prepared
		for (int j = 0; j < BLOCK_COUNT; j++)
		{
			if (m_wBlock.pWaveHdr[j].dwFlags & WHDR_PREPARED)
			{
				waveOutUnprepareHeader(m_hWaveoutDev, &m_wBlock.pWaveHdr[j], sizeof(WAVEHDR));
			}
		}

		waveOutClose(m_hWaveoutDev);
		m_hWaveoutDev = NULL;
	}

	return THREAD_EXIT;
}