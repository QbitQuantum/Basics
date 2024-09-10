void UEditorEngine::polySplitOverlappingEdges( TArray<FPoly>* InPolyList, TArray<FPoly>* InResult )
{
	InResult->Empty();

	for( int32 poly = 0 ; poly < InPolyList->Num() ; poly++ )
	{
		FPoly* SrcPoly = &(*InPolyList)[poly];
		FPoly NewPoly = *SrcPoly;

		for( int32 edge = 0 ; edge < SrcPoly->Vertices.Num() ; edge++ )
		{
			FEdge SrcEdge = FEdge( SrcPoly->Vertices[edge], SrcPoly->Vertices[ edge+1 < SrcPoly->Vertices.Num() ? edge+1 : 0 ] );
			FPlane SrcEdgePlane( SrcEdge.Vertex[0], SrcEdge.Vertex[1], SrcEdge.Vertex[0] + (SrcPoly->Normal * 16) );

			for( int32 poly2 = 0 ; poly2 < InPolyList->Num() ; poly2++ )
			{
				FPoly* CmpPoly = &(*InPolyList)[poly2];

				// We can't compare to ourselves.
				if( CmpPoly == SrcPoly )
					continue;

				for( int32 edge2 = 0 ; edge2 < CmpPoly->Vertices.Num() ; edge2++ )
				{
					FEdge CmpEdge = FEdge( CmpPoly->Vertices[edge2], CmpPoly->Vertices[ edge2+1 < CmpPoly->Vertices.Num() ? edge2+1 : 0 ] );

					// If both vertices on this edge lie on the same plane as the original edge, create
					// a sphere around the original 2 vertices.  If either of this edges vertices are inside of
					// that sphere, we need to split the original edge by adding a vertex to it's poly.
					if( FMath::Abs( FVector::PointPlaneDist( CmpEdge.Vertex[0], SrcEdge.Vertex[0], SrcEdgePlane ) ) < THRESH_POINT_ON_PLANE
							&& FMath::Abs( FVector::PointPlaneDist( CmpEdge.Vertex[1], SrcEdge.Vertex[0], SrcEdgePlane ) ) < THRESH_POINT_ON_PLANE )
					{
						//
						// Check THIS edge against the SOURCE edge
						//

						FVector Dir = SrcEdge.Vertex[1] - SrcEdge.Vertex[0];
						Dir.Normalize();
						float Dist = FVector::Dist( SrcEdge.Vertex[1], SrcEdge.Vertex[0] );
						FVector Origin = SrcEdge.Vertex[0] + (Dir * (Dist / 2.0f));
						float Radius = Dist / 2.0f;

						for( int32 vtx = 0 ; vtx < 2 ; vtx++ )
							if( FVector::Dist( Origin, CmpEdge.Vertex[vtx] ) && FVector::Dist( Origin, CmpEdge.Vertex[vtx] ) < Radius )
								NewPoly.InsertVertex( edge2+1, CmpEdge.Vertex[vtx] );
					}
				}
			}
		}

		new(*InResult)FPoly( NewPoly );
	}

}