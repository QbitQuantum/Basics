 virtual bool equals(const typename base::type& other) const {
     bool result = false;
     // not trying to compare exceptions
     other->accept(make_subscriber<T>(make_observer_dynamic<T>([](T) {}, [&result](std::exception_ptr) {
         result = true;
     })));
     return result;
 }