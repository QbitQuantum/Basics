/* The SM does not know anything about the system. This way it can be tested on a
 * different C compiler very easily.
 */
void TrafficLightSM(int event) {
	int NextState = State;
	switch (State) {
	case R_RY:
		switch (event) {
		case TICK:
			NextState = R_G;
			break;
		default:
			break;
		}
		break;
	case R_G:
		switch (event) {
		case TICK:
			NextState = R_Y;
			break;
		default:
			break;
		}
		break;
	case R_Y:
		switch (event) {
		case TICK:
			NextState = RY_R;
			break;
		default:
			break;
		}
		break;
	case RY_R:
		switch (event) {
		case TICK:
			NextState = G_R;
			break;
		default:
			break;
		}
		break;
	case G_R:
		switch (event) {
		case TICK:
			NextState = Y_R;
			break;
		default:
			break;
		}
		break;
	case Y_R:
		switch (event) {
		case TICK:
			NextState = R_RY;
			break;
		default:
			break;
		}
		break;
	default:
		break;
		// The program should never get here !
	}

	if (NextState != State) {
		OnExit(State);
		OnEnter(NextState);
		State = NextState;
	}

	Do(State);
}