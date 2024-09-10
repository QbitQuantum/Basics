int mtype::get_meat_chunks_count() const
{
    const float ch = to_gram( weight ) * ( 0.40f - 0.02f * log10f( to_gram( weight ) ) );
    const itype *chunk = item::find_type( get_meat_itype() );
    return static_cast<int>( ch / to_gram( chunk->weight ) );
}