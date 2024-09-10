void Ui::operator()(Ptr<Functor> functor) {
    functor->operator()(std::static_pointer_cast<Ui>(shared_from_this()));
}