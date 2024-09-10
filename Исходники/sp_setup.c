/**
 * Render a horizontal span of quads
 */
static void
flush_spans(struct setup_context *setup)
{
   const int step = MAX_QUADS;
   const int xleft0 = setup->span.left[0];
   const int xleft1 = setup->span.left[1];
   const int xright0 = setup->span.right[0];
   const int xright1 = setup->span.right[1];
   struct quad_stage *pipe = setup->softpipe->quad.first;

   const int minleft = block_x(MIN2(xleft0, xleft1));
   const int maxright = MAX2(xright0, xright1);
   int x;

   /* process quads in horizontal chunks of 16 */
   for (x = minleft; x < maxright; x += step) {
      unsigned skip_left0 = CLAMP(xleft0 - x, 0, step);
      unsigned skip_left1 = CLAMP(xleft1 - x, 0, step);
      unsigned skip_right0 = CLAMP(x + step - xright0, 0, step);
      unsigned skip_right1 = CLAMP(x + step - xright1, 0, step);
      unsigned lx = x;
      unsigned q = 0;

      unsigned skipmask_left0 = (1U << skip_left0) - 1U;
      unsigned skipmask_left1 = (1U << skip_left1) - 1U;

      /* These calculations fail when step == 32 and skip_right == 0.
       */
      unsigned skipmask_right0 = ~0U << (unsigned)(step - skip_right0);
      unsigned skipmask_right1 = ~0U << (unsigned)(step - skip_right1);

      unsigned mask0 = ~skipmask_left0 & ~skipmask_right0;
      unsigned mask1 = ~skipmask_left1 & ~skipmask_right1;

      if (mask0 | mask1) {
         do {
            unsigned quadmask = (mask0 & 3) | ((mask1 & 3) << 2);
            if (quadmask) {
               setup->quad[q].input.x0 = lx;
               setup->quad[q].input.y0 = setup->span.y;
               setup->quad[q].input.facing = setup->facing;
               setup->quad[q].inout.mask = quadmask;
               setup->quad_ptrs[q] = &setup->quad[q];
               q++;
            }
            mask0 >>= 2;
            mask1 >>= 2;
            lx += 2;
         } while (mask0 | mask1);

         pipe->run( pipe, setup->quad_ptrs, q );
      }
   }


   setup->span.y = 0;
   setup->span.right[0] = 0;
   setup->span.right[1] = 0;
   setup->span.left[0] = 1000000;     /* greater than right[0] */
   setup->span.left[1] = 1000000;     /* greater than right[1] */
}