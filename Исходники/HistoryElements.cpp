/* Crop Tool */
HEToolCrop::HEToolCrop(Workspace *wspc, Frame *frame, Tool *tool) : HistoryElement(wspc,
            frame,
            tool)
{
    SetRect(&this->canvasChange,0,0,0,0);
}