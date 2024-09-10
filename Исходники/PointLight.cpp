void PointLight::operator()(Ptr<Functor> functor) {
    functor->operator()(std::static_pointer_cast<PointLight>(shared_from_this()));
}