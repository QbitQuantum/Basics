TArray<FArrangedWidget> FHittestGrid::GetBubblePath( FVector2D DesktopSpaceCoordinate, bool bIgnoreEnabledStatus )
{
	if (WidgetsCachedThisFrame->Num() > 0 && Cells.Num() > 0)
	{
		const FVector2D CursorPositionInGrid = DesktopSpaceCoordinate - GridOrigin;
		const FIntPoint CellCoordinate = FIntPoint(
			FMath::Min( FMath::Max(FMath::FloorToInt(CursorPositionInGrid.X / CellSize.X), 0), NumCells.X-1),
			FMath::Min( FMath::Max(FMath::FloorToInt(CursorPositionInGrid.Y / CellSize.Y), 0), NumCells.Y-1 ) );
		
		static FVector2D LastCoordinate = FVector2D::ZeroVector;
		if ( LastCoordinate != CursorPositionInGrid )
		{
			LastCoordinate = CursorPositionInGrid;
		}

		checkf( (CellCoordinate.Y*NumCells.X + CellCoordinate.X) < Cells.Num(), TEXT("Index out of range, CellCoordinate is: %d %d CursorPosition is: %f %f"), CellCoordinate.X, CellCoordinate.Y, CursorPositionInGrid.X, CursorPositionInGrid.Y );

		const TArray<int32>& IndexesInCell = CellAt( CellCoordinate.X, CellCoordinate.Y ).CachedWidgetIndexes;
		int32 HitWidgetIndex = INDEX_NONE;
	
		// Consider front-most widgets first for hittesting.
		for ( int32 i = IndexesInCell.Num()-1; i>=0 && HitWidgetIndex==INDEX_NONE; --i )
		{
			check( IndexesInCell[i] < WidgetsCachedThisFrame->Num() ); 

			const FCachedWidget& TestCandidate = (*WidgetsCachedThisFrame)[IndexesInCell[i]];

			// Compute the render space clipping rect (FGeometry exposes a layout space clipping rect).
			FSlateRotatedRect DesktopOrientedClipRect = 
				TransformRect(
					Concatenate(
						Inverse(TestCandidate.CachedGeometry.GetAccumulatedLayoutTransform()), 
						TestCandidate.CachedGeometry.GetAccumulatedRenderTransform()
					), 
					FSlateRotatedRect(TestCandidate.CachedGeometry.GetClippingRect().IntersectionWith(TestCandidate.ClippingRect))
				);

			if (DesktopOrientedClipRect.IsUnderLocation(DesktopSpaceCoordinate) && TestCandidate.WidgetPtr.IsValid())
			{
				HitWidgetIndex = IndexesInCell[i];
			}
		}

		if (HitWidgetIndex != INDEX_NONE)
		{
			TArray<FArrangedWidget> BubblePath;
			int32 CurWidgetIndex=HitWidgetIndex;
			bool bPathUninterrupted = false;
			do
			{
				check( CurWidgetIndex < WidgetsCachedThisFrame->Num() );
				const FCachedWidget& CurCachedWidget = (*WidgetsCachedThisFrame)[CurWidgetIndex];
				const TSharedPtr<SWidget> CachedWidgetPtr = CurCachedWidget.WidgetPtr.Pin();
				
				bPathUninterrupted = CachedWidgetPtr.IsValid();
				if (bPathUninterrupted)
				{
					BubblePath.Insert(FArrangedWidget(CachedWidgetPtr.ToSharedRef(), CurCachedWidget.CachedGeometry), 0);
					CurWidgetIndex = CurCachedWidget.ParentIndex;
				}
			}
			while (CurWidgetIndex != INDEX_NONE && bPathUninterrupted);
			
			if (!bPathUninterrupted)
			{
				// A widget in the path to the root has been removed, so anything
				// we thought we had hittest is no longer actually there.
				// Pretend we didn't hit anything.
				BubblePath = TArray<FArrangedWidget>();
			}

			// Disabling a widget disables all of its logical children
			// This effect is achieved by truncating the path to the
			// root-most enabled widget.
			if ( !bIgnoreEnabledStatus )
			{
				const int32 DisabledWidgetIndex = BubblePath.IndexOfByPredicate( []( const FArrangedWidget& SomeWidget ){ return !SomeWidget.Widget->IsEnabled( ); } );
				if (DisabledWidgetIndex != INDEX_NONE)
				{
					BubblePath.RemoveAt( DisabledWidgetIndex, BubblePath.Num() - DisabledWidgetIndex );
				}
			}
			
			return BubblePath;
		}
		else
		{
			return TArray<FArrangedWidget>();
		}
	}
	else
	{
		return TArray<FArrangedWidget>();
	}
}