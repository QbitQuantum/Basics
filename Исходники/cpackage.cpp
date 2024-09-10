void C_ATO_Package::Refresh()
{
    if(!Ready() || Flags_ & C_BIT_INVISIBLE || Parent_ == NULL)
        return;

    Parent_->SetUpdateRect(GetX(),GetY(),GetX()+GetW(),GetY()+GetH(),Flags_,GetClient());
}