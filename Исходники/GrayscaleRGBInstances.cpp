bool ConvertToRGBColorInstance::ExecuteOn( View& view )
{
   ImageWindow window = view.Window();
   Array<ImageWindow> windows = ImageWindow::AllWindows();
   for ( size_type i = 0; i < windows.Length(); ++i )
      if ( windows[i].Mask() == window && !windows[i].MainView().IsColor() )
         windows[i].RemoveMask();

   AutoViewLock lock( view );

   ImageVariant image = view.Image();

   StandardStatus status;
   image.SetStatusCallback( &status );

   Console().EnableAbort();

   image.SetColorSpace( ColorSpace::RGB );

   return true;
}