SOM_Scope void  SOMLINK ShapePartAdjustViewTypeShapes(ShapePart *somSelf,
                                                       Environment *ev,
                                                       ODFrame* frame)
{
    ShapePartData *somThis = ShapePartGetData(somSelf);
    ShapePartMethodDebug("ShapePart","ShapePartAdjustViewTypeShapes");

    try
    {
      // Call parent
      ShapePart_parent_SimplePart_AdjustViewTypeShapes(somSelf, ev, frame);

      ODFrameFacetIterator* facets = frame->CreateFacetIterator(ev); // Get facets for frame
      ODFacet*    facet            = facets->First(ev);              // Assume 1 facet
      delete facets;

      ODRect rect;
      ODTypeToken viewType = frame->GetViewType(ev);

      // Override SimplePart's behavior only if this is an embedded part displaying as frame.
      if((viewType == somThis->fSession->Tokenize(ev,kODViewAsFrame)) &&
         (!frame->IsRoot(ev)))
      {

         // Set the used and active shape to a circle.
         int         width, height;
         ODRgnHandle hrgnUsedAndActive;
         ODRect      box;

         ODCanvas *canvas = facet->GetCanvas(ev);

#ifdef _PLATFORM_OS2_
         HPS       hps;
         hps = ((ODOS2WindowCanvas*) canvas->GetPlatformCanvas(ev, kODPM))->GetPS(ev); // Obtain a PS
#endif //_PLATFORM_OS2_

         TempODShape frameShape = frame->AcquireFrameShape(ev, canvas); // Get bounding box
         frameShape->GetBoundingBox(ev, &box);                          //  of frame
         width  = FixedToInt(box.right)-FixedToInt(box.left);           // circle to be
         height = abs(FixedToInt(box.top)-FixedToInt(box.bottom));      // constructed

#ifdef _PLATFORM_OS2_
         Point center;
         center.x = width/2;
         center.y = height/2;
         int rad  = (width < height) ? center.x : center.y;             // get radius
         GpiBeginPath(hps,1L);                                          // Define GPI path
         GpiSetCurrentPosition(hps , &center);                          // for circle
         GpiFullArc(hps,DRO_OUTLINE,MAKEFIXED(rad,0));
         GpiEndPath(hps);
         hrgnUsedAndActive = GpiPathToRegion(hps, 1, FPATH_ALTERNATE);  // Convert path to GPI region
         ((ODOS2WindowCanvas *)canvas->GetPlatformCanvas(ev, kODPM))->ReleasePS(ev); // Release the canvas
#elif defined(_PLATFORM_WIN32_)

         hrgnUsedAndActive = CreateEllipticRgn(0,0,width,height);       // region from Ellipse box
#endif //_PLATFORM_WIN32_

         if(hrgnUsedAndActive)
         {
            // Use TempODShape so this object won't have to be released.
            TempODShape usedAndActiveShape = frame->CreateShape(ev);       // create a shape
            usedAndActiveShape->SetRegion(ev, hrgnUsedAndActive);          // assign the region to the shape

            // Set used and active shapes to the newly defined shape
            frame->ChangeUsedShape(ev, usedAndActiveShape, kODNULL);
            if(facet)
            {
              facet->ChangeActiveShape(ev, usedAndActiveShape, kODNULL);
            }
         } // hrgnUsedAndActive
      } // viewtype is frame and frame isn't root
      else
      {
         // Reset used and active shapes to frame shape
         frame->ChangeUsedShape(ev, kODNULL, kODNULL);
         if(facet)
         {
           facet->ChangeActiveShape(ev, kODNULL, kODNULL);
         }

      }
    }
    catch(...)
    {
    }
}