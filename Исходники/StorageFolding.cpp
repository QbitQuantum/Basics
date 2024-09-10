int count_producers(Stmt in, const std::string &name) {
    CountProducers counter(name);
    in.accept(&counter);
    return counter.count;
}