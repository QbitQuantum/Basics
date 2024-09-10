void ToolManager::Reset()
{
   // Disconnect all docked bars
   for ( const auto &entry : DefaultConfigTable )
   {
      int ndx = entry.barID;
      ToolBar *bar = mBars[ ndx ].get();

      ToolBarConfiguration::Position position {
         (entry.rightOf == NoBarID) ? nullptr : mBars[ entry.rightOf ].get(),
         (entry.below == NoBarID) ? nullptr : mBars[ entry.below ].get()
      };

      wxWindow *floater;
      ToolDock *dock;
      bool expose = true;

      // Disconnect the bar
      if( bar->IsDocked() )
      {
         bar->GetDock()->Undock( bar );
         floater = NULL;
      }
      else
      {
         floater = bar->GetParent();
      }

      if (ndx == SelectionBarID 
#ifdef EXPERIMENTAL_SPECTRAL_EDITING
         || ndx == SpectralSelectionBarID
#endif
         )
      {
         dock = mBotDock;

         wxCommandEvent e;
         bar->GetEventHandler()->ProcessEvent(e);
      }
      else
      {
         dock = mTopDock;
         bar->ReCreateButtons();
      }

      bar->EnableDisableButtons();
#if 0
      if( bar->IsResizable() )
      {
         bar->SetSize(bar->GetBestFittingSize());
      }
#endif

      if( ndx == MeterBarID
#ifdef EXPERIMENTAL_SPECTRAL_EDITING
         || ndx == SpectralSelectionBarID
#endif
         || ndx == ScrubbingBarID
         )
      {
         expose = false;
      }

      if( dock != NULL )
      {
         // when we dock, we reparent, so bar is no longer a child of floater.
         dock->Dock( bar, false, position );
         Expose( ndx, expose );
         //OK (and good) to DELETE floater, as bar is no longer in it.
         if( floater )
            floater->Destroy();
      }
      else
      {
         // The (tool)bar has a dragger window round it, the floater.
         // in turn floater will have mParent (the entire App) as its
         // parent.

         // Maybe construct a NEW floater
         // this happens if we have just been bounced out of a dock.
         if( floater == NULL ) {
            wxASSERT(mParent);
            floater = safenew ToolFrame( mParent, this, bar, wxPoint(-1,-1) );
            bar->Reparent( floater );
         }

         // This bar is undocked and invisible.
         // We are doing a reset toolbars, so even the invisible undocked bars should
         // be moved somewhere sensible. Put bar near center of window.
         // If there were multiple hidden toobars the ndx * 10 adjustment means 
         // they won't overlap too much.
         floater->CentreOnParent( );
         floater->Move( floater->GetPosition() + wxSize( ndx * 10 - 200, ndx * 10 ));
         bar->SetDocked( NULL, false );
         Expose( ndx, false );
      }

   }
   // TODO:??
   // If audio was playing, we stopped the VU meters,
   // It would be nice to show them again, but hardly essential as
   // they will show up again on the next play.
   // SetVUMeters(AudacityProject *p);
   LayoutToolBars();
   Updated();
}