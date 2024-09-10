/*
 * dcomp is the sort function called from qsort().  When comparing
 * two device entries we sort by alphabetical order of the device's
 * driver name, then minor number, then block vs. character, then
 * the name of the device entry itself.
 */
static int
dcomp(const void *p1, const void *p2)
{
	struct devices_ent *dep1 = *((struct devices_ent **)p1);
	struct devices_ent *dep2 = *((struct devices_ent **)p2);

	if (dep1->drp->index == dep2->drp->index) {
		if (dep1->minor == dep2->minor) {
			if (dep1->israw == dep2->israw) {
				return (strcoll(dep1->devicename,
				    dep2->devicename));
			} else {
				return (dep1->israw - dep2->israw);
			}
		} else {
			return (dep1->minor - dep2->minor);
		}
	} else {
		return (dep1->drp->index - dep2->drp->index);
	}
}