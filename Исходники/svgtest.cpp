// Define the repainting behaviour
void MyCanvas::OnDraw(wxDC& dc)
{
    // vars to use ...
#if wxUSE_STATUSBAR
    wxString s ;
#endif // wxUSE_STATUSBAR
    wxPen wP ;
    wxBrush wB ;
    wxPoint points[6];
    wxColour wC;
    wxFont wF ;

    dc.SetFont(*wxSWISS_FONT);
    dc.SetPen(*wxGREEN_PEN);


    switch (m_index)
    {
        default:
        case 0:
            // draw lines to make a cross
            dc.DrawLine(0, 0, 200, 200);
            dc.DrawLine(200, 0, 0, 200);
            // draw point colored line and spline
            wP = *wxCYAN_PEN ;
            wP.SetWidth(3);
            dc.SetPen(wP);

            dc.DrawPoint (25,15) ;
            dc.DrawLine(50, 30, 200, 30);
            dc.DrawSpline(50, 200, 50, 100, 200, 10);
#if wxUSE_STATUSBAR
            s = wxT("Green Cross, Cyan Line and spline");
#endif // wxUSE_STATUSBAR
            break ;

        case 1:
            // draw standard shapes
            dc.SetBrush(*wxCYAN_BRUSH);
            dc.SetPen(*wxRED_PEN);
            dc.DrawRectangle(10, 10, 100, 70);
            wB = wxBrush (_T("DARK ORCHID"), wxTRANSPARENT);
            dc.SetBrush (wB);
            dc.DrawRoundedRectangle(50, 50, 100, 70, 20);
            dc.SetBrush (wxBrush(_T("GOLDENROD"), wxSOLID) );
            dc.DrawEllipse(100, 100, 100, 50);

            points[0].x = 100; points[0].y = 200;
            points[1].x = 70; points[1].y = 260;
            points[2].x = 160; points[2].y = 230;
            points[3].x = 40; points[3].y = 230;
            points[4].x = 130; points[4].y = 260;
            points[5].x = 100; points[5].y = 200;

            dc.DrawPolygon(5, points);
            dc.DrawLines (6, points, 160);
#if wxUSE_STATUSBAR
            s = wxT("Blue rectangle, red edge, clear rounded rectangle, gold ellipse, gold and clear stars");
#endif // wxUSE_STATUSBAR
            break ;

        case 2:
            // draw text in Arial or similar font
            dc.DrawLine(50,25,50,35);
            dc.DrawLine(45,30,55,30);
            dc.DrawText(wxT("This is a Swiss-style string"), 50, 30);
            wC = dc.GetTextForeground() ;
            dc.SetTextForeground (_T("FIREBRICK"));

            // no effect in msw ??
            dc.SetTextBackground (_T("WHEAT"));
            dc.DrawText(wxT("This is a Red string"), 50, 200);
            dc.DrawRotatedText(wxT("This is a 45 deg string"), 50, 200, 45);
            dc.DrawRotatedText(wxT("This is a 90 deg string"), 50, 200, 90);
            wF = wxFont ( 18, wxROMAN, wxITALIC, wxBOLD, false, wxT("Times New Roman"));
            dc.SetFont(wF);
            dc.SetTextForeground (wC) ;
            dc.DrawText(wxT("This is a Times-style string"), 50, 60);
#if wxUSE_STATUSBAR
            s = wxT("Swiss, Times text; red text, rotated and colored orange");
#endif // wxUSE_STATUSBAR
            break ;

        case 3 :
            // four arcs start and end points, center
            dc.SetBrush(*wxGREEN_BRUSH);
            dc.DrawArc ( 200,300, 370,230, 300,300 );
            dc.SetBrush(*wxBLUE_BRUSH);
            dc.DrawArc ( 270-50, 270-86, 270-86, 270-50, 270,270 );
            dc.SetDeviceOrigin(-10,-10);
            dc.DrawArc ( 270-50, 270-86, 270-86, 270-50, 270,270 );
            dc.SetDeviceOrigin(0,0);

            wP.SetColour (_T("CADET BLUE"));
            dc.SetPen(wP);
            dc.DrawArc ( 75,125, 110, 40, 75, 75 );

            wP.SetColour (_T("SALMON"));
            dc.SetPen(wP);
            dc.SetBrush(*wxRED_BRUSH);
            //top left corner, width and height, start and end angle
                                 // 315 same center and x-radius as last pie-arc, half Y radius
            dc.DrawEllipticArc(25,50,100,50,180.0,45.0) ;

            wP = *wxCYAN_PEN ;
            wP.SetWidth(3);
            dc.SetPen(wP);
                                 //wxTRANSPARENT));
            dc.SetBrush (wxBrush (_T("SALMON"),wxSOLID)) ;
            dc.DrawEllipticArc(300,  0,200,100, 0.0,145.0) ;
                                 //same end point
            dc.DrawEllipticArc(300, 50,200,100,90.0,145.0) ;
            dc.DrawEllipticArc(300,100,200,100,90.0,345.0) ;

#if wxUSE_STATUSBAR
            s = wxT("This is an arc test page");
#endif // wxUSE_STATUSBAR
            break ;

        case 4:
            dc.DrawCheckMark ( 30,30,25,25);
            dc.SetBrush (wxBrush (_T("SALMON"),wxTRANSPARENT));
            dc.DrawCheckMark ( 80,50,75,75);
            dc.DrawRectangle ( 80,50,75,75);
#if wxUSE_STATUSBAR
            s = wxT("Two check marks");
#endif // wxUSE_STATUSBAR
            break ;

        case 5:
            wF = wxFont ( 18, wxROMAN, wxITALIC, wxBOLD, false, wxT("Times New Roman"));
            dc.SetFont(wF);
            dc.DrawLine(0, 0, 200, 200);
            dc.DrawLine(200, 0, 0, 200);
            dc.DrawText(wxT("This is an 18pt string"), 50, 60);

            // rescale and draw in blue
            wP = *wxCYAN_PEN ;
            dc.SetPen(wP);
            dc.SetUserScale (2.0,0.5);
            dc.SetDeviceOrigin(200,0);
            dc.DrawLine(0, 0, 200, 200);
            dc.DrawLine(200, 0, 0, 200);
            dc.DrawText(wxT("This is an 18pt string 2 x 0.5 UserScaled"), 50, 60);
            dc.SetUserScale (2.0,2.0);
            dc.SetDeviceOrigin(200,200);
            dc.DrawText(wxT("This is an 18pt string 2 x 2 UserScaled"), 50, 60);

            wP = *wxRED_PEN ;
            dc.SetPen(wP);
            dc.SetUserScale (1.0,1.0);
            dc.SetDeviceOrigin(0,10);
            dc.SetMapMode (wxMM_METRIC) ; //svg ignores this
            dc.DrawLine(0, 0, 200, 200);
            dc.DrawLine(200, 0, 0, 200);
            dc.DrawText(wxT("This is an 18pt string in MapMode"), 50, 60);
#if wxUSE_STATUSBAR
            s = wxT("Scaling test page");
#endif // wxUSE_STATUSBAR
            break ;

        case 6:
            dc.DrawIcon( wxIcon(mondrian_xpm), 10, 10 );
            dc.DrawBitmap ( wxBitmap(svgbitmap_xpm), 50,15);
#if wxUSE_STATUSBAR
            s = wxT("Icon and Bitmap ");
#endif // wxUSE_STATUSBAR
            break ;

    }
#if wxUSE_STATUSBAR
    m_child->SetStatusText(s);
#endif // wxUSE_STATUSBAR
}