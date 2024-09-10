    /**
     * Inversion operator, i.e. "this->addBefore( ~this ) == Parent".
     * \note Forces are negated and rotated.
     */
    self operator ~() const {
      return self(this->Parent,
			 (-this->Position) * this->Rotation,
			 invert(this->Rotation),
			 ((AngVelocity % this->Position) - Velocity) * this->Rotation,
			 -AngVelocity,
			 ((AngVelocity * AngVelocity * this->Position) + (value_type(2.0) * AngVelocity) % Velocity + AngAcceleration % this->Position - Acceleration ) * this->Rotation,
			 -AngAcceleration,
			 -Force * this->Rotation,
			 -Torque);
    };