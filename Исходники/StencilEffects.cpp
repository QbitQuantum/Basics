void StencilEffects::RenderPlayfieldEffect()
{
    if (!GAMECONTEXT)
        return;

    auto playfield = PLAYFIELD.Get();
    if (!playfield)
        return;

    if (!m_bPlayfieldEffectVisible)
        return;

    GraphicsDriver::Instance()->SetTransform(GraphicsDriver::TS_World, playfield->GetWorldTransform());
    if (m_TilesVB.IsValid())
    {
        // Fill stencil with 1s
        GraphicsDriver::Instance()->SetStencilFunc(GraphicsDriver::CF_Always, 1, 0xff);
        GraphicsDriver::Instance()->SetStencilOps(GraphicsDriver::SO_Keep, GraphicsDriver::SO_Keep, GraphicsDriver::SO_Replace);

        m_TilesMaterial->Begin();
        m_TilesMaterial->GetShader()->GetConstant("uAmbientColor")->Set(&Color::White, 1);
        m_TilesMaterial->GetShader()->Begin();
        m_TilesVB->Begin(m_TilesMaterial->GetShader());
        m_TilesVB->Draw();
    }

    GraphicsDriver::Instance()->SetRenderState(GraphicsDriver::RS_StencilWriting, 0); // no more writing into the stencil buffer
    GraphicsDriver::Instance()->SetStencilFunc(GraphicsDriver::CF_NotEqual, 1, 0xff); // Render only where stencil is not 1

    m_DefaultMaterial->Begin();
    m_DefaultMaterial->GetShader()->GetConstant("uAmbientColor")->Set(&m_PlayfieldHighlight, 1);
    m_DefaultMaterial->GetShader()->Begin();
    m_PlayfieldVB->Begin(m_DefaultMaterial->GetShader());
    m_PlayfieldVB->Draw();
}