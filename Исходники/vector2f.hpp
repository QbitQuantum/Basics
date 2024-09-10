  static Vector2F nan() {
    const IMathUtils* mu = IMathUtils::instance();

    return Vector2F(mu->NanF(),
                    mu->NanF());
  }