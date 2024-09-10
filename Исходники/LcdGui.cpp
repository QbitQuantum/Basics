///////////////////
// Call with -100 .. +100
// e.g:
//#define VMAXCLIMB 4.0
//DrawVarioBar(Vario.toFloat()*100/VMAXCLIMB;)
void DrawVarioBar(int percent) {
  if (percent > 100) percent = 100;
  if (percent < -100) percent = -100;
                
  Lcd.drawRect(VX, VY, VW, VH, BLACK);
  Lcd.drawLine(VBARX, VBARY, VBARX2, VBARY, BLACK);
  
  int filledH = VH*percent/200;
  Lcd.fillRect(VX, VBARY, VW, -filledH, BLACK);
}