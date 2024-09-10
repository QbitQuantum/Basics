void PetStash::_PetErrorSystemMessage( int nErrorCode )
{
	CTString strMessage;

	switch(nErrorCode)
	{
	case ERROR_PET_STASH_KEEP_FAIL_ALREADY_EQ_PET:		//펫을 착용중이다.
		{
			strMessage.PrintF( _S( 825, "장착하고 있는 아이템은 보관할 수 없습니다.") );
		}
		break;
	case ERROR_PET_STASH_KEEP_FAIL_PET_SEAL:			//펫이 봉인상태이다.
		{
			strMessage.PrintF( _S( 5952, "봉인 된 펫은 보관 하실 수 없습니다.") );
		}
		break;
	case ERROR_PET_STASH_FAIL_ETC:						//알수 없는 오류
		{
			strMessage.PrintF( _S( 16, "알수 없는 오류가 발생했습니다.") );
		}
		break;
	case ERROR_PET_STASH_KEEP_FAIL_NOT_EXIST_PET:		//펫이 존재하지 않음
		{
			strMessage.PrintF( _S( 6071, "펫이 존재 하지 않습니다.") );
		}
		break;
	case ERROR_PET_STASH_KEEP_FAIL_TERMINATION_ITEM:	//펫 등록 아이템 사용기간 만료	
		{
			strMessage.PrintF( _S( 6072, "펫 창고 이용권 사용기간이 만료 되었습니다.") );
		}
		break;
	case ERROR_PET_STASH_KEEP_FAIL_FULL:				//펫 창고가 가득 참.
		{
			strMessage.PrintF( _S( 6073, "펫 창고에 공간이 부족 합니다.") );
		}
		break;
	case ERROR_PET_STASH_TAKE_FAIL:						//펫 찾기 실패
		{
			strMessage.PrintF( _S( 2850, "인벤토리가 가득 찼습니다.") );
		}
		break;
	case ERROR_PET_STASH_ERROR_NOT_USE_SYSTEM:			//펫 창고 시스템을 사용할 수 없습니다.
		{
			strMessage.PrintF( _S( 6075, "펫 창고 시스템을 사용할 수 없습니다.") );
		}
		break;
	default:
		return;
	}
	_pNetwork->ClientSystemMessage(strMessage, SYSMSG_ERROR);
}