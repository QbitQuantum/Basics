    VoroniTessellation (std::map<string, VoroniPoint*> points) : Thing ()
    {
        Text *t = new Text ("Voroni Tessellation with Oblong Greenhouse");
        t->SetTextColor(Color(0.8117, 0.7843, 0.7098));
        t -> SetFontSize (Feld () -> Height () / 40.0);
        t -> SlapOnFeld ();
        t->IncTranslation(Vect(-100,100,0));
        //http://greenhouse.oblong.com/reference/color_methods.html#qr_setalpha
        
        SlapOnFeld();
		Vect feld_loc = Feld()-> Loc ();
        greenhouse_width = ((float)Feld()-> Width() / 2) - 2;
        greenhouse_height = ((float)Feld()-> Height() / 2) - 2;
        
		right = feld_loc.Dot(Feld()-> Over()) + greenhouse_width;
        left = feld_loc.Dot(Feld()-> Over()) - greenhouse_width;
        
        top = feld_loc.Dot (Feld ()-> Up()) + greenhouse_height;
        bottom = feld_loc.Dot (Feld()-> Up()) - greenhouse_height;
        
        #ifdef DEBUG2
        cout<<"\ngreenhouse window dimensions "<<greenhouse_width<<", "<<greenhouse_height<<endl;  // gives (166, 133)
        #endif
        
		moving_points = points;
        num_points = moving_points.size();
    }