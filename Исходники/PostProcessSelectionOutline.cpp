void FRCPassPostProcessSelectionOutlineColor::Process(FRenderingCompositePassContext& Context)
{
	SCOPED_DRAW_EVENT(Context.RHICmdList, PostProcessSelectionOutlineBuffer, DEC_SCENE_ITEMS);

	const FPooledRenderTargetDesc* SceneColorInputDesc = GetInputDesc(ePId_Input0);

	if(!SceneColorInputDesc)
	{
		// input is not hooked up correctly
		return;
	}

	const FViewInfo& View = Context.View;
	FIntRect ViewRect = View.ViewRect;
	FIntPoint SrcSize = SceneColorInputDesc->Extent;

	// Get the output render target
	const FSceneRenderTargetItem& DestRenderTarget = PassOutputs[0].RequestSurface(Context);
	
	// Set the render target/viewport.
	SetRenderTarget(Context.RHICmdList, FTextureRHIParamRef(), DestRenderTarget.TargetableTexture);
	// This is a reversed Z depth surface, so 0.0f is the far plane.
	Context.RHICmdList.Clear(false, FLinearColor(0, 0, 0, 0), true, 0.0f, true, 0, FIntRect());
	Context.SetViewportAndCallRHI(ViewRect);

	if (View.Family->EngineShowFlags.Selection)
	{
		const bool bUseGetMeshElements = ShouldUseGetDynamicMeshElements();

		if (bUseGetMeshElements)
		{
			FHitProxyDrawingPolicyFactory::ContextType FactoryContext;

			//@todo - use memstack
			TMap<FName, int32> ActorNameToStencilIndex;
			ActorNameToStencilIndex.Add(NAME_BSP, 1);

			Context.RHICmdList.SetRasterizerState(TStaticRasterizerState<>::GetRHI());
			Context.RHICmdList.SetBlendState(TStaticBlendStateWriteMask<CW_NONE, CW_NONE, CW_NONE, CW_NONE>::GetRHI());

			for (int32 MeshBatchIndex = 0; MeshBatchIndex < View.DynamicMeshElements.Num(); MeshBatchIndex++)
			{
				const FMeshBatchAndRelevance& MeshBatchAndRelevance = View.DynamicMeshElements[MeshBatchIndex];
				const FPrimitiveSceneProxy* PrimitiveSceneProxy = MeshBatchAndRelevance.PrimitiveSceneProxy;

				if (PrimitiveSceneProxy->IsSelected() && MeshBatchAndRelevance.Mesh->bUseSelectionOutline)
				{
					const int32* AssignedStencilIndexPtr = ActorNameToStencilIndex.Find(PrimitiveSceneProxy->GetOwnerName());

					if (!AssignedStencilIndexPtr)
					{
						AssignedStencilIndexPtr = &ActorNameToStencilIndex.Add(PrimitiveSceneProxy->GetOwnerName(), ActorNameToStencilIndex.Num() + 1);
					}

					// This is a reversed Z depth surface, using CF_GreaterEqual.
					// Note that the stencil value will overflow with enough selected objects
					Context.RHICmdList.SetDepthStencilState(TStaticDepthStencilState<true, CF_GreaterEqual, true, CF_Always, SO_Keep, SO_Keep, SO_Replace>::GetRHI(), *AssignedStencilIndexPtr);

					const FMeshBatch& MeshBatch = *MeshBatchAndRelevance.Mesh;
					FHitProxyDrawingPolicyFactory::DrawDynamicMesh(Context.RHICmdList, View, FactoryContext, MeshBatch, false, true, MeshBatchAndRelevance.PrimitiveSceneProxy, MeshBatch.BatchHitProxyId);
				}
			}
		}
		else if (View.VisibleDynamicPrimitives.Num() > 0)
		{
			TDynamicPrimitiveDrawer<FHitProxyDrawingPolicyFactory> Drawer(Context.RHICmdList, &View, FHitProxyDrawingPolicyFactory::ContextType(), true, false, false, true);
			TMultiMap<FName, const FPrimitiveSceneInfo*> PrimitivesByActor;

			for (int32 PrimitiveIndex = 0; PrimitiveIndex < View.VisibleDynamicPrimitives.Num();PrimitiveIndex++)
			{
				const FPrimitiveSceneInfo* PrimitiveSceneInfo = View.VisibleDynamicPrimitives[PrimitiveIndex];

				// Only draw the primitive if relevant
				if(PrimitiveSceneInfo->Proxy->IsSelected())
				{
					PrimitivesByActor.Add(PrimitiveSceneInfo->Proxy->GetOwnerName(), PrimitiveSceneInfo);
				}
			}

			if (PrimitivesByActor.Num())
			{
				// 0 means no object, 1 means BSP so we start with 2
				uint32 StencilValue = 2;

				Context.RHICmdList.SetRasterizerState(TStaticRasterizerState<>::GetRHI());
				Context.RHICmdList.SetBlendState(TStaticBlendStateWriteMask<CW_NONE, CW_NONE, CW_NONE, CW_NONE>::GetRHI());

				// Sort by actor
				TArray<FName> Actors;
				PrimitivesByActor.GetKeys(Actors);
				for( TArray<FName>::TConstIterator ActorIt(Actors); ActorIt; ++ActorIt )
				{
					bool bBSP = *ActorIt == NAME_BSP;
					if (bBSP)
					{
						// This is a reversed Z depth surface, using CF_GreaterEqual.
						Context.RHICmdList.SetDepthStencilState(TStaticDepthStencilState<true, CF_GreaterEqual, true, CF_Always, SO_Keep, SO_Keep, SO_Replace>::GetRHI(), 1);
					}
					else
					{
						// This is a reversed Z depth surface, using CF_GreaterEqual.
						Context.RHICmdList.SetDepthStencilState(TStaticDepthStencilState<true, CF_GreaterEqual, true, CF_Always, SO_Keep, SO_Keep, SO_Replace>::GetRHI(), StencilValue);

						// we want to use 1..255 for all objects, not correct silhouettes after that is acceptable
						StencilValue = (StencilValue == 255) ? 2 : (StencilValue + 1);
					}

					TArray<const FPrimitiveSceneInfo*> Primitives;
					PrimitivesByActor.MultiFind(*ActorIt, Primitives);

					for( TArray<const FPrimitiveSceneInfo*>::TConstIterator PrimIt(Primitives); PrimIt; ++PrimIt )
					{
						const FPrimitiveSceneInfo* PrimitiveSceneInfo = *PrimIt;
						// Render the object to the stencil/depth buffer
						Drawer.SetPrimitive(PrimitiveSceneInfo->Proxy);
						PrimitiveSceneInfo->Proxy->DrawDynamicElements(&Drawer, &View);
					}
				}
			}
		}

		// to get an outline around the objects if it's partly outside of the screen
		{
			FIntRect InnerRect = ViewRect;

			// 1 as we have an outline that is that thick
			InnerRect.InflateRect(-1);

			// We could use Clear with InnerRect but this is just an optimization - on some hardware it might do a full clear (and we cannot disable yet)
			//			RHICmdList.Clear(false, FLinearColor(0, 0, 0, 0), true, 0.0f, true, 0, InnerRect);
			// so we to 4 clears - one for each border.

			// top
			Context.RHICmdList.SetScissorRect(true, ViewRect.Min.X, ViewRect.Min.Y, ViewRect.Max.X, InnerRect.Min.Y);
			Context.RHICmdList.Clear(false, FLinearColor(0, 0, 0, 0), true, 0.0f, true, 0, FIntRect());
			// bottom
			Context.RHICmdList.SetScissorRect(true, ViewRect.Min.X, InnerRect.Max.Y, ViewRect.Max.X, ViewRect.Max.Y);
			Context.RHICmdList.Clear(false, FLinearColor(0, 0, 0, 0), true, 0.0f, true, 0, FIntRect());
			// left
			Context.RHICmdList.SetScissorRect(true, ViewRect.Min.X, ViewRect.Min.Y, InnerRect.Min.X, ViewRect.Max.Y);
			Context.RHICmdList.Clear(false, FLinearColor(0, 0, 0, 0), true, 0.0f, true, 0, FIntRect());
			// right
			Context.RHICmdList.SetScissorRect(true, InnerRect.Max.X, ViewRect.Min.Y, ViewRect.Max.X, ViewRect.Max.Y);
			Context.RHICmdList.Clear(false, FLinearColor(0, 0, 0, 0), true, 0.0f, true, 0, FIntRect());

			Context.RHICmdList.SetScissorRect(false, 0, 0, 0, 0);
		}
	}
	
	// Resolve to the output
	Context.RHICmdList.CopyToResolveTarget(DestRenderTarget.TargetableTexture, DestRenderTarget.ShaderResourceTexture, false, FResolveParams());
}