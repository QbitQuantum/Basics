void
UVMapView::End()
{
    active = false;

    // get the model:
    if (!nmarks || !material || !material->tex_diffuse) return;

    // if not adding to selection:
    if (select_mode == SELECT_REPLACE) {
        Clear();
    }

    Bitmap*  bmp = material->tex_diffuse;
    int      w   = bmp->Width();
    int      h   = bmp->Height();

    double   cx  = window->Width()  / 2 + x_offset;
    double   cy  = window->Height() / 2 + y_offset;


    // if only one mark:
    if (nmarks < 2) {
        // find all selected verts:
        ListIter<Poly> iter = polys;
        while (++iter) {
            Poly*       p     = iter.value();
            VertexSet*  vset  = p->vertex_set;

            for (int i = 0; i < p->nverts; i++) {
                int    n1   = p->verts[i];
                double tu1  = vset->tu[n1];
                double tv1  = vset->tv[n1];

                int x1 = (int) (cx + zoom * w * (tu1-0.5));
                int y1 = (int) (cy + zoom * h * (tv1-0.5));

                int dx = abs(marks[0].x - x1);
                int dy = abs(marks[0].y - y1);

                if (dx < 4 && dy < 4) {
                    WORD  p_index = iter.index();
                    DWORD value   = (p_index << 16) | i;

                    if (select_mode == SELECT_REMOVE) {
                        for (auto svi = selverts.begin(); svi != selverts.end(); ++svi) {
                            if (*svi == value) {
                                selverts.erase(svi);
                            }
                        }
                    }
                    else {
                        bool contains = false;
                        for (auto svi = selverts.begin(); svi != selverts.end(); ++svi) {
                            if (*svi == value) {
                                contains = true;
                            }
                        }
                        if (!contains)
                            selverts.push_back(value);
                    }
                }
            }
        }
    }

    // otherwise, build a region:
    else {
        CRgn rgn;
        rgn.CreatePolygonRgn(marks, nmarks, WINDING);

        // find all selected verts:
        ListIter<Poly> iter = polys;
        while (++iter) {
            Poly*       p     = iter.value();
            VertexSet*  vset  = p->vertex_set;

            for (int i = 0; i < p->nverts; i++) {
                int    n1   = p->verts[i];
                double tu1  = vset->tu[n1];
                double tv1  = vset->tv[n1];

                int x1 = (int) (cx + zoom * w * (tu1-0.5));
                int y1 = (int) (cy + zoom * h * (tv1-0.5));

                CPoint p(x1,y1);

                if (rgn.PtInRegion(p)) {
                    WORD  p_index = iter.index();
                    DWORD value   = (p_index << 16) | i;

                    if (select_mode == SELECT_REMOVE) {
                        for (auto svi = selverts.begin(); svi != selverts.end(); ++svi) {
                            if (*svi == value)
                                selverts.erase(svi);
                        }
                    }
                    else {
                        bool contains = false;
                        for (auto svi = selverts.begin(); svi != selverts.end(); ++svi) {
                            if (*svi == value)
                                contains = true;
                        }
                        if (!contains)
                            selverts.push_back(value);
                    }
                }
            }
        }
    }

    nmarks = 0;
}