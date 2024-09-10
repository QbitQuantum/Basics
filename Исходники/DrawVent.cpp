void DrawCmd::DrawWindLibrary( void )
{
	AcDbObjectId objId = ArxUtilHelper::SelectObject( _T( "请选择一条巷道:" ) );
	if( objId.isNull() ) return;
	if( !ArxUtilHelper::IsEqualType( _T( "LinkedGE" ), objId ) ) return;


	AcGePoint3d pt,insertPt;

	double angle;

	if( !ArxUtilHelper::PromptPt( _T( "\n请指定风库的插入点坐标:" ), pt ) ) return;

	if( !GetClosePtAndAngle( objId, pt, angle ) ) return;

	AcGeVector3d v = AcGeVector3d(AcGeVector3d::kXAxis);
	v.rotateBy(angle - PI/2,AcGeVector3d::kZAxis);
	v.normalize();

	insertPt = pt + v * 60;

	WindLibrary* pWindLib = new WindLibrary( insertPt, angle ); 	
	if( pWindLib == 0 ) return;


	pWindLib->setRelatedGE( objId ); // 关联巷道

	// 初始化并提交到数据库
	if( !ArxUtilHelper::PostToModelSpace( pWindLib ) ) delete pWindLib;

}