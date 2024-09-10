/*
 *  When phis are created, only the sigma and phi operands are inserted into them. Thus, we need to insert V, for which sigmas and phis were created, as incoming value of all
 *  incoming edges that still haven't an operand associated for them
 */
void vSSA::populatePhis(SmallVector<PHINode*, 25> &vssaphi_created, Value *V)
{
	// If any vSSA_PHI was created, iterate over the predecessors of vSSA_PHIs to insert V as an operand from the branches where sigma was not created
	for (SmallVectorImpl<PHINode*>::iterator vit = vssaphi_created.begin(), vend = vssaphi_created.end(); vit != vend; ++vit) {
		PHINode *vssaphi = *vit;
		BasicBlock *BB_parent = vssaphi->getParent();
		
		DenseMap<BasicBlock*, unsigned> howManyTimesIsPred;
		
		// Get how many times each basicblock is predecessor of BB_parent
		for (pred_iterator PI = pred_begin(BB_parent), PE = pred_end(BB_parent); PI != PE; ++PI) {
			BasicBlock *predBB = *PI;
			
			DenseMap<BasicBlock*, unsigned>::iterator mit = howManyTimesIsPred.find(predBB);
			
			if (mit == howManyTimesIsPred.end()) {
				howManyTimesIsPred.insert(std::make_pair(predBB, 1));
			}
			else {
				++mit->second;
			}
		}
		
		unsigned i, e;
		
		// If a predecessor already has incoming values in the vSSA_phi, we don't count them
		for (i = 0, e = vssaphi->getNumIncomingValues(); i < e; ++i) {
			--howManyTimesIsPred[vssaphi->getIncomingBlock(i)];
		}
		
		// Finally, add V as incoming value of predBB as many as necessary
		for (DenseMap<BasicBlock*, unsigned>::iterator mit = howManyTimesIsPred.begin(), mend = howManyTimesIsPred.end(); mit != mend; ++mit) {
			unsigned count;
			BasicBlock *predBB = mit->first;
			
			for (count = mit->second; count > 0; --count) {
				vssaphi->addIncoming(V, predBB);
			}
		}
		
		howManyTimesIsPred.clear();
	}
}