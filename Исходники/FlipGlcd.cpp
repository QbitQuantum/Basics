void FlipGlcd::glcdDisp(int a, int b)
{
  display.clearDisplay();
  display.setTextSize(1);
  
  display.setCursor(0,0);
  display.print("Steps: ");
  display.setCursor(40,0);
  display.print(a);
    
  display.setCursor(0,15);  
  display.print("Temp: ");
  display.setCursor(40,15);
  display.print(b);
  display.setCursor(60,15);
  display.print("F");  
    
  display.display();
}