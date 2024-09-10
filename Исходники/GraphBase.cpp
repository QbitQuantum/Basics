UIHierarchyCell * GraphBase::CellForNode(UIHierarchy *forHierarchy, void *node)
{
    UIHierarchyCell *c= forHierarchy->GetReusableCell("Graph cell"); //try to get cell from the reusable cells store
    if(!c)
    { 
        //if cell of requested type isn't find in the store create new cell
        int32 leftSideWidth = EditorSettings::Instance()->GetLeftPanelWidth();
        c = new UIHierarchyCell(Rect(0, 0, leftSideWidth, ControlsFactory::CELL_HEIGHT), "Graph cell");
        
        UIControl *icon = new UIControl(Rect(0, 0, ControlsFactory::CELL_HEIGHT, ControlsFactory::CELL_HEIGHT));
        icon->SetName("_Icon_");
        icon->GetBackground()->SetDrawType(UIControlBackground::DRAW_SCALE_PROPORTIONAL);
        c->text->AddControl(icon);

        UIControl *marker = new UIControl(Rect(0, 0, ControlsFactory::CELL_HEIGHT, ControlsFactory::CELL_HEIGHT));
        marker->SetName("_Marker_");
        marker->GetBackground()->SetDrawType(UIControlBackground::DRAW_SCALE_PROPORTIONAL);
        c->text->AddControl(marker);
        
        UIStaticText *text = new UIStaticText(Rect(ControlsFactory::CELL_HEIGHT, 0, leftSideWidth - ControlsFactory::CELL_HEIGHT, ControlsFactory::CELL_HEIGHT));
        Font *font = ControlsFactory::GetFont12();
        text->SetFont(font);
        text->SetAlign(ALIGN_LEFT|ALIGN_VCENTER);
        text->SetName("_Text_");
		text->SetTextColor(ControlsFactory::GetColorDark());
        c->text->AddControl(text);
    }
    
    FillCell(c, node);
    
    ControlsFactory::CustomizeExpandButton(c->openButton);
    ControlsFactory::CustomizeSceneGraphCell(c);
    
    return c;
}