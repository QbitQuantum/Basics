/*
** This is called once at the start.
*/
void sfnts_start(TTStreamWriter& stream)
{
    stream.puts("/sfnts[<");
    in_string=TRUE;
    string_len=0;
    line_len=8;
} /* end of sfnts_start() */