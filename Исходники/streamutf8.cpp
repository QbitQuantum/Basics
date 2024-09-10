//-----------------------------------------------------------------------
void InStmUtf8::Rewind()
{
    stm_->Rewind();
    if(has_bom_)
    {
        // skip byte order mark
        stm_->GetChar();
        stm_->GetChar();
        stm_->GetChar();
    }
}