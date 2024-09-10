void RouteMapOverlay::Render(wxDateTime time, SettingsDialog &settingsdialog,
                             wrDC &dc, PlugIn_ViewPort &vp, bool justendroute)
{
    if(!justendroute) {
        RouteMapConfiguration configuration = GetConfiguration();

        if(!isnan(configuration.StartLat)) {
            wxPoint r;
            GetCanvasPixLL(&vp, &r, configuration.StartLat, configuration.StartLon);
            SetColor(dc, *wxBLUE, true);
            SetWidth(dc, 3, true);
            dc.DrawLine(r.x, r.y-10, r.x+10, r.y+7);
            dc.DrawLine(r.x, r.y-10, r.x-10, r.y+7);
            dc.DrawLine(r.x-10, r.y+7, r.x+10, r.y+7);
        }

        if(!isnan(configuration.StartLon)) {
            wxPoint r;
            GetCanvasPixLL(&vp, &r, configuration.EndLat, configuration.EndLon);
            SetColor(dc, *wxRED, true);
            SetWidth(dc, 3, true);
            dc.DrawLine(r.x-10, r.y-10, r.x+10, r.y+10);
            dc.DrawLine(r.x-10, r.y+10, r.x+10, r.y-10);
        }

        static const double NORM_FACTOR = 16;
        bool use_dl = vp.m_projection_type == PI_PROJECTION_MERCATOR;
        if(!dc.GetDC() && use_dl) {
            glPushMatrix();

            /* center display list on start lat/lon */

            wxPoint point;
            GetCanvasPixLL(&vp, &point, configuration.StartLat, configuration.StartLon);

            glTranslated(point.x, point.y, 0);
            glScalef(vp.view_scale_ppm / NORM_FACTOR, vp.view_scale_ppm / NORM_FACTOR, 1);
            glRotated(vp.rotation*180/M_PI, 0, 0, 1);
        }

        if(!dc.GetDC() && !m_UpdateOverlay && use_dl && vp.m_projection_type == m_overlaylist_projection) {
            glCallList(m_overlaylist);
            glPopMatrix();

        } else {
            PlugIn_ViewPort nvp = vp;

            if(!dc.GetDC() && use_dl) {
                m_UpdateOverlay = false;

                if(!m_overlaylist)
                    m_overlaylist = glGenLists(1);
            
                glNewList(m_overlaylist, GL_COMPILE);

                nvp.clat = configuration.StartLat, nvp.clon = configuration.StartLon;
                nvp.pix_width = nvp.pix_height = 0;
                nvp.view_scale_ppm = NORM_FACTOR;
                nvp.rotation = nvp.skew = 0;

                m_overlaylist_projection = vp.m_projection_type;
            }

            /* draw alternate routes first */
            int AlternateRouteThickness = settingsdialog.m_sAlternateRouteThickness->GetValue();
            if(AlternateRouteThickness) {
                Lock();
                IsoChronList::iterator it;

                /* reset drawn flag for all positions
                   this is used to avoid duplicating alternate route segments */
                for(it = origin.begin(); it != origin.end(); ++it)
                    (*it)->ResetDrawnFlag();

                bool AlternatesForAll = settingsdialog.m_cbAlternatesForAll->GetValue();
                if(AlternatesForAll)
                    it = origin.begin();
                else {
                    it = origin.end();
                    it--;
                }

                SetWidth(dc, AlternateRouteThickness);
                if(!dc.GetDC())
                    glBegin(GL_LINES);
                for(; it != origin.end(); ++it)
                    for(IsoRouteList::iterator rit = (*it)->routes.begin();
                        rit != (*it)->routes.end(); ++rit) {
                        RenderAlternateRoute(*rit, !AlternatesForAll, dc, nvp);
                    }

                if(!dc.GetDC())
                    glEnd();
                Unlock();
            }

            unsigned char routecolors[][3] = {
                {  0,   0, 128}, {  0, 192,   0}, {  0, 128, 192}, {  0, 255,   0},
                {  0,   0, 255}, {  0, 128, 128}, {  0, 255,   0}, {  0, 192, 192},
                {  0, 128, 255}, {  0, 255, 128}, {  0,   0, 255}, {  0, 192,   0},
                {  0,   0, 128}, {  0, 255,   0}, {  0, 192, 128}, {  0, 128, 255}, 
                {  0, 192,   0}, {  0, 128,   0}, {  0,   0, 255}, {  0, 192, 192}};
#if 0
                {255, 127,   0}, {255, 127, 127},
                {  0, 255,   0}, {  0, 255, 127},
                {127, 255,   0}, {127, 255, 127},
                {127, 127,   0},                  {127, 127, 255},
                {255,   0,   0}, {255,   0, 127}, {255,   0, 255},
                {127,   0,   0}, {127,   0, 127}, {127,   0, 255},
                {  0, 127,   0}, {  0, 127, 127}, {  0, 127, 255},
                {255, 255,   0},                  };