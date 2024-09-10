//------------------------------------------------------------------------------
// CUISiegeWarfareDoc::TimeConfirm
// Explain:  공성 시간 확정 알림(공지)
// Date : 2005-07-06,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfareDoc::TimeConfirm( int nZoneIndex, int nMonth, int nDay, int nHour, int nMin )
{
	m_nZoneIndex = nZoneIndex;
	
	CTString strMessage;
	strMessage.PrintF( _S( 2017, "[%s]지역 [%s]공성이 %d월 %d일 %d시로 예정되었습니다." ),	
		CZoneInfo::getSingleton()->GetZoneName( nZoneIndex ), GetCastleName( nZoneIndex ), nMonth, nDay, nHour );	
	// [2012/06/04 : Sora] ITS 8986 공성시작전 공성시작 지점으로 이동 시 캐릭터 이동불가 상태 발생 수정
	// 공성 메시지 출력하면서 해당 UI를 활성화 시켜주어햐 한다. 공성 메시지 출력 방식 변경
	CUIManager::getSingleton()->GetSiegeWarfare()->SetNotice( strMessage );
}