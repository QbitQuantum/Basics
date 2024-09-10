void hb_gt_winapi_setKbdState( int iKbdState )
{
   BYTE kbState[ 256 ];

   GetKeyboardState( kbState );

   kbState[ VK_SHIFT ]   = ( iKbdState & HB_GTI_KBD_SHIFT ) ? 0x80 : 0;
   kbState[ VK_CONTROL ] = ( iKbdState & HB_GTI_KBD_CTRL ) ? 0x80 : 0;
   kbState[ VK_MENU ]    = ( iKbdState & HB_GTI_KBD_ALT ) ? 0x80 : 0;
   kbState[ VK_LWIN ]    = ( iKbdState & HB_GTI_KBD_LWIN ) ? 0x80 : 0;
   kbState[ VK_RWIN ]    = ( iKbdState & HB_GTI_KBD_RWIN ) ? 0x80 : 0;
   kbState[ VK_APPS ]    = ( iKbdState & HB_GTI_KBD_MENU ) ? 0x80 : 0;
   kbState[ VK_SCROLL ]  = ( iKbdState & HB_GTI_KBD_SCROLOCK ) ? 0x01 : 0;
   kbState[ VK_NUMLOCK ] = ( iKbdState & HB_GTI_KBD_NUMLOCK ) ? 0x01 : 0;
   kbState[ VK_CAPITAL ] = ( iKbdState & HB_GTI_KBD_CAPSLOCK ) ? 0x01 : 0;
   kbState[ VK_INSERT ]  = ( iKbdState & HB_GTI_KBD_INSERT ) ? 0x01 : 0;

   kbState[ VK_LSHIFT ]   = ( iKbdState & HB_GTI_KBD_LSHIFT ) ? 0x80 : 0;
   kbState[ VK_RSHIFT ]   = ( iKbdState & HB_GTI_KBD_RSHIFT ) ? 0x80 : 0;
   kbState[ VK_LCONTROL ] = ( iKbdState & HB_GTI_KBD_LCTRL ) ? 0x80 : 0;
   kbState[ VK_RCONTROL ] = ( iKbdState & HB_GTI_KBD_RCTRL ) ? 0x80 : 0;
   kbState[ VK_LMENU ]    = ( iKbdState & HB_GTI_KBD_LALT ) ? 0x80 : 0;
   kbState[ VK_RMENU ]    = ( iKbdState & HB_GTI_KBD_RALT ) ? 0x80 : 0;

   SetKeyboardState( kbState );
}