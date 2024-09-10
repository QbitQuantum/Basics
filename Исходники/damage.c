void Damage::Incur (BoxObj& newb) {
    BoxObj* b;
    Iterator i;

    if (_areas->IsEmpty()) {
	_areas->Prepend(new UList(new BoxObj(&newb)));

    } else if (_areas->First() == _areas->Last()) {
        FirstArea(i);
        b = GetArea(i);
	if (newb.Intersects(*b)) {
	    if (!newb.Within(*b)) {
		*b = *b + newb;
	    }
	} else {
	    _areas->Prepend(new UList(new BoxObj(&newb)));
	}
    } else {
	Merge(newb);
    }
}