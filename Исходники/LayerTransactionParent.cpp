bool
LayerTransactionParent::RecvUpdate(const InfallibleTArray<Edit>& cset,
                                   const uint64_t& aTransactionId,
                                   const TargetConfig& targetConfig,
                                   const bool& isFirstPaint,
                                   const bool& scheduleComposite,
                                   const uint32_t& paintSequenceNumber,
                                   const bool& isRepeatTransaction,
                                   InfallibleTArray<EditReply>* reply)
{
  profiler_tracing("Paint", "Composite", TRACING_INTERVAL_START);
  PROFILER_LABEL("LayerTransactionParent", "RecvUpdate",
    js::ProfileEntry::Category::GRAPHICS);

#ifdef COMPOSITOR_PERFORMANCE_WARNING
  TimeStamp updateStart = TimeStamp::Now();
#endif

  MOZ_LAYERS_LOG(("[ParentSide] received txn with %d edits", cset.Length()));

  if (mDestroyed || !layer_manager() || layer_manager()->IsDestroyed()) {
    return true;
  }

  if (mLayerManager && mLayerManager->GetCompositor() &&
      !targetConfig.naturalBounds().IsEmpty()) {
    mLayerManager->GetCompositor()->SetScreenRotation(targetConfig.rotation());
  }

  EditReplyVector replyv;

  {
    AutoResolveRefLayers resolve(mShadowLayersManager->GetCompositionManager(this));
    layer_manager()->BeginTransaction();
  }

  for (EditArray::index_type i = 0; i < cset.Length(); ++i) {
    const Edit& edit = cset[i];

    switch (edit.type()) {
    // Create* ops
    case Edit::TOpCreateThebesLayer: {
      MOZ_LAYERS_LOG(("[ParentSide] CreateThebesLayer"));

      nsRefPtr<ThebesLayerComposite> layer =
        layer_manager()->CreateThebesLayerComposite();
      AsLayerComposite(edit.get_OpCreateThebesLayer())->Bind(layer);
      break;
    }
    case Edit::TOpCreateContainerLayer: {
      MOZ_LAYERS_LOG(("[ParentSide] CreateContainerLayer"));

      nsRefPtr<ContainerLayer> layer = layer_manager()->CreateContainerLayerComposite();
      AsLayerComposite(edit.get_OpCreateContainerLayer())->Bind(layer);
      break;
    }
    case Edit::TOpCreateImageLayer: {
      MOZ_LAYERS_LOG(("[ParentSide] CreateImageLayer"));

      nsRefPtr<ImageLayerComposite> layer =
        layer_manager()->CreateImageLayerComposite();
      AsLayerComposite(edit.get_OpCreateImageLayer())->Bind(layer);
      break;
    }
    case Edit::TOpCreateColorLayer: {
      MOZ_LAYERS_LOG(("[ParentSide] CreateColorLayer"));

      nsRefPtr<ColorLayerComposite> layer = layer_manager()->CreateColorLayerComposite();
      AsLayerComposite(edit.get_OpCreateColorLayer())->Bind(layer);
      break;
    }
    case Edit::TOpCreateCanvasLayer: {
      MOZ_LAYERS_LOG(("[ParentSide] CreateCanvasLayer"));

      nsRefPtr<CanvasLayerComposite> layer =
        layer_manager()->CreateCanvasLayerComposite();
      AsLayerComposite(edit.get_OpCreateCanvasLayer())->Bind(layer);
      break;
    }
    case Edit::TOpCreateRefLayer: {
      MOZ_LAYERS_LOG(("[ParentSide] CreateRefLayer"));

      nsRefPtr<RefLayerComposite> layer =
        layer_manager()->CreateRefLayerComposite();
      AsLayerComposite(edit.get_OpCreateRefLayer())->Bind(layer);
      break;
    }

    // Attributes
    case Edit::TOpSetLayerAttributes: {
      MOZ_LAYERS_LOG(("[ParentSide] SetLayerAttributes"));

      const OpSetLayerAttributes& osla = edit.get_OpSetLayerAttributes();
      ShadowLayerParent* layerParent = AsLayerComposite(osla);
      Layer* layer = layerParent->AsLayer();
      if (!layer) {
        return false;
      }
      const LayerAttributes& attrs = osla.attrs();

      const CommonLayerAttributes& common = attrs.common();
      layer->SetVisibleRegion(common.visibleRegion());
      layer->SetEventRegions(common.eventRegions());
      layer->SetContentFlags(common.contentFlags());
      layer->SetOpacity(common.opacity());
      layer->SetClipRect(common.useClipRect() ? &common.clipRect() : nullptr);
      layer->SetBaseTransform(common.transform().value());
      layer->SetPostScale(common.postXScale(), common.postYScale());
      layer->SetIsFixedPosition(common.isFixedPosition());
      layer->SetFixedPositionAnchor(common.fixedPositionAnchor());
      layer->SetFixedPositionMargins(common.fixedPositionMargin());
      if (common.isStickyPosition()) {
        layer->SetStickyPositionData(common.stickyScrollContainerId(),
                                     common.stickyScrollRangeOuter(),
                                     common.stickyScrollRangeInner());
      }
      layer->SetScrollbarData(common.scrollbarTargetContainerId(),
        static_cast<Layer::ScrollDirection>(common.scrollbarDirection()));
      layer->SetMixBlendMode((gfx::CompositionOp)common.mixBlendMode());
      layer->SetForceIsolatedGroup(common.forceIsolatedGroup());
      if (PLayerParent* maskLayer = common.maskLayerParent()) {
        layer->SetMaskLayer(cast(maskLayer)->AsLayer());
      } else {
        layer->SetMaskLayer(nullptr);
      }
      layer->SetAnimations(common.animations());
      layer->SetInvalidRegion(common.invalidRegion());

      typedef SpecificLayerAttributes Specific;
      const SpecificLayerAttributes& specific = attrs.specific();
      switch (specific.type()) {
      case Specific::Tnull_t:
        break;

      case Specific::TThebesLayerAttributes: {
        MOZ_LAYERS_LOG(("[ParentSide]   thebes layer"));

        ThebesLayerComposite* thebesLayer = layerParent->AsThebesLayerComposite();
        if (!thebesLayer) {
          return false;
        }
        const ThebesLayerAttributes& attrs =
          specific.get_ThebesLayerAttributes();

        thebesLayer->SetValidRegion(attrs.validRegion());

        break;
      }
      case Specific::TContainerLayerAttributes: {
        MOZ_LAYERS_LOG(("[ParentSide]   container layer"));

        ContainerLayerComposite* containerLayer = layerParent->AsContainerLayerComposite();
        if (!containerLayer) {
          return false;
        }
        const ContainerLayerAttributes& attrs =
          specific.get_ContainerLayerAttributes();
        containerLayer->SetFrameMetrics(attrs.metrics());
        containerLayer->SetScrollHandoffParentId(attrs.scrollParentId());
        containerLayer->SetPreScale(attrs.preXScale(), attrs.preYScale());
        containerLayer->SetInheritedScale(attrs.inheritedXScale(), attrs.inheritedYScale());
        containerLayer->SetBackgroundColor(attrs.backgroundColor().value());
        containerLayer->SetContentDescription(attrs.contentDescription());
        break;
      }
      case Specific::TColorLayerAttributes: {
        MOZ_LAYERS_LOG(("[ParentSide]   color layer"));

        ColorLayerComposite* colorLayer = layerParent->AsColorLayerComposite();
        if (!colorLayer) {
          return false;
        }
        colorLayer->SetColor(specific.get_ColorLayerAttributes().color().value());
        colorLayer->SetBounds(specific.get_ColorLayerAttributes().bounds());
        break;
      }
      case Specific::TCanvasLayerAttributes: {
        MOZ_LAYERS_LOG(("[ParentSide]   canvas layer"));

        CanvasLayerComposite* canvasLayer = layerParent->AsCanvasLayerComposite();
        if (!canvasLayer) {
          return false;
        }
        canvasLayer->SetFilter(specific.get_CanvasLayerAttributes().filter());
        canvasLayer->SetBounds(specific.get_CanvasLayerAttributes().bounds());
        break;
      }
      case Specific::TRefLayerAttributes: {
        MOZ_LAYERS_LOG(("[ParentSide]   ref layer"));

        RefLayerComposite* refLayer = layerParent->AsRefLayerComposite();
        if (!refLayer) {
          return false;
        }
        refLayer->SetReferentId(specific.get_RefLayerAttributes().id());
        break;
      }
      case Specific::TImageLayerAttributes: {
        MOZ_LAYERS_LOG(("[ParentSide]   image layer"));

        ImageLayerComposite* imageLayer = layerParent->AsImageLayerComposite();
        if (!imageLayer) {
          return false;
        }
        const ImageLayerAttributes& attrs = specific.get_ImageLayerAttributes();
        imageLayer->SetFilter(attrs.filter());
        imageLayer->SetScaleToSize(attrs.scaleToSize(), attrs.scaleMode());
        break;
      }
      default:
        NS_RUNTIMEABORT("not reached");
      }
      break;
    }
    case Edit::TOpSetDiagnosticTypes: {
      mLayerManager->GetCompositor()->SetDiagnosticTypes(
        edit.get_OpSetDiagnosticTypes().diagnostics());
      break;
    }
    // Tree ops
    case Edit::TOpSetRoot: {
      MOZ_LAYERS_LOG(("[ParentSide] SetRoot"));

      Layer* newRoot = AsLayerComposite(edit.get_OpSetRoot())->AsLayer();
      if (!newRoot) {
        return false;
      }
      if (newRoot->GetParent()) {
        // newRoot is not a root!
        return false;
      }
      mRoot = newRoot;
      break;
    }
    case Edit::TOpInsertAfter: {
      MOZ_LAYERS_LOG(("[ParentSide] InsertAfter"));

      const OpInsertAfter& oia = edit.get_OpInsertAfter();
      Layer* child = ShadowChild(oia)->AsLayer();
      if (!child) {
        return false;
      }
      ContainerLayerComposite* container = ShadowContainer(oia)->AsContainerLayerComposite();
      if (!container ||
          !container->InsertAfter(child, ShadowAfter(oia)->AsLayer()))
      {
        return false;
      }
      break;
    }
    case Edit::TOpPrependChild: {
      MOZ_LAYERS_LOG(("[ParentSide] PrependChild"));

      const OpPrependChild& oac = edit.get_OpPrependChild();
      Layer* child = ShadowChild(oac)->AsLayer();
      if (!child) {
        return false;
      }
      ContainerLayerComposite* container = ShadowContainer(oac)->AsContainerLayerComposite();
      if (!container ||
          !container->InsertAfter(child, nullptr))
      {
        return false;
      }
      break;
    }
    case Edit::TOpRemoveChild: {
      MOZ_LAYERS_LOG(("[ParentSide] RemoveChild"));

      const OpRemoveChild& orc = edit.get_OpRemoveChild();
      Layer* childLayer = ShadowChild(orc)->AsLayer();
      if (!childLayer) {
        return false;
      }
      ContainerLayerComposite* container = ShadowContainer(orc)->AsContainerLayerComposite();
      if (!container ||
          !container->RemoveChild(childLayer))
      {
        return false;
      }
      break;
    }
    case Edit::TOpRepositionChild: {
      MOZ_LAYERS_LOG(("[ParentSide] RepositionChild"));

      const OpRepositionChild& orc = edit.get_OpRepositionChild();
      Layer* child = ShadowChild(orc)->AsLayer();
      if (!child) {
        return false;
      }
      ContainerLayerComposite* container = ShadowContainer(orc)->AsContainerLayerComposite();
      if (!container ||
          !container->RepositionChild(child, ShadowAfter(orc)->AsLayer()))
      {
        return false;
      }
      break;
    }
    case Edit::TOpRaiseToTopChild: {
      MOZ_LAYERS_LOG(("[ParentSide] RaiseToTopChild"));

      const OpRaiseToTopChild& rtc = edit.get_OpRaiseToTopChild();
      Layer* child = ShadowChild(rtc)->AsLayer();
      if (!child) {
        return false;
      }
      ContainerLayerComposite* container = ShadowContainer(rtc)->AsContainerLayerComposite();
      if (!container ||
          !container->RepositionChild(child, nullptr))
      {
        return false;
      }
      break;
    }
    case Edit::TCompositableOperation: {
      if (!ReceiveCompositableUpdate(edit.get_CompositableOperation(),
                                replyv)) {
        return false;
      }
      break;
    }
    case Edit::TOpAttachCompositable: {
      const OpAttachCompositable& op = edit.get_OpAttachCompositable();
      CompositableHost* host = CompositableHost::FromIPDLActor(op.compositableParent());
      if (!Attach(cast(op.layerParent()), host, false)) {
        return false;
      }
      host->SetCompositorID(mLayerManager->GetCompositor()->GetCompositorID());
      break;
    }
    case Edit::TOpAttachAsyncCompositable: {
      const OpAttachAsyncCompositable& op = edit.get_OpAttachAsyncCompositable();
      PCompositableParent* compositableParent = CompositableMap::Get(op.containerID());
      if (!compositableParent) {
        NS_ERROR("CompositableParent not found in the map");
        return false;
      }
      CompositableHost* host = CompositableHost::FromIPDLActor(compositableParent);
      if (!Attach(cast(op.layerParent()), host, true)) {
        return false;
      }

      host->SetCompositorID(mLayerManager->GetCompositor()->GetCompositorID());
      break;
    }
    default:
      NS_RUNTIMEABORT("not reached");
    }
  }

  mShadowLayersManager->ShadowLayersUpdated(this, aTransactionId, targetConfig,
      isFirstPaint, scheduleComposite, paintSequenceNumber, isRepeatTransaction);

  {
    AutoResolveRefLayers resolve(mShadowLayersManager->GetCompositionManager(this));
    layer_manager()->EndTransaction(nullptr, nullptr, LayerManager::END_NO_IMMEDIATE_REDRAW);
  }

  if (reply) {
    reply->SetCapacity(replyv.size());
    if (replyv.size() > 0) {
      reply->AppendElements(&replyv.front(), replyv.size());
    }
  }

  if (!IsSameProcess()) {
    // Ensure that any pending operations involving back and front
    // buffers have completed, so that neither process stomps on the
    // other's buffer contents.
    LayerManagerComposite::PlatformSyncBeforeReplyUpdate();
  }

#ifdef COMPOSITOR_PERFORMANCE_WARNING
  int compositeTime = (int)(mozilla::TimeStamp::Now() - updateStart).ToMilliseconds();
  if (compositeTime > 15) {
    printf_stderr("Compositor: Layers update took %i ms (blocking gecko).\n", compositeTime);
  }
#endif

  return true;
}