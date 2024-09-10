bool translation::operator<( const translation &that ) const
{
    return translated() < that.translated();
}