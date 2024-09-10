 	bool operator()(const arc &A, const arc &B) {
 		if (A.c == B.c) return A.sign < B.sign;
 		return A.val() < B.val();
 	}