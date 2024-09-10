void MyHeap<Key, Element>::insertItem(const Key& k, const Element& e) {
    heap.push_back(item(k, e));
        
    iterator parent = heap.end() - distance(heap.begin()++, heap.end()) / 2;
    if (parent > heap.end()) {
        parent = heap.begin();
    }
    iterator child = heap.end();
    
    
    while (child->first < parent->first) {
        swap(*child, *parent);
        child = parent;
        parent = child - distance(heap.begin()++, child) / 2;
    }
}