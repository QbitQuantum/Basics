    void render_edge_fine(scanline_rasterizer& ras, 
                          solid_renderer& ren_fine,
                          draft_renderer& ren_draft,
                          Source& src)
    {
        double x, y;
        switch(m_draw)
        {
            case 0:
                src.rewind(0);
                while(!agg::is_stop(src.vertex(&x, &y)));
            break;

            case 1:
                ras.reset();
                ras.add_path(src);
            break;

            case 2:
                ras.reset();
                ras.add_path(src);
                ras.sort();
            break;

            case 3:
            {
                int r = rand() & 0x7F;
                int g = rand() & 0x7F;
                int b = rand() & 0x7F;
                int a = 255;
                if(m_translucent.status()) a = 80;
                ras.add_path(src);

                if(m_type.cur_item() < 4)
                {
                    ren_fine.color(agg::srgba8(r, g, b, a));
                    agg::render_scanlines(ras, m_sl, ren_fine);
                }
                else
                {
                    ren_draft.color(agg::srgba8(r, g, b, a));
                    agg::render_scanlines(ras, m_sl, ren_draft);
                }
            }
            break;
        }
    }