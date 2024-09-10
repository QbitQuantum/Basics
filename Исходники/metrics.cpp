void __fastcall TExtPolyline::DrawBezierSeg(void *dc,int n)
{
int n1=(n+1)%Count;
int p1=(n+Count-1)%Count;
POINT pt[3];
pt[0].x=Points[p1].x;
pt[0].y=Points[p1].y;
pt[1].x=Points[n].x;
pt[1].y=Points[n].y;
pt[2].x=Points[n1].x;
pt[2].y=Points[n1].y;
PolyBezierTo(dc,pt,3);
}