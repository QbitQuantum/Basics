// ZTimer - ctor
ZTimer::ZTimer( ZSubtask *pZSubtask,
                CWnd     *pWndParent,
                ZMapAct  *pzmaComposite,
                zVIEW    vDialog,
                zSHORT   nOffsetX,
                zSHORT   nOffsetY,
                zKZWDLGXO_Ctrl_DEF *pCtrlDef ) :
        CStatic( ),
        ZMapAct( pZSubtask,             // base class ctor
                 pzmaComposite,
                 pWndParent,
                 this,
                 vDialog,
                 nOffsetX,
                 nOffsetY,
                 pCtrlDef,
                 "Timer" )
{
#ifdef DEBUG_ALL
   TraceLineI( "In ctor for ZTimer", (zLONG) this );
#endif

   m_ulMapActFlags &= ~zMAPACT_FOCUS_ENABLED;

   // Make it a hidden window.
   Attr.Style &= ~(WS_TABSTOP | WS_VISIBLE );
   Attr.Style |= WS_DISABLED;
   Attr.X = 0;
   Attr.Y = 0;
   Attr.W = 0;
   Attr.H = 0;

   // Localize settings from XWD.
   m_lInterval = pCtrlDef->StyleX;
   m_bEnabled = TRUE;
   m_pThread = 0;

// TraceLineI( "Timer interval --> ", m_lInterval );
// TraceLineS( "string interval -> ", pCtrlDef->Text );
// TraceLineI( "Timer enabled ---> ", m_bEnabled );

#ifdef zREMOTE_SERVER
   zCHAR szInterval[ 32 ];

   _ltoa_s( m_lInterval, szInterval );
   SetRemoteZCtrlAttribute( this, "Timer", "Interval", szInterval );
#endif

   CreateZ( );
}