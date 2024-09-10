//---------------------------------------------------------------------------
void TPolFuncFrame::SetPoint(const TGraphElem *Elem, int X, int Y)
{
  if(const TPolFunc *Func = dynamic_cast<const TPolFunc*>(Elem))
  {
    TTraceType TraceType;
    switch(ComboBox1->ItemIndex)
    {
      case 0: TraceType = ttTrace;        break;
      case 1: TraceType = ttIntersection; break;
      case 2: TraceType = ttXAxis;        break;
      case 3: TraceType = ttYAxis;        break;
      case 4: TraceType = ttExtremeX;     break;
      case 5: TraceType = ttExtremeY;     break;
    }

    double t = TraceFunction(Func, TraceType, X, Y, Form1->Data, Form1->Draw);
    if(_isnan(t))
      Edit1->Text = "";
    else
      Edit1->Text = RoundToStr(t, ComboBox1->ItemIndex == 0 ? Property.RoundTo : std::max(8, Property.RoundTo));
  }
}