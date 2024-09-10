void SeLct::make_funnel_path ( GsPolygon& path, float radius, float dang, float extclear )
 {
   GS_TRACE1 ( "Entering funnel path..." );

   if ( radius<=0 ) { SeDcdt::make_funnel_path(path); return; }

   path.open ( true );
   path.size ( 0 );

   if ( _path_result==NoPath )
    { GS_TRACE1 ( "No path to compute." );
      return;
    }

   if ( _path_result==TrivialPath )
    { path.push().set((float)_xi,(float)_yi);
      path.push().set((float)_xg,(float)_yg);
      GS_TRACE1 ( "Trivial path computed." );
      return;
    }

   if ( _path_result==LocalPath )
    { GS_TRACE1 ( "Computing local path..." );
      path.push().set((float)_xi,(float)_yi);
      GsArray<GsPnt2>& fp = _ent[0].fp;
      bool top = _ent[0].top;
      if ( !top ) dang=-dang;
      GsVec2 c, v1, v2;
      int k, max = fp.size()-2;
      for ( k=0; k<max; k++ )
       { c = fp[k+1];
         if ( top )
          { v1 = (fp[k]-c).ortho();
            v2 = (c-fp[k+2]).ortho();
          }
         else
          { v1 = (c-fp[k]).ortho();
            v2 = (fp[k+2]-c).ortho();
          }
         path.arc ( c, v1, v2, radius, dang );
       }
      path.push().set((float)_xg,(float)_yg);
      GS_TRACE1 ( "Local path has "<<path.size()<<" vertices." );
      return;
    }

   // ok from now on we are treating the global path search case:
   GS_TRACE1 ( "Computing global path..." );

   // allocate/access used buffers:
   // (we reset autolen to false since this is shared with the optimal search)
   if ( !_fpath ) _fpath = new FunnelPath(false); else { _fpath->size(0); _fpath->autolen=false; }
   if ( !_fdeque ) _fdeque = new FunnelDeque; else _fdeque->init();

   // init auxiliary structures if extra clearance is asked:
   if ( extclear>0 ) _finitextcl ( radius, extclear );

   // check entrances and start funnel:
   _funnelstart ( _fdeque, GsPnt2(_xi,_yi), _channel[0], _fpath, radius, extclear );
   if (_funnelcb) _funnelcb(_fudata);

   // now add remaining vertices of the funnel:
   GS_TRACE1 ( "Running funnel algorithm..." );
   int i, j, max = _channel.size()-1;

   if ( extclear>0 )
    { SeDcdtSymEdge *s;
      float r=radius;
      for ( i=0; i<max; i++ )
       { j=i+1;
         s = (SeDcdtSymEdge*)_channel[j];
         if ( _extcl[j].l=='t' ) // add top vertex
          { r = _extcl[j].r;
            _funneladd ( _fdeque, 't', _fpath, s->nvtx()->p, r ); // add top edge vertex
          }
         else // add bot vertex
          { r = _extcl[j].r;
            _funneladd ( _fdeque, 'b', _fpath, s->vtx()->p, r ); // add bottom edge vertex
          }
        if (_funnelcb) _funnelcb(_fudata);
      }
    }
   else
    { SeDcdtSymEdge *s1, *s2;
      for ( i=0; i<max; i++ )
       { s1 = (SeDcdtSymEdge*)_channel[i];
         s2 = (SeDcdtSymEdge*)_channel[i+1];
         if ( s1->vtx()==s2->vtx() ) // add top vertex
          { GS_TRACE2 ( "Updating funnel top with channel edge "<<(i+1) );
            _funneladd ( _fdeque, 't', _fpath, s2->nvtx()->p, radius ); // add top edge vertex
          }
         else // add bot vertex
          { GS_TRACE2 ( "Updating funnel bottom with channel edge "<<(i+1) );
            _funneladd ( _fdeque, 'b', _fpath, s2->vtx()->p, radius ); // add bottom edge vertex
          }
        if (_funnelcb) _funnelcb(_fudata);
      }
    }

   GS_TRACE1 ( "Path has " << _fpath->size() << " vertices before closure." );
   GS_TRACE1 ( "Processing closure..." );
   _funnelclose ( _fdeque, _fpath, 3, radius );

   // build path approximation based on tangents:
   GS_TRACE1 ( "Building curved path approximation..." );
   _fpathmake ( _fpath, path, radius, dang );

   GS_TRACE1 ( "Done." );
 }