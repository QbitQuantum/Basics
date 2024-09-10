/*
 * Generate the information decribing the output data. The default
 * implementation of this method will copy information from the input to the
 * output. A filter may override this method if its output will have different
 * information than its input. For instance, a filter that shrinks an image will
 * need to provide an implementation for this method that changes the spacing of
 * the pixels. Such filters should call their superclass' implementation of this
 * method prior to changing the information values they need (i.e.
 * GenerateOutputInformation() should call
 * Superclass::GenerateOutputInformation() prior to changing the information.
 */
void mitk::ExtractImageFilter::GenerateOutputInformation()
{
 Image::Pointer output = this->GetOutput();
 Image::ConstPointer input = this->GetInput();
 if (input.IsNull()) return;

 if ( m_SliceDimension >= input->GetDimension() && input->GetDimension() != 2 )
 {
   MITK_ERROR << "mitk::ExtractImageFilter:GenerateOutputInformation  m_SliceDimension == " << m_SliceDimension << " makes no sense with an " << input->GetDimension() << "D image." << std::endl;
   itkExceptionMacro("This is not a sensible value for m_SliceDimension.");
   return;
 }

 unsigned int sliceDimension( m_SliceDimension );
 if ( input->GetDimension() == 2)
 {
   sliceDimension = 2;
 }

  unsigned int tmpDimensions[2];

  switch ( sliceDimension )
  {
    default:
    case 2: 
      // orientation = PlaneGeometry::Axial;
      tmpDimensions[0] = input->GetDimension(0);
      tmpDimensions[1] = input->GetDimension(1);
      break;
    case 1: 
      // orientation = PlaneGeometry::Frontal;
      tmpDimensions[0] = input->GetDimension(0);
      tmpDimensions[1] = input->GetDimension(2);
      break;
    case 0: 
      // orientation = PlaneGeometry::Sagittal;
      tmpDimensions[0] = input->GetDimension(1);
      tmpDimensions[1] = input->GetDimension(2);
      break;
  }

  output->Initialize(input->GetPixelType(), 2, tmpDimensions, 1 /*input->GetNumberOfChannels()*/);

  // initialize the spacing of the output
/*
  Vector3D spacing = input->GetSlicedGeometry()->GetSpacing();
  if(input->GetDimension()>=2)
    spacing[2]=spacing[1];
  else
    spacing[2] = 1.0;
  output->GetSlicedGeometry()->SetSpacing(spacing);
*/

  output->SetPropertyList(input->GetPropertyList()->Clone());
}