                static States predict(const States& x, const Scalar dT) {
                    typedef typename ModelDescription::StateDescription states;
                    States xnext(x);
                    using std::sin; using std::cos;

                    const auto a = 2. * x(states::v) * sin(x(states::w) * dT / 2.) / x(states::w);
                    const auto b = x(states::th) + (x(states::w) * dT / 2.);

                    xnext(states::x) += a*cos(b);
                    xnext(states::y) += a*sin(b);
                    xnext(states::th) += x(states::w)*dT;
                    xnext(states::v) += x(states::a)*dT;
                    return xnext;
                }