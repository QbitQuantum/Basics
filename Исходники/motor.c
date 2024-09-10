static float update_control_rpm(uint32_t comm_period, float dt)
{
	if (_state.rpm_setpoint <= 0) {
		return nan("");
	}
	if (_state.rpm_setpoint < _params.rpm_min) {
		_state.rpm_setpoint = _params.rpm_min;
	}

	const struct rpmctl_input input = {
		_state.limit_mask,
		dt,
		(float)comm_period_to_rpm(comm_period),
		_state.rpm_setpoint
	};
	return rpmctl_update(&input);
}