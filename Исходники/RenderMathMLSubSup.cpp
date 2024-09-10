void RenderMathMLSubSup::addChild(RenderObject* child, RenderObject* beforeChild)
{
    if (firstChild()) {
        // We already have a base, so this is the super/subscripts being added.
        
        if (m_kind == SubSup) {
            if (!m_scripts) {
                m_scripts = new (renderArena()) RenderMathMLBlock(node());
                RefPtr<RenderStyle> scriptsStyle = RenderStyle::create();
                scriptsStyle->inheritFrom(style());
                scriptsStyle->setDisplay(INLINE_BLOCK);
                scriptsStyle->setVerticalAlign(MIDDLE);
                scriptsStyle->setMarginLeft(Length(gSubsupScriptMargin, Fixed));
                scriptsStyle->setTextAlign(LEFT);
                m_scripts->setStyle(scriptsStyle.release());
                RenderMathMLBlock::addChild(m_scripts, beforeChild);
            }
            
            RenderBlock* script = new (renderArena()) RenderMathMLBlock(node());
            RefPtr<RenderStyle> scriptStyle = RenderStyle::create();
            scriptStyle->inheritFrom(m_scripts->style());
            scriptStyle->setDisplay(BLOCK);
            script->setStyle(scriptStyle.release());
            
            m_scripts->addChild(script, m_scripts->firstChild());
            script->addChild(child);
        } else
            RenderMathMLBlock::addChild(child, beforeChild);
        
    } else {
        RenderMathMLBlock* wrapper = new (renderArena()) RenderMathMLBlock(node());
        RefPtr<RenderStyle> wrapperStyle = RenderStyle::create();
        wrapperStyle->inheritFrom(style());
        wrapperStyle->setDisplay(INLINE_BLOCK);
        wrapperStyle->setVerticalAlign(MIDDLE);
        wrapper->setStyle(wrapperStyle.release());
        RenderMathMLBlock::addChild(wrapper, beforeChild);
        wrapper->addChild(child);
    }
}