			inline Vector2d Vector2d::normalized() const
			{
				Vector2d toReturn = *this;

				toReturn.normalize();

				return toReturn;
			}