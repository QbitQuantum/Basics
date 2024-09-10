 // constructor stores the specified particle index and child pointers (which may be null)
 Node(int m, int depth, Node* left, Node* right) : _m(m), _axis(depth%3), _up(0), _left(left), _right(right)
 {
     if (_left) _left->setParent(this);
     if (_right) _right->setParent(this);
 }