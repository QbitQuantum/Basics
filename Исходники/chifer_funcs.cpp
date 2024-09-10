bool UserInput::empty() const
{
    return ( 
        history.size() == 0 && 
        min_variants.size() == 0 && 
        Ceil(*this).empty() 
        );
}