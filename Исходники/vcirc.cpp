void Circle::Hide()
{
   if (!Visible) return;      // no need to hide
   unsigned int TempColor;    // to save current color
   TempColor = getcolor();    // set to current color
   setcolor(getbkcolor());    // set drawing color to background
   Visible = false;
   circle(X, Y, Radius);      // draw in background color to erase
   setcolor(TempColor);       // set color back to current color
};