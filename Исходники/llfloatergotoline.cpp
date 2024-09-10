LLFloaterGotoLine::LLFloaterGotoLine(LLScriptEdCore* editor_core)
:       LLFloater(LLSD()),
        mGotoBox(NULL),
        mEditorCore(editor_core)
{
        buildFromFile("floater_goto_line.xml");

        sInstance = this;
        
        // find floater in which script panel is embedded
        LLView* viewp = (LLView*)editor_core;
        while(viewp)
        {
                LLFloater* floaterp = dynamic_cast<LLFloater*>(viewp);
                if (floaterp)
                {
                        floaterp->addDependentFloater(this);
                        break;
                }
                viewp = viewp->getParent();
        }
}