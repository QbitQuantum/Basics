    void add_path(VertexSource& vs, unsigned path_id=0)
    {
        double x;
        double y;

        unsigned flag;
        vs.rewind(path_id);
        while(!agg::is_stop(flag = vs.vertex(&x, &y)))
        {
            if(agg::is_vertex(flag))
            {
                if(agg::is_move_to(flag)) 
                {
                    move_to(int(x), int(y));
                }
                else 
                {
                    line_to(int(x), int(y));
                }
            }
        }
    }