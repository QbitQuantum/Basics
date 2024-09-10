    void Render(Context* pcontext)
    {
        int count = m_data.GetCount();

        if (count > 0) {
                  Camera* pcamera = GetCamera();
                  float   focus   = pcamera->GetFocus();
            const Rect&   rect    = GetViewRect()->GetValue();

            float scale = focus * rect.XSize() / 2;
            float xc    = rect.Center().X();
            float yc    = rect.Center().Y();

            const Orientation& orient = GetCamera()->GetOrientation();

            VertexScreen* pvertex = pcontext->GetVertexScreenBuffer(count * 2);
            WORD*         pindex  = pcontext->GetIndexBuffer(count * 2);

            int index      = 0;
            int indexPoint = count * 2;
            for(int indexSource = 0; indexSource < count; indexSource++) {
                StarData& data      = m_data.Get(indexSource);
                Color&    color     = data.m_color;
                Vector&   direction = data.m_direction;
                Point&    pointOld  = data.m_pointOld;

                //
                // orient the start based on the current camera
                //

                Vector vec = orient.TimesInverse(direction);

                //
                // fold up the stars for higher density
                //

                if (vec.z > 0) {
                    vec.SetX(-vec.X());
                    vec.SetY(-vec.Y());
                    vec.SetZ(-vec.Z());
                }

                //
                // project the star onto the screen
                //

                float x = (float)(int)(scale * vec.X() + xc);
                float y = (float)(int)(yc - scale * vec.Y());
                float xold;
                float yold;

                if (data.m_bFirstFrame) {
                    xold = x;
                    yold = y;
                    data.m_bFirstFrame = false;
                } else {
                    xold = pointOld.X();
                    yold = pointOld.Y();
                }

                if (rect.Inside(Point(x, y))) {
                    float dx     = abs(x - xold);
                    float dy     = abs(y - yold);
                    float length = dx + dy;

                    if (length <= 1.0f) {
                        //
                        // Draw a point
                        //

                        indexPoint--;
                        pvertex[indexPoint].x        = x;
                        pvertex[indexPoint].y        = y;
                        pvertex[indexPoint].z        = 0;
                        pvertex[indexPoint].qw       = (float)1.0f/10000.0f;
                        pvertex[indexPoint].color    = MakeD3DCOLOR(color);
                        pvertex[indexPoint].specular = 0;
                    } else {
                        //
                        // Draw a line
                        //

                        if (length > 16.0f) {
                            float scale = 16.0f / length;

                            xold = x + (xold - x) * scale;
                            yold = y + (yold - y) * scale;
                        }

                        if (rect.Inside(Point(xold, yold))) {
                            float alpha  = 1.0f - 0.1f * length;

                            if (alpha < 0.25f) {
                                alpha = 0.25f;
                            }

                            pvertex[index * 2].x        = x;
                            pvertex[index * 2].y        = y;
                            pvertex[index * 2].z        = 0;
                            pvertex[index * 2].qw       = (float)1.0f/10000.0f;
                            pvertex[index * 2].color    = MakeD3DCOLOR(color * alpha);
                            pvertex[index * 2].specular = 0;

                            pvertex[index * 2 + 1].x        = xold;
                            pvertex[index * 2 + 1].y        = yold;
                            pvertex[index * 2 + 1].z        = 0;
                            pvertex[index * 2 + 1].qw       =(float)1.0f/10000.0f;
                            pvertex[index * 2 + 1].color    = MakeD3DCOLOR(color * alpha);
                            pvertex[index * 2 + 1].specular = 0;

                            pindex[index * 2    ] = index * 2;
                            pindex[index * 2 + 1] = index * 2 + 1;

                            index += 1;
                        }
                    }
                }

                pointOld.SetX(x);
                pointOld.SetY(y);
            };

            //
            // Do the rendering
            //

            pcontext->SetShadeMode(ShadeModeFlat);
            pcontext->DrawPoints(pvertex + indexPoint, count * 2 - indexPoint);

            if (index != 0) 
			{
                pcontext->SetBlendMode(BlendModeAdd);
                pcontext->DrawLines(pvertex, index * 2, pindex, index * 2);
            }
        }
    }