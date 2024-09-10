void
Savable::write (TAO::Storable_Base & stream)
{
  stream.rewind ();

  for (int index = 0; index < 2; ++index)
    {
      stream << this->string_[index];
      stream << this->i_[index];
      stream << this->ui_[index];
      stream << this->bytes_size_[index];
      stream.write (this->bytes_size_[index], this->bytes_[index]);
    }

  stream.flush ();
}