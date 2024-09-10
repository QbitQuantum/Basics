FVector FGeomEdge::GetWidgetLocation()
{
	FVector dir = (GetParentObject()->VertexPool[ VertexIndices[1] ] - GetParentObject()->VertexPool[ VertexIndices[0] ]);
	const float dist = dir.Size() / 2;
	dir.Normalize();
	const FVector loc = GetParentObject()->VertexPool[ VertexIndices[0] ] + (dir * dist);
	return GetParentObject()->GetActualBrush()->ActorToWorld().TransformPosition( loc );
}