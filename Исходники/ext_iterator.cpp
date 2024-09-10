void f_hphp_recursiveiteratoriterator_next(CObjRef obj) {
  RecursiveIteratorIterator *rii = get_recursiveiteratoriterator(obj);
  unsigned int size = rii->m_iterators.size();
  if (!size) return;
  Object ci = rii->m_iterators[size-1].first;
  if (rii->m_mode == HPHP::q_recursiveiteratoriterator_SELF_FIRST) {
    if (!ci.is<RecursiveDirectoryIterator>()) {
      throw InvalidArgumentException("iterator", "unsupported type");
    }
    RecursiveDirectoryIterator *rdi =
      ci.getTyped<RecursiveDirectoryIterator>();
    String pathName = rdi->getPathName();
    if (f_is_dir(pathName) && !rii->m_iterators[size-1].second) {
      rii->m_iterators[size-1].second = 1;
      RecursiveDirectoryIterator *ii =
        NEW(RecursiveDirectoryIterator)(pathName, rdi->m_flags);
      rii->m_iterators.push_back(std::pair<Object, bool>(ii, 0));
      ii->next();
    } else {
      rdi->next();
      rii->m_iterators[size-1].second = 0;
    }
    if (f_hphp_recursiveiteratoriterator_valid(obj)) return;
    rii->m_iterators.pop_back();
    return f_hphp_recursiveiteratoriterator_next(obj);
  } else if (rii->m_mode == HPHP::q_recursiveiteratoriterator_CHILD_FIRST ||
             rii->m_mode == HPHP::q_recursiveiteratoriterator_LEAVES_ONLY) {
    if (!ci.is<RecursiveDirectoryIterator>()) {
      throw InvalidArgumentException("iterator", "unsupported type");
    }
    RecursiveDirectoryIterator *rdi =
      ci.getTyped<RecursiveDirectoryIterator>();
    String pathName = rdi->getPathName();
    if (pathName.empty()) {
      rii->m_iterators.pop_back();
      return f_hphp_recursiveiteratoriterator_next(obj);
    } else if (f_is_dir(pathName)) {
      if (!rii->m_iterators[size-1].second) {
        rii->m_iterators[size-1].second = 1;
        RecursiveDirectoryIterator *ii =
          NEW(RecursiveDirectoryIterator)(pathName, rdi->m_flags);
        rii->m_iterators.push_back(std::pair<Object, bool>(ii, 0));
        ii->rewind();
        if (f_hphp_recursiveiteratoriterator_valid(obj)) return;
        return f_hphp_recursiveiteratoriterator_next(obj);
      } else {
        // CHILD_FIRST: 0 - drill down; 1 - visit 2 - next
        // LEAVES_ONLY: 0 - drill down; 1 - next
        if (rii->m_mode == HPHP::q_recursiveiteratoriterator_CHILD_FIRST &&
          rii->m_iterators[size-1].second == 1) {
          rii->m_iterators[size-1].second = 2;
          return;
        }
      }
    }
    rii->m_iterators[size-1].second = 0;
    rdi->next();
    if (f_hphp_recursiveiteratoriterator_valid(obj)) return;
    return f_hphp_recursiveiteratoriterator_next(obj);
  } else if (rii->m_mode == HPHP::q_recursiveiteratoriterator_CATCH_GET_CHILD) {
    throw InvalidArgumentException("iterator", "unsupported mode");
  }
  throw InvalidArgumentException("iterator", "unsupported mode");
}