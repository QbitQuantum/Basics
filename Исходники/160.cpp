    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
		int lena = 0;
		int lenb = 0;
		ListNode* tempa = headA;
		ListNode* tempb = headB;
		while (tempa) {
			lena++;
			tempa = tempa->next;
		}
		while (tempb) {
			lenb++;
			tempb = tempb->next;
		}
		int diff = abs(lena - lenb);
		while (diff--) {
			if (lena > lenb) {
				headA = headA->next;
			} else {
				headB = headB->next;
			}
		}
		while (headA and headB) {
			if (headA == headB) return headA;
			headA = headA->next;
			headB = headB->next;
		}
		return NULL;
    }