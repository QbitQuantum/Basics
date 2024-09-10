/**
 * Funkcja, która finalizuje wczytywanie słowa i wypisuje o nim informacje.
 * Na standardowe wyjście słowo zostaje przepisane, lub przepisane poprzedzone
 * znakiem '#', jeśli go nie znaleziono w słowniku.
 * Jeśli w 'pstate' ustawiony jest tryb "verbose", wypisywane są również
 * dodatkowe informacje o podpowiedziach na wyjście błędów.
 * @param [in,out] pstate Stan parsera. Zostanie uaktualniona jedynie pozycja
 * w buforze.
 */
void process_word(struct parser_state * pstate)
{
    // finalizing buffer iterator
    *pstate->buffer_iterator = L'\0';
    pstate->buffer_iterator = word_buffer;

    // word for dictionary
    make_lower(word_buffer, word_buffer_lowered);

    // true position of the word
    int word_column_num = pstate->last_non_word_column_num + 1;

    // getting data from dictionary and printing it
    const bool is_in_dict = dictionary_find(pstate->dict, word_buffer_lowered);
    if (!is_in_dict && pstate->verbose)
    {
        {
            struct word_list wlist;
            dictionary_hints(pstate->dict, word_buffer_lowered, &wlist);
            print_verbose_info(pstate, word_column_num, &wlist, stderr);
        }
        fputwc(L'#', stdout);
    }
    fputws(word_buffer, stdout);
}