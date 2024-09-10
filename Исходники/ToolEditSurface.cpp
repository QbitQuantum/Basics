bool ToolEditSurfaceT::OnMouseMove3D(ViewWindow3DT& ViewWindow, wxMouseEvent& ME)
{
    ViewWindow.SetCursor(CursorMan->GetCursor(m_EyeDropperActive ? CursorManT::EYE_DROPPER : CursorManT::EDIT_FACEPROPS_TOOL));

    return true;
}