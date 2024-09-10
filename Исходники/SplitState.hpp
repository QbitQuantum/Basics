 TokenSplitPolicy(IHypergraph<Arc> const& hg, Util::Utf8RangePred pred, bool spaceBetween)
     : hg_(hg), pVoc_(hg.getVocabulary()), pred_(pred), spaceBetween_(spaceBetween) {
   assert(hg.isGraph());
   assert(hg.hasAtMostOneLexicalTail());
 }