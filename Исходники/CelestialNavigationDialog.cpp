void CelestialNavigationDialog::UpdateFix()
{
    std::list<std::vector<double> > J;
    std::list<double> R;

    double X[3]; /* result */

    double initiallat = m_sInitialLatitude->GetValue(), initiallon = m_sInitialLongitude->GetValue();
    X[0] = cos(deg2rad(initiallat))*cos(deg2rad(initiallon));
    X[1] = cos(deg2rad(initiallat))*sin(deg2rad(initiallon));
    X[2] = sin(deg2rad(initiallat));

    int iterations = 0;
again:

    for (SightList::iterator it = m_SightList.begin(); it != m_SightList.end(); it++) {
        Sight *s = *it;
        if(!s->IsVisible() || s->m_Type != Sight::ALTITUDE)
            continue;
    
        if(s->m_ShiftNm) {
            static bool seenwarning = false;
            if(!seenwarning) {
                wxMessageDialog mdlg(this, _("Shifted sights are not used to compute a fix, \
determine fix visually instead.\n"), wxString(_("Fix Position"), wxID_OK | wxICON_WARNING));
                mdlg.ShowModal();
                seenwarning = true;
            }
            continue;
        }

        double lat, lon;
        s->BodyLocation(s->m_DateTime, &lat, &lon, 0, 0);

        /* take vector from body location of length equal to
           normalized measurement (so the plane this vector
           describes intersects the unit sphere along the positions
           the sight is valid) */
        std::vector<double> v;
        double x = cos(deg2rad(lat))*cos(deg2rad(lon));
        double y = cos(deg2rad(lat))*sin(deg2rad(lon));
        double z = sin(deg2rad(lat));

        double sm = sin(deg2rad(s->m_ObservedAltitude));
        double cm = cos(deg2rad(s->m_ObservedAltitude));

        double d;

        switch(m_cbFixAlgorithm->GetSelection()) {
        case 0: /* plane */
        plane:
            /* plane */
            v.push_back(x);
            v.push_back(y);
            v.push_back(z);
            d = sm - (X[0]*x + X[1]*y + X[2]*z);
            break;
        case 1: /* sphere */
        {
            double xc = X[0] - x, yc = X[1] - y, zc = X[2] - z;
            v.push_back(2*xc);
            v.push_back(2*yc);
            v.push_back(2*zc);
            d = cm*cm + (1-sm)*(1-sm) - xc*xc - yc*yc - zc*zc;
        } break;
        case 2: /* cone */
        {
            double t2 = X[0]*X[0] + X[1]*X[1] + X[2]*X[2], t = sqrt(t2);
            if(t < .1) goto plane;
            v.push_back(x);
            v.push_back(y);
            v.push_back(z);
            d = sm - (X[0]*x + X[1]*y + X[2]*z)/t;
        } break;
        case 3: /* cone 2 */
        {
            double t2 = X[0]*X[0] + X[1]*X[1] + X[2]*X[2], t = sqrt(t2);
            if(t < .1) goto plane;
            v.push_back(x/t - x*X[0]*X[0]/(t*t2));
            v.push_back(y/t - y*X[1]*X[1]/(t*t2));
            v.push_back(z/t - z*X[2]*X[2]/(t*t2));
            d = sm - (X[0]*x + X[1]*y + X[2]*z)/t;
        } break;
        }

        J.push_back(v);
        R.push_back(d);
    }