bool PianoRenderCache::Piano_RenderKey(RenderBuffer &buffer, Sprite* sprite, std::hash_map<wxPoint_, int>& drawn,
                                 int style, wxSize& canvas, wxSize& keywh, const wxString &placement, bool clip)
//bool RgbEffects::Sprite::render(wxSize& keywh, wxSize& BufferWH_int, int yscroll, bool Clipping)
{
    debug_function(9);
    
    //hash_map<pair<wxPoint, wxSize>, int>& drawn)
    //PIANO_STYLE_KEYS sprites have 2 states: on (down) and off (up); draw all sprites; top view or edge view
    int drawstate = sprite->ani_state++; //bump to next active (animation) state
    if (!drawstate) sprite->ani_state = 0; //stay in inactive state
    else
        //    if ((xy.size() == 1) && (drawstate == -1)) return false; //inactive on/off sprite; don't need tp draw anything
        if (drawstate >= sprite->xy.size()) //end of animation
            //				if (it->repeat > 0) drawstate = 0; //loop immediately
            //				else if (it->repeat < 0) drawstate = -rnd(); //loop with delay
        /*else*/ drawstate = sprite->xy.size() - 1; //stay at last state; don't loop
    
    //    wxPoint realxy = sprite->destxy;
    //    realxy.y += yscroll; //scrolling
    debug_more(30, ", dest (%d => %d, %d), #drawn %d", sprite->destxy.x, (clip? sprite->destxy.x: sprite->destxy.x % canvas.x), sprite->destxy.y, drawn.size());
    if (clip)
        if ((sprite->destxy.x >= buffer.BufferWi) || (sprite->destxy.y >= buffer.BufferHt) || (sprite->destxy.x + keywh.x < 0) || (sprite->destxy.y + keywh.y < 0)) return false; //outside of visible rect
    //    debug_more(30, ", here1");
    wxPoint_ where = sprite->destxy.y * 65536 + (clip? sprite->destxy.x: sprite->destxy.x % canvas.x); //wrap on even key boundary
    //    debug_more(30, ", here2");
    if ((style != PIANO_STYLE_ANIMAGE) && (drawn.find(where) != drawn.end()) && (drawstate <= drawn[where])) { debug_more(30, ", already drawn[0x%x]=%d vs %d", where, drawn[where], drawstate); return false; } //do not redraw older states in same location
    drawn[where] = drawstate; //remember highest state drawn in this location
    
    //don't draw overlapping regions more than once
    
    //                    SetPixel(x-xoffset,(state % ((imght+BufferHt)*speedfactor)) / speedfactor-y,c); //moving up
    //                    SetPixel(x-xoffset,BufferHt+imght-y-(state % ((imght+BufferHt)*speedfactor)) / speedfactor,c); //moving down
    //copy sprite image to pixel buffer, scale up/down:
    //iterate thru target pixels and pull from sprite in case sizes don't match (need to set all target pixels, but okay to skip some source pixels)
    float xscale = (float)sprite->wh.x / keywh.x, yscale = (float)sprite->wh.y / keywh.y; //src -> dest scale factor
    //    debug_more(30, ", here3");
    //TODO: use wxImage.GetData for better performance?
    int xofs = !clip? (buffer.BufferWi % (7 * keywh.x)) / 2: 0; //center keys if not clipped
    if (WantHistory(style)) debug(20, "draw sprite '%s': set x/y %d/%d + %d/%d to 0x%x", (const char*)sprite->name.ToStdString().c_str(), sprite->destxy.x, sprite->destxy.y, keywh.x, keywh.y, drawstate? sprite->on.GetRGB(): sprite->off.GetRGB()); //.Flush(true);
    else debug(20, "draw sprite '%s': copy from x/y[%d/%d] %d/%d + %d/%d => x/y %d/%d + %d/%d, x/y scale = %f/%f", (const char*)sprite->name.ToStdString().c_str(), drawstate, sprite->xy.size(), sprite->xy[drawstate].x, sprite->xy[drawstate].y, sprite->wh.x, sprite->wh.y, sprite->destxy.x, sprite->destxy.y, keywh.x, keywh.y, 1.0 / xscale, 1.0 / yscale); //.Flush(true);
    for (int x = 0; x < keywh.x; ++x) //copying to it->w columns in dest
        for (int y = 0; y < keywh.y; ++y) //copying to it->h rows in dest; vert scaling is more likely, so make Y the inner loop for better pixel caching
        {
            //            static xlColor cached_rgb; //cached mapped pixel color
            //            static wxPoint cached_xy(-1, -1);
            wxPoint src_xy(sprite->xy[drawstate].x + x * xscale, sprite->xy[drawstate].y + y * yscale);
            //TODO: scale doesn't make sense for all cases
            src_xy.y = Shapes.GetHeight() - src_xy.y - 1; //whoops, origin is top left but wanted bottom left
            bool transparent = 0;
            if (WantHistory(style)) cached_rgb = drawstate? sprite->on: sprite->off; //kludge: fill rect with same color to avoid losing pixels due to scaling
            else if ((src_xy.x != cached_xy.x) || (src_xy.y != cached_xy.y)) //update cached pixel info
            {
                cached_xy = src_xy; //prev_xy.x = src_xy.x; prev_y = srcy; //not sure how expensive wx pixel functions are, so cache current pixel info just in case; aliasing/averaging and color mapping also makes thiss more expensive
                if (Shapes.IsTransparent(src_xy.x, src_xy.y)) transparent = 1; //-1; //-1 matches white, so use + instead
                else
                {
                    //                        xlColor c;
                    //TODO: tile, center, anti-aliasing
                    cached_rgb.Set(Shapes.GetRed(src_xy.x, src_xy.y), Shapes.GetGreen(src_xy.x, src_xy.y), Shapes.GetBlue(src_xy.x, src_xy.y)); //NOTE: need to do pixel merging if scale is not 1:1
                    if (!ColorMap.empty()) cached_rgb = ColorMap[cached_rgb.GetRGB()]; //map to user-selected colors
                }
                debug_more(20, ", LK(%d,%d)", cached_xy.x, cached_xy.y);
            }
            if (transparent == 1 /*-1*/) continue; //don't need to draw pixel
            int wrapx = sprite->destxy.x + x, scrolly = sprite->destxy.y;
            //            if (style == PIANO_STYLE_ANIMAGE) { wrapx *= xscale; scrolly *= yscale; }
            if (!clip) wrapx %= canvas.x; //wrap on even key boundary
            //            if ((style == PIANO_STYLE_ICICLES) || (style == PIANO_STYLE_EQBARS)) scrolly += canvas.y - keywh.y; //draw at top instead of bottom
            if (style == PIANO_STYLE_ICICLES) scrolly += canvas.y - keywh.y; //draw at top instead of bottom
            //            debug_more(20, ", %d+%d vs. %d-%d? %d", xofs, wrapx, BufferWi, xofs, xofs + wrapx < BufferWi - xofs);
            //            if (!clip) wrapx = (wrapx + 2 * xofs) % BufferWi - 2 * xofs; //wrap within reduced area, not expanded area
            debug_more(20, ", (%d,%d)<-0x%x", wrapx, sprite->destxy.y + y, cached_rgb.GetRGB());
            if (xofs + wrapx < buffer.BufferWi - xofs) buffer.SetPixel(xofs + wrapx, sprite->destxy.y + y, cached_rgb); //no vertical wrap, only horizontal wrap
        }
    //    debug.Flush(true);
    return true;
}