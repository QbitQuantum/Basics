//---------------------------------------------------------
bool Cut_Shapes(CSG_Rect Extent, int Method, CSG_Shapes *pShapes, CSG_Shapes *pCut)
{
	if( pCut && pShapes && pShapes->is_Valid() && Extent.Intersects(pShapes->Get_Extent()) )
	{
		pCut->Create(
			pShapes->Get_Type(),
			CSG_String::Format(SG_T("%s [%s]"), pShapes->Get_Name(), _TL("Cut")),
			pShapes
		);

		for(int iShape=0; iShape<pShapes->Get_Count() && SG_UI_Process_Set_Progress(iShape, pShapes->Get_Count()); iShape++)
		{
			bool		bAdd;
			CSG_Shape	*pShape	= pShapes->Get_Shape(iShape);

			if( Method == 2 )	// center
			{
				bAdd	= pShapes->Get_Type() == SHAPE_TYPE_Polygon
						? Extent.Contains(((CSG_Shape_Polygon *)pShape)->Get_Centroid())
						: Extent.Contains(pShape->Get_Extent().Get_Center());
			}
			else				// completely contained, intersects
			{
				switch( pShape->Intersects(Extent) )
				{
				case INTERSECTION_Identical:
				case INTERSECTION_Contained:
					bAdd	= true;
					break;

				case INTERSECTION_Overlaps:
				case INTERSECTION_Contains:
					bAdd	= Method == 1;
					break;

				default:
					bAdd	= false;
					break;
				}
			}

			if( bAdd )
			{
				pCut->Add_Shape(pShape);
			}
		}

		return( pCut->Get_Count() > 0 );
	}

	return( false );
}