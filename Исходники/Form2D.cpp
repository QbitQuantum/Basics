//---------------------------------------------------------------------------
void TForm2D::DataPrepare()
{
 m_setval = 0;
 m_val_n  = 0;
 AnsiString as;

 //range of grid values must be slightly wider...
 Chart1->LeftAxis->Maximum = m_fnc_max;
 Chart1->LeftAxis->Minimum = m_fnc_min;

 Chart1->Title->Text->Clear();
 Chart1->Title->Text->Add(m_chart_title_text);
 Chart1->LeftAxis->Title->Caption = m_y_axis_title;
 Chart1->BottomAxis->Title->Caption = m_x_axis_title;

 for(int i = 0; i < m_count_of_function_points; i++)
 {
  if (m_horizontal_axis_grid_mode < 2) //0,1 modes
   as.sprintf(m_horizontal_axis_values_format.c_str(), m_horizontal_axis_grid_values[i]);
  else  //mode 2
   as.sprintf(m_horizontal_axis_values_format.c_str(), mp_modified_function[i+m_count_of_function_points]);
   
  Series1->Add(mp_original_function[i], as, clAqua);
  Series2->Add(mp_modified_function[i], as, clRed);
 }

 if (2==m_horizontal_axis_grid_mode)
  UpdateBins();
}