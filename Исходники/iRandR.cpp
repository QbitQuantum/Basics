/*!
 * \brief get the current settins
 * \returns Nothing
 */
void iRandR::reload() {
   HWND lDesktopHWND_win32 = GetDesktopWindow();
   RECT lDesktopRect_win32;


   DISPLAY_DEVICEW lDisplayDevice_win32;
   lDisplayDevice_win32.cb = sizeof( DISPLAY_DEVICEW );

   GetWindowRect( lDesktopHWND_win32, &lDesktopRect_win32 );

   vScreenWidth_uI  = lDesktopRect_win32.right - lDesktopRect_win32.left;
   vScreenHeight_uI = lDesktopRect_win32.bottom - lDesktopRect_win32.top;

   vCurrentConfig_eD.clear();

   DEVMODEW lSettings_win32;
   lSettings_win32.dmSize = sizeof( DEVMODEW );

   for ( DWORD lDeviceNum_win32 = 0;
         EnumDisplayDevicesW( NULL, lDeviceNum_win32, &lDisplayDevice_win32, 0 );
         ++lDeviceNum_win32 ) {

      DISPLAY_DEVICEW lDisplayDeviceTemp_win32;
      lDisplayDeviceTemp_win32.cb = sizeof( DISPLAY_DEVICEW );

      for ( DWORD lDisplayNum_win32 = 0; EnumDisplayDevicesW(
                  lDisplayDevice_win32.DeviceName, lDisplayNum_win32, &lDisplayDeviceTemp_win32, 0 );
            ++lDisplayNum_win32 ) {
         bool lIsEnabled_B = false;
         bool lIsPrimary_B = false;

         if ( lDisplayDeviceTemp_win32.StateFlags & DISPLAY_DEVICE_ACTIVE )
            lIsEnabled_B = true;

         if ( lDisplayDeviceTemp_win32.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE )
            lIsPrimary_B = true;

         iDisplays lTempDisplay( lDisplayDevice_win32.DeviceName, lIsEnabled_B, lIsPrimary_B );

         lTempDisplay.setDisplayDevice( lDisplayDevice_win32 );

         EnumDisplaySettingsW(
               lDisplayDevice_win32.DeviceName, ENUM_CURRENT_SETTINGS, &lSettings_win32 );
         lTempDisplay.setCurrentSettings( lSettings_win32 );
         lTempDisplay.setCurrentSizeAndPosition( lSettings_win32.dmPelsWidth,
                                                 lSettings_win32.dmPelsHeight,
                                                 lSettings_win32.dmPosition.x,
                                                 lSettings_win32.dmPosition.y,
                                                 lSettings_win32.dmDisplayFrequency );


         for ( DWORD lModeNum_win32 = 0; EnumDisplaySettingsW(
                     lDisplayDevice_win32.DeviceName, lModeNum_win32, &lSettings_win32 );
               lModeNum_win32++ )
            lTempDisplay.addMode( lSettings_win32 );

         vCurrentConfig_eD.push_back( lTempDisplay );
      }
   }
   printRandRStatus();
}