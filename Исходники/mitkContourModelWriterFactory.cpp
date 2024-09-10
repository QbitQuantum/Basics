void ContourModelWriterFactory::UnRegisterOneFactory(void)
{
  ObjectFactoryBase::UnRegisterFactory( GetInstance().GetPointer() );
}