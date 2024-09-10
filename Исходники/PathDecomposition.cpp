htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::rememberedVertices(htd::vertex_t vertex, htd::vertex_t child) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    if (isVertex(vertex) && isChild(vertex, child))
    {
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);
        const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child);

        std::set_intersection(bag.begin(), bag.end(), childBag.begin(), childBag.end(), std::back_inserter(result));
    }
    else
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::rememberedVertices(htd::vertex_t, htd::vertex_t) const");
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}