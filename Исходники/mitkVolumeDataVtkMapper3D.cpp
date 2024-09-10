mitk::Image::Pointer mitk::VolumeDataVtkMapper3D::GetMask()
{
  if (this->m_Mask)
  {
    Image::Pointer mask = Image::New();

    mask->Initialize(this->m_Mask);
    mask->SetImportVolume(this->m_Mask->GetScalarPointer(), 0, 0, Image::ReferenceMemory);
    mask->SetGeometry(this->GetInput()->GetGeometry());
    return mask;
  }

  return 0;
}