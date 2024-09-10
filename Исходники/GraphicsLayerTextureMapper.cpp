void GraphicsLayerTextureMapper::commitLayerChanges()
{
    if (m_changeMask == NoChanges)
        return;

    if (m_changeMask & ChildrenChange)
        m_layer.setChildren(children());

    if (m_changeMask & MaskLayerChange)
        m_layer.setMaskLayer(&downcast<GraphicsLayerTextureMapper>(maskLayer())->layer());

    if (m_changeMask & ReplicaLayerChange)
        m_layer.setReplicaLayer(&downcast<GraphicsLayerTextureMapper>(replicaLayer())->layer());

    if (m_changeMask & PositionChange)
        m_layer.setPosition(position());

    if (m_changeMask & AnchorPointChange)
        m_layer.setAnchorPoint(anchorPoint());

    if (m_changeMask & SizeChange)
        m_layer.setSize(size());

    if (m_changeMask & TransformChange)
        m_layer.setTransform(transform());

    if (m_changeMask & ChildrenTransformChange)
        m_layer.setChildrenTransform(childrenTransform());

    if (m_changeMask & Preserves3DChange)
        m_layer.setPreserves3D(preserves3D());

    if (m_changeMask & ContentsRectChange)
        m_layer.setContentsRect(contentsRect());

    if (m_changeMask & MasksToBoundsChange)
        m_layer.setMasksToBounds(masksToBounds());

    if (m_changeMask & DrawsContentChange)
        m_layer.setDrawsContent(drawsContent());

    if (m_changeMask & ContentsVisibleChange)
        m_layer.setContentsVisible(contentsAreVisible());

    if (m_changeMask & ContentsOpaqueChange)
        m_layer.setContentsOpaque(contentsOpaque());

    if (m_changeMask & BackfaceVisibilityChange)
        m_layer.setBackfaceVisibility(backfaceVisibility());

    if (m_changeMask & OpacityChange)
        m_layer.setOpacity(opacity());

    if (m_changeMask & BackgroundColorChange)
        m_layer.setSolidColor(m_solidColor);

    if (m_changeMask & FilterChange)
        m_layer.setFilters(filters());

    if (m_changeMask & BackingStoreChange)
        m_layer.setBackingStore(m_backingStore);

    if (m_changeMask & DebugVisualsChange)
        m_layer.setDebugVisuals(isShowingDebugBorder(), debugBorderColor(), debugBorderWidth(), isShowingRepaintCounter());

    if (m_changeMask & RepaintCountChange)
        m_layer.setRepaintCount(repaintCount());

    if (m_changeMask & ContentChange)
        m_layer.setContentsLayer(platformLayer());

    if (m_changeMask & AnimationChange)
        m_layer.setAnimations(m_animations);

    if (m_changeMask & AnimationStarted)
        client().notifyAnimationStarted(this, "", m_animationStartTime);

    if (m_changeMask & FixedToViewporChange)
        m_layer.setFixedToViewport(fixedToViewport());

    if (m_changeMask & IsScrollableChange)
        m_layer.setIsScrollable(isScrollable());

    if (m_changeMask & CommittedScrollOffsetChange)
        m_layer.didCommitScrollOffset(m_committedScrollOffset);

    m_changeMask = NoChanges;
}