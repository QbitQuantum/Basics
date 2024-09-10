Collision * CircleVsCircle(Circle * A , Circle * B)
{
  Vec2 normal = Vector( A->center  , B->center );          // Wektor od A do B

  if(normal.square_value() > square(A->radius + B->radius ) )
  return NULL;

  Collision * c = new Collision ;

  c->A = A->body;
  c->B = B->body;


  float d = normal.value();            // Obliczamy odleg³oœæ kó³ ( g³upi pierwiastek :( )
 
  if(d != 0)                           // Jeœli odleg³oœæ nie wynosi zero
  {
    c->penetration = A->radius +  B->radius - d;  // Obliczamy penetracje i j¹ zapisujemy do struktury kolizji
 
	normal.normalize();                // Normalizujemy normaln¹

    c->normal = normal;                // zapisujemy do struktury

	c->contacts_num = 1;

	c->contacts[0] = A->center + normal * A->radius ;

    return c;                       // Zwracamy prawdê
  }
  else                                 // Ko³a na tej samej pozycji
  {
    // Jesteœmy w dupie , wybieramy randomowe wartoœci

    if(A->radius > B->radius )    // Chyba lepiej podaæ wiêksz¹ penetracje
    c->penetration = A->radius;
	else
	c->penetration = B->radius;

    c->normal = Vec2( 1, 0 );       //  normalna w prawo Korwin style

	c->contacts_num = 1;

	c->contacts[0] = A->center ;
    
	return c;
  }
}