int Flu_Wrap_Group :: layout( bool sbVisible, bool doScrollTo, int *measure )
{
  int xx = x()+Fl::box_dx(box()), yy = y()+Fl::box_dy(box()),
    ww = w()-Fl::box_dw(box()), hh = h()-Fl::box_dh(box());

  if( type() == FL_VERTICAL )
    {
      int i, X, Y, maxH, H, col, row, maxW, scrollY;
      Fl_Widget *c;

      scrollbar.type( FL_VERTICAL );

    BEGIN_H:

      X = xx+_offset[0];
      Y = yy+_offset[1] - (sbVisible ? scrollbar.value() : 0);
      maxH = _offset[1];
      H = 0;
      col = 0;
      row = 0;
      scrollY = 0;
      maxW = xx + ww - (sbVisible ? scrollbar.w() : 0);

      for( i = 0; i < group.children(); i++ )
	{
	  c = group.child(i);
	  if( !c->visible() )
	    continue;
	  H = MAX( H, c->h() );
	  if( col == 0 )
	    maxH += H + _spacing[1];
	  if( ( X + c->w() ) > maxW )
	    {
	      Y += H + _spacing[1];
	      scrollY += H + _spacing[1];
	      if( i == group.children()-1 )
		maxH += H + _spacing[1];

	      if( measure )
		{
		  if( xx+_offset[0] <= measure[0] && measure[0] <= xx+c->w()+_offset[0]+_spacing[0] &&
		      Y <= measure[1] && measure[1] <= Y+c->h()+_spacing[1] )
		    return i;
		}
	      else
		c->position( xx+_offset[0], Y );

	      col = 0;
	      row++;
	      H = 0;
	      X = xx+c->w() + _offset[0] + _spacing[0];
	    }
	  else
	    {
	      if( measure )
		{
		  if( X <= measure[0] && measure[0] <= X+c->w()+_spacing[0] &&
		      Y <= measure[1] && measure[1] <= Y+c->h()+_spacing[1] )
		    return i;
		}
	      else
		c->position( X, Y );
	      X += c->w() + _spacing[0];
	      col++;
	    }

	  if( doScrollTo && (c == scrollTo) )
	    {
	      if( scrollY > scrollbar.maximum() )
		scrollY = (int)scrollbar.maximum();
	      ((Fl_Valuator*)&scrollbar)->value( scrollY );
	      scrollTo = NULL;
	      goto BEGIN_H;
	    }

	  // if we exceed the height and the scrollbar is not visible,
	  // then it will soon become visible so we don't need to process anymore
	  if( !measure && !sbVisible && maxH > hh )
	    return 1;
	}

      if( measure )
	return -1;
      else if( maxH > hh )
	{
	  scrollbar.range( 0, maxH-hh );
	  scrollbar.slider_size( MAX( float(scrollbar.h()-(maxH-hh))/float(scrollbar.h()), 0.08f ) );
	  return 1;
	}
      else
	return 0;
    }
  else
    {
      int i, X, Y, W, maxW, maxH, col, row, scrollX;
      Fl_Widget *c;

      scrollbar.type( FL_HORIZONTAL );

    BEGIN_W:

      X = xx+_offset[0] - (sbVisible ? scrollbar.value() : 0);
      Y = yy+_offset[1];
      maxW = _offset[0];
      W = 0;
      col = 0;
      row = 0;
      scrollX = 0;
      maxH = yy + hh - (sbVisible ? scrollbar.h() : 0);

      for( i = 0; i < group.children(); i++ )
	{
	  c = group.child(i);
	  if( !c->visible() )
	    continue;

	  W = MAX( W, c->w() );

	  if( row == 0 )
	    maxW += W + _spacing[0];

	  if( ( Y + c->h() ) > maxH )
	    {
	      X += W + _spacing[0];
	      scrollX += W + _spacing[0];
	      if( i == group.children()-1 )
		maxW += W + _spacing[0];

	      if( measure )
		{
		  if( X <= measure[0] && measure[0] <= X+c->w()+_spacing[0] &&
		      yy+_offset[1] <= measure[1] && measure[1] <= yy+c->h()+_offset[1]+_spacing[1] )
		    return i;
		}
	      else
		c->position( X, yy+_offset[1] );

	      row = 0;
	      col++;
	      W = 0;
	      Y = yy+c->h() + _offset[1] + _spacing[1];
	    }
	  else
	    {
	      if( measure )
		{
		  if( X <= measure[0] && measure[0] <= X+c->w()+_spacing[0] &&
		      Y <= measure[1] && measure[1] <= Y+c->h()+_spacing[1] )
		    return i;
		}
	      else
		c->position( X, Y );
	      Y += c->h() + _spacing[1];
	      row++;
	    }

	  if( doScrollTo && (c == scrollTo) )
	    {
	      if( scrollX > scrollbar.maximum() )
		scrollX = (int)scrollbar.maximum();
	      ((Fl_Valuator*)&scrollbar)->value( scrollX );
	      scrollTo = NULL;
	      goto BEGIN_W;
	    }

	  // if we exceed the width and the scrollbar is not visible,
	  // then it will soon become visible so we don't need to process anymore
	  if( !measure && !sbVisible && maxW > ww )
	    return 1;
	}

      if( measure )
	return -1;
      else if( maxW > ww )
	{
	  scrollbar.range( 0, maxW-ww );
	  scrollbar.slider_size( MAX( float(scrollbar.w()-(maxW-ww))/float(scrollbar.w()), 0.08f ) );
	  return 1;
	}
      else
	return 0;
    }
}