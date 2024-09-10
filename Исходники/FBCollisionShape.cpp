	IResult Intersects(const Ray& ray, const Transformation& objT) const{
		if (!mBV)
			return IResult(false, FLT_MAX);
		Ray localRay = objT.ApplyInverse(ray, false);
		Ray::IResult ret = localRay.Intersects(mBV.get());
		return ret;
	}