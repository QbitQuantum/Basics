node<P> batch_insert(const DistanceCallback& dcb, const P& p,
		int max_scale, 
		int top_scale,
		v_array<ds_node<P> >& point_set, 
		v_array<ds_node<P> >& consumed_set,
		v_array<v_array<ds_node<P> > >& stack)
{
	if (point_set.index == 0) 
		return new_leaf(p);
	else {
		DefaultScalarType max_dist = max_set(point_set); //O(|point_set|)
		int next_scale = min(max_scale - 1, get_scale(max_dist));
		if (next_scale == -2147483647-1) // We have points with distance 0.
		{
			v_array<node<P> > children;
			push(children,new_leaf(p));
			while (point_set.index > 0)
			{
				push(children,new_leaf(point_set.last().p));
				push(consumed_set,point_set.last());
				point_set.decr();
			}
			node<P> n = new_node(p);
			n.scale = 100; // A magic number meant to be larger than all scales.  
			n.max_dist = 0;
			alloc(children,children.index);
			n.num_children = children.index;
			n.children = children.elements;
			return n;
		}
		else
		{
			v_array<ds_node<P> > far = pop(stack);
			split(point_set,far,max_scale); //O(|point_set|)

			node<P> child = batch_insert(dcb, p, next_scale, top_scale, point_set, consumed_set, stack);

			if (point_set.index == 0)
			{
				push(stack,point_set);
				point_set=far;
				return child;
			}
			else {
				node<P> n = new_node(p);
				v_array<node<P> > children;
				push(children, child);
				v_array<ds_node<P> > new_point_set = pop(stack);
				v_array<ds_node<P> > new_consumed_set = pop(stack);
				while (point_set.index != 0) { //O(|point_set| * num_children)
					P new_point = point_set.last().p;
					DefaultScalarType new_dist = point_set.last().dist.last();
					push(consumed_set, point_set.last());
					point_set.decr();

					dist_split(dcb,point_set,new_point_set,new_point,max_scale); //O(|point_saet|)
					dist_split(dcb,far,new_point_set,new_point,max_scale); //O(|far|)

					node<P> new_child = 
						batch_insert(dcb, new_point, next_scale, top_scale, new_point_set, new_consumed_set, stack);
					new_child.parent_dist = new_dist;

					push(children, new_child);

					DefaultScalarType fmax = dist_of_scale(max_scale);
					for(int i = 0; i< new_point_set.index; i++) //O(|new_point_set|)
					{
						new_point_set[i].dist.decr();
						if (new_point_set[i].dist.last() <= fmax)
							push(point_set, new_point_set[i]);
						else
							push(far, new_point_set[i]);
					}
					for(int i = 0; i< new_consumed_set.index; i++) //O(|new_point_set|)
					{
						new_consumed_set[i].dist.decr();
						push(consumed_set, new_consumed_set[i]);
					}
					new_point_set.index = 0;
					new_consumed_set.index = 0;
				}
				push(stack,new_point_set);
				push(stack,new_consumed_set);
				push(stack,point_set);
				point_set=far;
				n.scale = top_scale - max_scale;
				n.max_dist = max_set(consumed_set);
				alloc(children,children.index);
				n.num_children = children.index;
				n.children = children.elements;
				return n;
			}
		}
	}
}