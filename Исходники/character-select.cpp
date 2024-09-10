static void parseSimpleList(Util::ReferenceCount<Gui::SimpleSelect> list, std::map<int, unsigned int> & cursorLocations, const Token * token){
    if ( *token != "simple-list" ){
        throw LoadException(__FILE__, __LINE__, "Not a Simple Select List");
    }
    TokenView view = token->view();
    while (view.hasMore()){
        try{
            const Token * tok;
            view >> tok;
            int offset=0;
            std::string layout;
            int viewable = 0;
            if (parseBaseList(list, cursorLocations, tok)){
            } else if (tok->match("viewable", viewable)){
                list->setViewable(viewable);
            } else if (tok->match("layout", layout)){
                if (layout == "horizontal"){
                    list->setLayout(Gui::SimpleSelect::Horizontal);
                } else if (layout == "vertical"){
                    list->setLayout(Gui::SimpleSelect::Vertical);
                }
            } else if (tok->match("scroll-offset", offset)){
                list->setScrollOffset(offset);
            } else {
                Global::debug(0) << "Unknown Simple List property: " << tok->getName() << std::endl;
            }
        } catch ( const TokenException & ex ) {
            throw LoadException(__FILE__, __LINE__, ex, "Simple Select parse error");
        }
    }
}