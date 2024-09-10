static real_t
nd_prediction (real_t max_costs, real_t price, unsigned band, int y_state,
	       range_t *range, wfa_t *wfa, coding_t *c)
{
   real_t  costs;			/* current approximation costs */
   range_t lrange = *range;
   
   /*
    *  Predict 'range' with DC component approximation
    */
   {
      real_t x = get_ip_image_state (range->image, range->address,
				     range->level, 0, c);
      real_t y = get_ip_state_state (0, 0, range->level, c);
      real_t w = btor (rtob (x / y, c->coeff->dc_rpf), c->coeff->dc_rpf);
      word_t s [2] = {0, -1};

      lrange.into [0] 	     = 0;
      lrange.into [1] 	     = NO_EDGE;
      lrange.weight [0]      = w;
      lrange.mv_coord_bits   = 0;
      lrange.mv_tree_bits    = 0;
      lrange.nd_tree_bits    = tree_bits (LEAF, lrange.level, &c->p_tree);
      lrange.nd_weights_bits = 0;
      lrange.tree_bits       = 0;
      lrange.matrix_bits     = 0;
      lrange.weights_bits    = c->coeff->bits (&w, s, range->level, c->coeff);
   }
   costs = price * (lrange.weights_bits + lrange.nd_tree_bits);
   
   /*
    *  Recursive aproximation of difference image
    */
   if (costs < max_costs)		
   {
      unsigned  state;
      range_t  	rrange;			/* range: recursive subdivision */
      unsigned  last_state;		/* last WFA state before recursion */
      real_t   *ipi [MAXSTATES];	/* inner products pointers */
      unsigned 	width  = width_of_level (range->level);
      unsigned  height = height_of_level (range->level);
      real_t   *pixels;

      /*
       *  Generate difference image original - approximation
       */
      {
	 unsigned  n;
	 real_t *src, *dst;		/* pointers to image data */
	 real_t w = - lrange.weight [0] * c->images_of_state [0][0];
		     
	 src = c->pixels + range->address * size_of_level (range->level); 
	 dst = c->pixels = pixels = Calloc (width * height, sizeof (real_t));

	 for (n = width * height; n; n--)
	    *dst++ = *src++ + w;
      }
      
      /*
       *  Approximate difference recursively.
       */
      rrange                 = *range;
      rrange.tree_bits       = 0;
      rrange.matrix_bits     = 0;
      rrange.weights_bits    = 0;
      rrange.mv_coord_bits   = 0;
      rrange.mv_tree_bits    = 0;
      rrange.nd_tree_bits    = 0;
      rrange.nd_weights_bits = 0;
      rrange.image           = 0;
      rrange.address         = 0;

      last_state = wfa->states - 1;
      for (state = 0; state <= last_state; state++)
	 if (need_image (state, wfa))
	 {
	    ipi [state] = c->ip_images_state[state];
	    c->ip_images_state[state]
	       = Calloc (size_of_tree (c->products_level), sizeof (real_t));
	 }
      
      compute_ip_images_state (rrange.image, rrange.address, rrange.level,
			       1, 0, wfa, c);
      
      costs += subdivide (max_costs - costs, band, y_state, &rrange, wfa, c,
			  NO, YES);
      
      Free (pixels);

      if (costs < max_costs && ischild (rrange.tree)) /* use prediction */
      {
	 unsigned img, adr;
	 unsigned edge;

	 img                     = range->image;
	 adr                     = range->address;
	 *range                  = rrange;
	 range->image            = img;
	 range->address          = adr;
	 range->nd_tree_bits    += lrange.nd_tree_bits;
	 range->nd_weights_bits += lrange.weights_bits;
	 
	 for (edge = 0; isedge (lrange.into [edge]); edge++)
	 {
	    range->into [edge]   = lrange.into [edge];
	    range->weight [edge] = lrange.weight [edge];
	 }
	 range->into [edge] = NO_EDGE;
	 range->prediction  = edge;

	 for (state = last_state + 1; state < wfa->states; state++)
	    if (need_image (state, wfa))
	       memset (c->ip_images_state [state], 0,
		       size_of_tree (c->products_level) * sizeof (real_t));
      }
      else
	 costs = MAXCOSTS;
      
      for (state = 0; state <= last_state; state++)
	 if (need_image (state, wfa))
	 {
	    Free (c->ip_images_state [state]);
	    c->ip_images_state [state] = ipi [state];
	 }
   }
   else
      costs = MAXCOSTS;

   return costs;
}