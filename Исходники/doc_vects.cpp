void gigaword_doc_to_vects (
    const std::map<std::string, unsigned long>& words,
    const gigaword_document& doc,
    sparse_vector_type& lhs,
    sparse_vector_type& rhs,
    dlib::rand& rnd
)
{
    lhs.clear();
    rhs.clear();
    istringstream sin(doc.text + " " + doc.headline);
    unigram_tokenizer tok(sin);
    string word;
    while (tok(word))
    {
        const unsigned long id = get_word_id(words, word);
        if (rnd.get_random_float() > 0.5)
        {
            lhs.push_back(make_pair(id, 1));
        }
        else
        {
            rhs.push_back(make_pair(id, 1));
        }
    }

    make_sparse_vector_inplace(lhs);
    make_sparse_vector_inplace(rhs);
}