    bool intersects(const T& a, const T& b) {
        DisjointSet<T>* sa = this->findSet(a);
        DisjointSet<T>* sb = this->findSet(b);

        return sa->getAncestor() == sb->getAncestor();
    }