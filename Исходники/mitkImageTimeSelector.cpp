void mitk::ImageTimeSelector::GenerateOutputInformation()
{
  Image::ConstPointer input  = this->GetInput();
  Image::Pointer output = this->GetOutput();

  itkDebugMacro(<<"GenerateOutputInformation()");

  int dim=(input->GetDimension()<3?input->GetDimension():3);
  output->Initialize(input->GetPixelType(), dim, input->GetDimensions());

  if( (unsigned int) m_TimeNr >= input->GetDimension(3) )
  {
    m_TimeNr = input->GetDimension(3)-1;
  }

  // initialize geometry
  output->SetGeometry(dynamic_cast<Geometry3D*>(input->GetSlicedGeometry(m_TimeNr)->Clone().GetPointer()));
  output->SetPropertyList(input->GetPropertyList()->Clone());  
}