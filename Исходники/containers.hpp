 void swap(stable_priority_queue<Type> &that) {
     using std::swap;
     swap(sequence_, that.sequence_);
     swap(compare_, that.compare_);
     swap(heap_, that.heap_);
 }