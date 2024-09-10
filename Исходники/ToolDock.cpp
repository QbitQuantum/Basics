//
// Determine the location and bar before which a new bar would be placed
//
int ToolDock::PositionBar( ToolBar *t, wxPoint & pos, wxRect & rect )
{
   struct
   {
      wxRect rect;
      wxSize min;
   } tinfo[ ToolBarCount + 1 ];

   wxRect stack[ ToolBarCount + 1 ];
   wxPoint cpos, lpos;
   int ct, lt = 0;
   int ndx, stkcnt = 0;
   int tindx = -1;
   int cnt = mDockedBars.GetCount();
   int width, height;

   // Get size of our parent since we haven't been sized yet
   GetParent()->GetClientSize( &width, &height );
   width -= toolbarGap;
   height -= toolbarGap;

   // Set initial stack entry to maximum size
   stack[ 0 ].SetX( toolbarGap );
   stack[ 0 ].SetY( toolbarGap );
   stack[ 0 ].SetWidth( width );
   stack[ 0 ].SetHeight( height );

   // Process all docked and visible toolbars
   //
   // Careful...slightly different from above in that we expect to
   // process one more bar than is currently docked (<= in for)
   for( ndx = 0, ct = 0; ndx <= cnt; ndx++, ct++ )
   {
      // We're on the last entry...
      if( ndx == cnt )
      {
         // ...so check to see if the new bar has been placed yet
         if( tindx == -1 )
         {
            // Add the new bars' dimensions to the mix
            tinfo[ ct ].rect = t->GetRect();
            tinfo[ ct ].min = t->GetMinSize();
            tindx = ct;
         }
      }
      else
      {
         // Cache toolbar pointer
         ToolBar *b = (ToolBar *) mDockedBars[ ndx ];

         // Remember current bars' dimensions
         tinfo[ ct ].rect = b->GetRect();
         tinfo[ ct ].min = b->GetSize();

         // Insert the new bar if it hasn't already been done
         if( tindx == -1 )
         {
            wxRect r;

            // Get bar rect and make gap part of it
            r.SetPosition( b->GetParent()->ClientToScreen( b->GetPosition() ) );
            r.SetSize( b->IsResizable() ? b->GetSize() : b->GetSize() );
            r.width += toolbarGap;
            r.height += toolbarGap;

            // Does the location fall within this bar?
            if( r.Contains( pos ) || pos.y <= r.y )
            {
               // Add the new bars' dimensions to the mix
               tinfo[ ct ].rect = t->GetRect();
               tinfo[ ct ].min = t->GetSize();
               tindx = ct;
               ndx--;
            }
         }
      }

      // Get and cache the toolbar sizes
      wxSize sz = tinfo[ ct ].min;
      int tw = sz.GetWidth() + toolbarGap;
      int th = sz.GetHeight() + toolbarGap;

      // Will this one fit in remaining horizontal space?
      if( ( tw > stack[ stkcnt ].GetWidth() ) ||
          ( th > stack[ stkcnt ].GetHeight() ) ) 
      {
         // Destack entries until one is found in which this bar
         // will fit or until we run out of stacked entries
         while( stkcnt > 0 )
         {
            stkcnt--;

            // Get out if it will fit
            if( ( tw <= stack[ stkcnt ].GetWidth() ) &&
                ( th <= stack[ stkcnt ].GetHeight() ) )
            {
               break;
            }
         }
      }

      // The current stack entry position is where the bar
      // will be placed.
      cpos = stack[ stkcnt ].GetPosition();

      // We'll be using at least a portion of this stack entry, so
      // adjust the location and size.  It is possible that these
      // will become zero if this entry and the toolbar have the
      // same height.  This is what we want as it will be destacked
      // in the next iteration.
      stack[ stkcnt ].SetY(      stack[ stkcnt ].GetY()      + th );
      stack[ stkcnt ].SetHeight( stack[ stkcnt ].GetHeight() - th );

      // Calc the next possible horizontal location.
      int x = cpos.x + tw;

      // Add a new stack entry
      stkcnt++;
      stack[ stkcnt ].SetX( x );
      stack[ stkcnt ].SetY( cpos.y );
      stack[ stkcnt ].SetWidth( width - x );
      stack[ stkcnt ].SetHeight( th );

      // Position the previous toolbar
      if( ndx > 0 )
      {
         // Place the unstretched toolbar
         tinfo[ lt ].rect.x = lpos.x;
         tinfo[ lt ].rect.y = lpos.y;
      }

      // Place and stretch the final toolbar
      if( ndx == cnt )
      {
         tinfo[ ct ].rect.x = cpos.x;
         tinfo[ ct ].rect.y = cpos.y;
      }

      // Remember for next iteration
      lt = ct;
      lpos = cpos;
   }

   // Fill in the final position
   rect = tinfo[ tindx ].rect;

   return tindx;
}