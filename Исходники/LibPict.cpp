PCT_BEG

LibPictmancer::LibPictmancer()
{
  HRESULT hr = DWriteCreateFactory(
    DWRITE_FACTORY_TYPE_SHARED,
    _WriteFactory.IID(),
    &_WriteFactory
    );


  auto type = D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_MULTI_THREADED;
  hr = D2D1CreateFactory(
    type,
    _Factory.IID(),
    &_Factory );
}