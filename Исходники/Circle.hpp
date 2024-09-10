 // Draws a filled disk //
 void DrawDisk( const Rgba &color, float innerXRadius, float innerYRadius ) const {
    color.Select();
    DiskRender( color, color, innerXRadius, innerYRadius, false );
 }