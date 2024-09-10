	inline Vector2F SFMLToRedVector2F(const sf::Vector2<T> &pVec){
		return Vector2F(static_cast<f32>(pVec.x), static_cast<f32>(pVec.y));
	}