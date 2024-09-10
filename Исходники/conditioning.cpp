		// Denormalize the results. See HZ page 109.
		void UnnormalizerI::Unnormalize(const Mat3 &T1, const Mat3 &T2, Mat3 *H)  {
			*H = T2.inverse() * (*H) * T1;
		}