/**
 @brief 
*/
BOOL XESkillMng::ParsingEffect( TiXmlAttribute *pAttr,
								const char *cAttrName,
								const char *cParam,
								XSkillDat* pSkillDat,
								EFFECT *pEffect )
{
#ifdef _DEBUG
	_tstring strUTF16 = U82SZ(cAttrName);
#endif
	if( XSAME( cAttrName, 2 ) ) {	// 시전대상
		pEffect->castTarget = (xtCastTarget) ParsingParam( cParam );
	} else
	if( XSAME( cAttrName, 15 ) )	// 시전대상 우호
	{
		pEffect->castfiltFriendship = (xtFriendshipFilt) ParsingParam( cParam );
	} else
	if( XSAME( cAttrName, 199 ) )	// 시전조건
	{
		pEffect->castTargetCond = (xtTargetCond) ParsingParam( cParam );
	} else
	if( XSAME( cAttrName, 17 ) )	// 시전대상플레이어
	{
		pEffect->castfiltPlayerType = (xtPlayerTypeFilt) ParsingParam( cParam );
	} else
	if( XSAME( cAttrName, 126 ) )	// 시전범위타입
	{
		pEffect->castTargetRange = (xtTargetRangeType) ParsingParam( cParam );
	} else
	if( XSAME( cAttrName, 20 ) )	// 시전대상이펙트
	{	
		pEffect->m_CastTargetEff.m_strSpr = U82SZ( cParam );
	} else
	if( XSAME( cAttrName, 21 ) )	// 시전대상이펙트id
	{	
		pEffect->m_CastTargetEff.m_idAct = (int)pAttr->IntValue();
	} else
	if( XSAME( cAttrName, 261 ) )	// 시전대상이펙트반복
	{
		pEffect->m_CastTargetEff.m_Loop = (xtAniLoop)ParsingParam( cParam );
	} else
	if( XSAME( cAttrName, 156 ) )	// 시전대상이펙트생성지점
	{
		pEffect->m_CastTargetEff.m_Point = (xtPoint) ParsingParam( cParam );
	} else
	if( XSAME( cAttrName, 60 ) || XSAME( cAttrName, 127 ) )	// /시전범위 시전길이
	{	
		pEffect->castSize.w = (float)pAttr->DoubleValue();
	} else
	if( XSAME( cAttrName, 128 ) )	// 시전폭
	{
		pEffect->castSize.h = (float)pAttr->DoubleValue();
	} else
	if( XSAME( cAttrName, 22 ) )	// 지속시간
	{	
//		pEffect->secDuration = (float)pAttr->DoubleValue();
		_tstring strParam = U82SZ( cParam );
		_tstring strAttrName = U82SZ( cAttrName );
		ReadTableAry( strAttrName.c_str(),
			pSkillDat->GetstrIdentifier().c_str(),
			&pEffect->arySecDuration, strParam.c_str(), xVAL );
	} else
	if( XSAME( cAttrName, 233 ) )	// 발동지속시간
	{	
		pEffect->secDurationInvoke = (float)pAttr->DoubleValue();
	} else
	if( XSAME( cAttrName, 23 ) )	// 시전사운드
	{	
		pEffect->idCastSound = (int)pAttr->IntValue();
	} else
	if( XSAME( cAttrName, 3 ) )	// 발동대상
	{
		pEffect->invokeTarget = (xtInvokeTarget) ParsingParam( cParam );
	} else
	if( XSAME( cAttrName, 10 ) )	// 발동대상 우호
	{
		pEffect->invokefiltFriendship = (xtFriendshipFilt) ParsingParam( cParam );
	} else
	if( XSAME( cAttrName, 24 ) )	// 발동대상플레이어
	{
		pEffect->invokefiltPlayerType = (xtPlayerTypeFilt) ParsingParam( cParam );
	} else
	if( XSAME( cAttrName, 122 ) )	// 발동시점
	{
		pEffect->invokeJuncture = (xtJuncture) ParsingParam( cParam );
	} else
	if( XSAME( cAttrName, 25 ) )	// 발동대상조건
	{
		pEffect->invokeTargetCondition = (xtCondition) ParsingParam( cParam );
	} else
	if( XSAME( cAttrName, 99 ) )	// 발동스킬id
	{	
		pEffect->idInvokeSkill = (ID)pAttr->IntValue();
	} else
	if( XSAME( cAttrName, 26 ) )	// 발동스킬
	{	
		pEffect->strInvokeSkill = U82SZ( cParam );
	} else
	if( XSAME( cAttrName, 232 ) )	// 발동시점스킬
	{
		pEffect->strInvokeTimeSkill = U82SZ( cParam );
	} else
	if( XSAME( cAttrName, 239 ) )	// 발동조건스킬
	{
		pEffect->strInvokeIfHaveBuff = U82SZ( cParam ); 
	} else
	if( XSAME( cAttrName, 116 ) )	// 발동확률
	{
		const _tstring strParam = U82SZ( cParam ); 
		const _tstring strAttrName = U82SZ( cAttrName );
		ReadTableAry( strAttrName.c_str(), 
					pSkillDat->GetstrIdentifier().c_str(), 
					&pEffect->aryInvokeRatio, strParam.c_str(), xPERCENT );
	} else
	if( XSAME( cAttrName, 257 ) )	{// 발동적용확률
		const _tstring strParam = U82SZ( cParam ); 
		const _tstring strAttrName = U82SZ( cAttrName );
		ReadTableAry2( strAttrName.c_str(), 
					pSkillDat->GetstrIdentifier().c_str(), 
					&pEffect->m_aryInvokeApplyRatio, strParam.c_str(), xPERCENT );
	} else
	if( XSAME( cAttrName, 7 ) || XSAME( cAttrName, 161 ) )	// 발동파라메터/효과인덱스.
	{	
		pEffect->invokeParameter = (int)ParsingParam( cParam );
	} else
	if( XSAME( cAttrName, 30 ) )	// 발동대상이펙트
	{	
		pEffect->m_invokeTargetEff.m_strSpr = U82SZ( cParam );
	} else
	if( XSAME( cAttrName, 31 )  )	// 발동대상이펙트id
	{	
		pEffect->m_invokeTargetEff.m_idAct = (int)pAttr->IntValue();
	} else
	if( XSAME( cAttrName, 157 ) )	// 발동대상이펙트생성지점
	{
		pEffect->m_invokeTargetEff.m_Point = (xtPoint) ParsingParam( cParam );
	} else
	if( XSAME( cAttrName, 262 ) )	// 발동대상이펙트반복
	{
		pEffect->m_invokeTargetEff.m_Loop = (xtAniLoop)ParsingParam( cParam );
	} else
	if( XSAME( cAttrName, 228) )	// 증폭파라메터
	{
		pEffect->attrAmplify = (xtEffectAttr)ParsingParam( cParam );
	} else
	if( XSAME( cAttrName, 8 ) )	// 능력치
	{	
		CToken token;
		token.LoadStr( U82SZ( cParam ) );
		token.GetToken();
		pEffect->valtypeInvokeAbility = GetValType( token.m_Token[0] );
		if( pEffect->valtypeInvokeAbility == xNONE_VALTYPE )
		{	
			XALERT( "skill %s:unknown valtype.", pSkillDat->GetszIdentifier() );
			return FALSE;
		}
		// %#기호뒤에 숫자가 더 있을때만 읽는다.

		if( token.IsEof() == FALSE )
		{
			float ability = token.GetNumberF();
			if( pEffect->invokeAbilityMin.size() != 0 )
			{
				XALERT( "skill %s(%s):이미 능력치값이 존재합니다.",
					pSkillDat->GetszIdentifier(),
					U82SZ( cAttrName ) );
				return FALSE;
			}
			// "능력치"만 단독으로 쓰일때는 index 0을 사용한다.
			if( pEffect->valtypeInvokeAbility == xPERCENT )
				pEffect->invokeAbilityMin.Add( ability / 100.f );
			else
				pEffect->invokeAbilityMin.Add( ability );
		}

	} else
	if( XSAME( cAttrName, 125 ))	// 능력치테이블
	{
		_tstring strParam = U82SZ( cParam ); 
		_tstring strAttrName = U82SZ( cAttrName );
		ReadTableAry( strAttrName.c_str(), 
					pSkillDat->GetstrIdentifier().c_str(), 
					&pEffect->invokeAbilityMin, strParam.c_str(), pEffect->valtypeInvokeAbility );
		if( pEffect->invokeParameter == 0 )
		{
			XALERT( "skill %s(%s):발동파라메터가 없거나(해석하지 못했거나) 능력치테이블의 앞에 있지 않습니다.",
							pSkillDat->GetszIdentifier(),
							U82SZ( cAttrName ) );
		}
	} else
	if( XSAME( cAttrName, 101 ) )	// 상태발동
	{
		pEffect->invokeState = (int)ParsingParam( cParam );
	} else
	if( XSAME( cAttrName, 65 ) || XSAME( cAttrName, 28 ) )	// 발동반경/범위
	{	
		_tstring strParam = U82SZ( cParam );
		_tstring strAttrName = U82SZ( cAttrName );
		ReadTableAry( strAttrName.c_str(),
			pSkillDat->GetstrIdentifier().c_str(),
			&pEffect->aryInvokeSize, strParam.c_str(), xVAL );
	} else
	if( XSAME( cAttrName, 159 ) )	// 발동길이
	{
		pEffect->_invokeSize.w = (float)pAttr->DoubleValue();
	} else
	if( XSAME( cAttrName, 160 ) )	// 발동폭
	{
		pEffect->_invokeSize.h = (float)pAttr->DoubleValue();
	} else
	if( XSAME( cAttrName, 29 ) )	// 발동주기
	{	
		pEffect->secInvokeDOT = (float)pAttr->DoubleValue();
	} else
	if( XSAME( cAttrName, 32 ) )	// 적용대상수
	{	
		pEffect->invokeNumApply = pAttr->IntValue();
	} else
	if( XSAME( cAttrName, 162 )  )	// 발동자이펙트
	{	
		if( pEffect->m_invokerEff.m_strSpr.empty() == false )
			XLOGXN("%s: 중복입력. 기존값:%s", U82SZ(cAttrName), pEffect->m_invokerEff.m_strSpr.c_str() );
		pEffect->m_invokerEff.m_strSpr = U82SZ( cParam );
	} else
	if( XSAME( cAttrName, 163 ) )	// 발동자대상이펙트id
	{	
		pEffect->m_invokerEff.m_idAct = (int)pAttr->IntValue();
	} else
	if( XSAME( cAttrName, 258 ) )	// 발동자이펙트생성지점
	{
		pEffect->m_invokerEff.m_Point = (xtPoint) ParsingParam( cParam );
	} else
	if( XSAME( cAttrName, 33 ) )	// 발동사운드
	{	
		pEffect->idInvokeSound = (int)pAttr->IntValue();
	} else
	if( XSAME( cAttrName, 34 ) )	// 중복가능
	{
		pEffect->bDuplicate = (BOOL)ParsingParam( cParam );
	} else
	if( XSAME( cAttrName, 100 ) )	// 버프중첩
	{	
		pEffect->numOverlap = (int)pAttr->IntValue();
	} else
	if( XSAME( cAttrName, 175 ) )	// 대상생존
	{
		pEffect->liveTarget = (xtTargetLive) ParsingParam( cParam );
	} else
	if( XSAME( cAttrName, 129 ) )	// 소환
	{
		pEffect->strCreateObj = U82SZ( cParam );
	} else
	if( XSAME( cAttrName, 134 ) )	// 소환id
	{
		pEffect->idCreateObj = (ID)pAttr->IntValue();
	} else
	if( XSAME( cAttrName, 130 ) )	// 소환변수1
	{
		pEffect->createObjParam[0] = (float) pAttr->DoubleValue();
	} else
	if( XSAME( cAttrName, 130 ) )	// 소환변수1
	{
		pEffect->createObjParam[0] = (float) pAttr->DoubleValue();
	} else
	if( XSAME( cAttrName, 131 ) )	// 소환변수2
	{
		pEffect->createObjParam[1] = (float) pAttr->DoubleValue();
	} else
	if( XSAME( cAttrName, 132 ) )	// 소환변수3
	{
		pEffect->createObjParam[2] = (float) pAttr->DoubleValue();
	} else
	if( XSAME( cAttrName, 133 ) )	// 소환변수4
	{
		pEffect->createObjParam[1] = (float) pAttr->DoubleValue();
	} else
	if( XSAME( cAttrName, 44 ) )	// 사용
	{	
		pEffect->scriptUse = cParam;
	} else
	if( XSAME( cAttrName, 43 ) )	// 대상시전
	{	
		pEffect->scriptCast = cParam;
	} else
	if( XSAME( cAttrName, 39 ) )	// 발동시작
	{	
		pEffect->scriptInit = cParam;
	} else
	if( XSAME( cAttrName, 40 ) )	// 발동중
	{	
		pEffect->scriptProcess = cParam;
	} else
	if( XSAME( cAttrName, 41 ) )	// 발동끝
	{	
		pEffect->scriptUninit = cParam;
	} else
	if( XSAME( cAttrName, 42 ) )	// 도트
	{	
		pEffect->scriptDOT = cParam;
	} else
	if( XSAME( cAttrName, 171 ) )	// 면역여부
	{ 
		pEffect->bImmunity = (BOOL) ParsingParam( cParam );
	} else
	if( XSAME( cAttrName, 189 ) )	// 지속이펙트
	{	
		pEffect->m_PersistEff.m_strSpr = U82SZ( cParam );
	} else
	if( XSAME( cAttrName, 191 ) )	// 지속이펙트생성지점
	{
		pEffect->m_PersistEff.m_Point = (xtPoint) ParsingParam( cParam );
	} else
	if( XSAME( cAttrName, 190 ) )	// 지속이펙트id
	{	
		pEffect->m_PersistEff.m_idAct = (int)pAttr->IntValue();
	} else
	if( XSAME( cAttrName, 207 ) )	// 파라메터1
	{	
		pEffect->dwParam[ 0 ] = ParsingConstantAndNumber( cParam );
	} else
	if( XSAME( cAttrName, 208 ) )	// 파라메터2
	{	
		pEffect->dwParam[1] = ParsingConstantAndNumber( cParam );
	} else
	if( XSAME( cAttrName, 209 ) )	// 파라메터3
	{	
		pEffect->dwParam[2] = ParsingConstantAndNumber( cParam );
	} else
	if( XSAME( cAttrName, 210 ) )	// 파라메터4
	{	
		pEffect->dwParam[3] = ParsingConstantAndNumber( cParam );
	} else
	if( XE::IsSame(cAttrName, "debug") ) {
		int a = pAttr->IntValue();
		pEffect->m_Debug = a;
	} else
	if( CustomParsingEffect( pAttr, cAttrName, cParam, pSkillDat, pEffect ) == FALSE )
	{
		XLOGXN( "unknown variable name: %s", U82SZ( cAttrName ) );
		return FALSE;
	}
	return TRUE;
}