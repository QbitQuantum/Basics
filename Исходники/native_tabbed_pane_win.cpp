    // Switches to the tab page identified by the given index.
    void SwitchToPage(View* host, View* page)
    {
        for(int i=0; i<host->child_count(); ++i)
        {
            View* child = host->child_at(i);
            // The child might not have been laid out yet.
            if(child == page)
            {
                child->SetBoundsRect(host->GetContentsBounds());
            }
            child->SetVisible(child == page);
        }

        FocusManager* focus_manager = page->GetFocusManager();
        DCHECK(focus_manager);
        View* focused_view = focus_manager->GetFocusedView();
        if(focused_view && host->Contains(focused_view) &&
                !page->Contains(focused_view))
        {
            focus_manager->SetFocusedView(page);
        }
    }