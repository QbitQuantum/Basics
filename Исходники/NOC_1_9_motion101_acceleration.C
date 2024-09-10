 void Travail ()
 { // create random acceleration vector
   acceleration = Vect (Random (-1.0, 1.0), Random (-1.0, 1.0), 0);
   acceleration.Scale (0.5);
   // add acceleration
   velocity += acceleration;
   // limit the speed, see Limit method below
   velocity = Limit (velocity, top_speed);
   // update position, translating velocity onto Feld size and orientation
   IncTranslation (MapToFeld (velocity));
   
   // detect bounds
   Vect v = Translation ();
   if (v . Dot (over) > (loc + over * wid / 2.0) . Dot (over))
     IncTranslation (MapToFeld (Vect (-wid, 0, 0)));
   if (v . Dot (over) < (loc - over * wid / 2.0) . Dot (over))
     IncTranslation (MapToFeld (Vect (wid, 0, 0)));
   if (v . Dot (up) > (loc + up * hei / 2.0) . Dot (up))
     IncTranslation (MapToFeld (Vect (0, -hei, 0)));
   if (v . Dot (up) < (loc - up * hei / 2.0) . Dot (up))
     IncTranslation (MapToFeld (Vect (0, hei, 0)));
 }