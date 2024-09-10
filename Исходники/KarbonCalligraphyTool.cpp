void KarbonCalligraphyTool::deactivate()
{
    if (m_lastShape && canvas()->shapeManager()->shapes().contains(m_lastShape)) {
        KoSelection *selection = canvas()->shapeManager()->selection();
        selection->deselectAll();
        selection->select(m_lastShape);
    }
}