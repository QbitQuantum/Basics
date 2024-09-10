cTime operator /(cTime left, eeDouble right) {
	return Seconds(left.AsSeconds() / right);
}