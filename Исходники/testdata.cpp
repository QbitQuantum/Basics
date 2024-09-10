NodeData testConstructors() {
    NodeData A;
    assert(A.getToken() == "");
    assert(A.getCount() == 1);
    NodeData B("hello world");
    assert(B.getToken() == "hello world");
    NodeData C(B);
    assert(C.getToken() == "hello world");
    return B;
}