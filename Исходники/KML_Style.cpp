void
KML_Style::scan( const Config& conf, KMLContext& cx )
{
    Style style( conf.value("id") );

    KML_IconStyle icon;
    icon.scan( conf.child("iconstyle"), style, cx );

    KML_LabelStyle label;
    label.scan( conf.child("labelstyle"), style, cx );

    KML_LineStyle line;
    line.scan( conf.child("linestyle"), style, cx );

    KML_PolyStyle poly;
    poly.scan( conf.child("polystyle"), style, cx );

    cx._sheet->addStyle( style );

    cx._activeStyle = style;
}