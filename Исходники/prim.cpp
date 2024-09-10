void
UsdPrim::Unload() const
{
    _GetStage()->Unload(GetPath());
}