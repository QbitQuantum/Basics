void
TAO::PG_Group_List_Store::read (TAO::Storable_Base & stream)
{
  group_ids_.clear ();

  stream.rewind ();

  unsigned int next_group_id;
  stream >> next_group_id;
  this->next_group_id_ = next_group_id;

  int size;
  stream >> size;

  // TODO: Look at adding streaming of unsigned long long
  // PortableGroup::ObjectGroupId group_id;
  int group_id;
  for (int i = 0; i < size; ++i)
    {
      stream >> group_id;
      group_ids_.insert (group_id);
    }
}