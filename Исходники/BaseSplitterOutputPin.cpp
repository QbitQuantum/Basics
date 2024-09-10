HRESULT CBaseSplitterOutputPin::DeliverPacket(CAutoPtr<Packet> p)
{
	HRESULT hr;

	long nBytes = (long)p->GetCount();

	if (nBytes == 0) {
		return S_OK;
	}

	DWORD nFlag = (static_cast<CBaseSplitterFilter*>(m_pFilter))->GetFlag();

	if (p->rtStart != INVALID_TIME && (nFlag & PACKET_PTS_DISCONTINUITY)) {
		// Filter invalid PTS value (if too different from previous packet)
		if (!IsDiscontinuous() && !((nFlag & PACKET_PTS_VALIDATE_POSITIVE) && p->rtStart < 0)) {
			REFERENCE_TIME rt = p->rtStart + m_rtOffset;
			if (_abs64(rt - m_rtPrev) > MAX_PTS_SHIFT) {
				m_rtOffset += m_rtPrev - rt;
				DbgLog((LOG_TRACE, 3, L"CBaseSplitterOutputPin::DeliverPacket() : Packet discontinuity detected, adjusting offset to %I64d", m_rtOffset));
			}
		}

		p->rtStart	+= m_rtOffset;
		p->rtStop	+= m_rtOffset;

		m_rtPrev	= p->rtStart;
	}

	m_brs.nBytesSinceLastDeliverTime += nBytes;

	if (p->rtStart != INVALID_TIME) {
		if (m_brs.rtLastDeliverTime == INVALID_TIME) {
			m_brs.rtLastDeliverTime = p->rtStart;
			m_brs.nBytesSinceLastDeliverTime = 0;
		}

		if (m_brs.rtLastDeliverTime + 10000000 < p->rtStart) {
			REFERENCE_TIME rtDiff = p->rtStart - m_brs.rtLastDeliverTime;

			double secs, bits;

			secs = (double)rtDiff / 10000000;
			bits = 8.0 * m_brs.nBytesSinceLastDeliverTime;
			m_brs.nCurrentBitRate = (DWORD)(bits / secs);

			m_brs.rtTotalTimeDelivered += rtDiff;
			m_brs.nTotalBytesDelivered += m_brs.nBytesSinceLastDeliverTime;

			secs = (double)m_brs.rtTotalTimeDelivered / 10000000;
			bits = 8.0 * m_brs.nTotalBytesDelivered;
			m_brs.nAverageBitRate = (DWORD)(bits / secs);

			m_brs.rtLastDeliverTime = p->rtStart;
			m_brs.nBytesSinceLastDeliverTime = 0;
			/*
						TRACE(_T("[%d] c: %d kbps, a: %d kbps\n"),
							p->TrackNumber,
							(m_brs.nCurrentBitRate+500)/1000,
							(m_brs.nAverageBitRate+500)/1000);
			*/
		}

		double dRate = 1.0;
		if (SUCCEEDED((static_cast<CBaseSplitterFilter*>(m_pFilter))->GetRate(&dRate))) {
			p->rtStart = (REFERENCE_TIME)((double)p->rtStart / dRate);
			p->rtStop = (REFERENCE_TIME)((double)p->rtStop / dRate);
		}
	}

	do {
		CComPtr<IMediaSample> pSample;
		if (S_OK != (hr = GetDeliveryBuffer(&pSample, NULL, NULL, 0))) {
			break;
		}

		if (nBytes > pSample->GetSize()) {
			pSample.Release();

			ALLOCATOR_PROPERTIES props, actual;
			if (S_OK != (hr = m_pAllocator->GetProperties(&props))) {
				break;
			}
			props.cbBuffer = nBytes*3/2;

			if (props.cBuffers > 1) {
				if (S_OK != (hr = __super::DeliverBeginFlush())) {
					break;
				}
				if (S_OK != (hr = __super::DeliverEndFlush())) {
					break;
				}
			}

			if (S_OK != (hr = m_pAllocator->Decommit())) {
				break;
			}
			if (S_OK != (hr = m_pAllocator->SetProperties(&props, &actual))) {
				break;
			}
			if (S_OK != (hr = m_pAllocator->Commit())) {
				break;
			}
			if (S_OK != (hr = GetDeliveryBuffer(&pSample, NULL, NULL, 0))) {
				break;
			}
		}

		if (p->pmt) {
			pSample->SetMediaType(p->pmt);
			p->bDiscontinuity = true;

			// CAutoLock cAutoLock(m_pLock); // this can cause the lock
			m_mts.RemoveAll();
			m_mts.Add(*p->pmt);
		}

		bool fTimeValid = p->rtStart != INVALID_TIME;

#if defined(_DEBUG) && 0
		TRACE(_T("[%d]: d%d s%d p%d, b=%d, [%20I64d - %20I64d]\n"),
			  p->TrackNumber,
			  p->bDiscontinuity, p->bSyncPoint, fTimeValid && p->rtStart < 0,
			  nBytes, p->rtStart, p->rtStop);
#endif

		ASSERT(!p->bSyncPoint || fTimeValid);

		BYTE* pData = NULL;
		if (S_OK != (hr = pSample->GetPointer(&pData)) || !pData) {
			break;
		}
		memcpy(pData, p->GetData(), nBytes);
		if (S_OK != (hr = pSample->SetActualDataLength(nBytes))) {
			break;
		}
		if (S_OK != (hr = pSample->SetTime(fTimeValid ? &p->rtStart : NULL, fTimeValid ? &p->rtStop : NULL))) {
			break;
		}
		if (S_OK != (hr = pSample->SetMediaTime(NULL, NULL))) {
			break;
		}
		if (S_OK != (hr = pSample->SetDiscontinuity(p->bDiscontinuity))) {
			break;
		}
		if (S_OK != (hr = pSample->SetSyncPoint(p->bSyncPoint))) {
			break;
		}
		if (S_OK != (hr = pSample->SetPreroll(fTimeValid && p->rtStart < 0))) {
			break;
		}
		if (S_OK != (hr = Deliver(pSample))) {
			break;
		}
	} while (false);

	return hr;
}