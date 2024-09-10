Physics::State Physics::interpolate(const State &a, const State &b, float alpha)
{
	State state = b;
	state._position = a._position*(1-alpha) + b._position*alpha;							//alpha needs to be checked for errors. it is currently doing 1-1 no matter what.
	state._momentum = a._momentum*(1-alpha) + b._momentum*alpha;
	state._orientation = slerp(a._orientation, b._orientation, alpha);
	state._angularMomentum = a._angularMomentum*(1-alpha) + b._angularMomentum*alpha;
	state.recalculate();
	return state;
}