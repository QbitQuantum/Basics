char ASCIIShade(double x)
{
  if(IsNaN(x)) return 'E';
  if(IsInf(x)==1) return 'I';
  else if(IsInf(x)==-1) return 'i';
  int index = (int)Trunc(x*8) + 7;
  if(index < 0) index=0;
  if(index >= kNumAsciiShades) index=kNumAsciiShades-1;
  if(index == 7) {
    if(x > 0) return kAsciiShades[8];
    else if(x < 0) return kAsciiShades[6];
    else return kAsciiShades[7];
  }
  return kAsciiShades[index];
}