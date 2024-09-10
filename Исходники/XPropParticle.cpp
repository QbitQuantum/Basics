/**
 @brief angle,speed,alpha등 각종 파라메터의 함수와 범위값을 얻는다.
 @param nodeRoot particle노드
*/
int XPropParticle::LoadFunc( XEXmlNode& nodeRoot, const char *cKey, xParticle::xFunc *pOut )
{
	auto node = nodeRoot.FindNode( cKey );
	int ret = 0;
	if( node.IsEmpty() )
		return ret;
	pOut->funcType = xFN_FIXED;		// 디폴트 함수.
	std::string strParam = node.GetString( "func" );
	if( strParam == "random" )
		pOut->funcType = xFN_RANDOM;
	else if( strParam == "linear" )
		pOut->funcType = xFN_LINEAR;
	else if( strParam == "sin" )
		pOut->funcType = xFN_SIN;
	float secCycle = node.GetFloat( "cycle" );
	if( secCycle )
		pOut->secCycle = secCycle;
	// val의 범위값을 얻는다.
	_tstring strVal = node.GetTString( "val" );
	float v1 = 0, v2 = 0;
	CToken token;
	if( token.LoadStr( strVal.c_str() ) ) {
		v1 = token.GetNumberF();
		++ret;
		if( !token.IsEof() ) {
			token.GetToken();	// ,
			if( !token.IsEof() ) {
				v2 = token.GetNumberF();
				++ret;
			}
		}
	}
	if( pOut ) {
		pOut->range.Set( v1, v2 );
	}
	return ret;
}