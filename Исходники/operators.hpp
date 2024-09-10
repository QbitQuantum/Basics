			operators_found(operators_found &&other) : operators_found() {
				quotes.swap(other.quotes);
				negative.swap(other.negative);
			}