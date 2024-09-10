bool FieldView::DrawPath(const Path& path){
    //get dots container from givven path
    Path::Dots dots = path.GetPath();
    const size_t size = dots.size();
    
    if(dots.empty())        //if container with dots coordinats is empty, then exit
        return false;

    window = get_window();    //get pointer to parent window
    if(window){             //if pointer to window is not NULL...
        cr = window->create_cairo_context();
        if(cr){             //and if pointer to context is not NULL...
            allocation = get_allocation();
            
            cr->save();
            cr->rectangle(0, 0, allocation.get_width(), allocation.get_height());
            cr->clip();

            //choose color
            switch(path.GetColor()){
                case RED:
                    cr->set_source_rgb(1.0, 0.0, 0.0);
                    break;
                case BLUE:
                    cr->set_source_rgb(0.0, 0.0, 1.0);
                    break;
                default:
                    return false;
            }

            cr->set_line_width((ctrl->GetPrefs()->line_width) * 2);
            //move to start point
            cr->move_to((dots[0].GetX()+1) * CELL_SIZE * sx, (dots[0].GetY() + 1) * CELL_SIZE * sy);

            //here we will just move from one point to another while there is at least one of them
            for(size_t i = 1; i < size; i++)
                //we add 1 because field has some kind of "dead zone" on its sides
                cr->line_to((dots[i].GetX() + 1) * CELL_SIZE * sx, (dots[i].GetY() + 1) * CELL_SIZE * sy);
            cr->stroke();
            dots.clear();
            return true;
        }
    }
    return false;
}