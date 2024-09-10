//////////////////////////////////////////////////////////////////////////////
/// @brief
/// Returns if the string can be matched to an expression
///
/// @param input The string to be matched to a regex
/// @param expression The regex expression
///
/// @return bool 
//////////////////////////////////////////////////////////////////////////////
bool Selector::check_in_selection( const std::string & input )
{
    // The function pointer type of the overloaded match_regex we will use
    // for matching.
    typedef bool (*Regex_match_ptr)( const string &, const regex &,
        match_flag_type);

    // Set match flag to full match or partial match, whatever was selected.
    match_flag_type match_type = match_default;
  
    if ( !is_and_match )
    {  
        // Check regex_match(input, ith expression, match_type) matches any 
        // of the expressions in selection list. We must cast regex_match to the 
        // overloaded function pointer type we are using.
        return ( find_if( regex_selections.begin(), regex_selections.end(), 
            bind( static_cast<Regex_match_ptr>( regex_match ), input, _1, 
                match_type ) ) != regex_selections.end() );
    }
    else
    {
        return ( count_if( regex_selections.begin(), regex_selections.end(),
            bind( static_cast<Regex_match_ptr>( regex_match ), input, _1,
                match_type ) ) == regex_selections.size() ); 
    }

} // End of Selector::check_in_selection( ... )