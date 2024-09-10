//---------------------------------------------------------------------------
// Quote
void ZtringListList::Quote_Set (const Ztring &NewQuote)
{
    Quote=NewQuote;
    for (size_type Pos0=0; Pos0<size(); Pos0++)
        operator () (Pos0).Quote_Set(Quote);
}