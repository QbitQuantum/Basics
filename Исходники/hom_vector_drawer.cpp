void
HomVectorDrawer::draw(Cairo::RefPtr<Cairo::Context>& context)
{
  context->save();

  HomPoint start, end;
  if (m_offset)
    {
      start = HomPoint( m_offset->x(), m_offset->y() );
      end   = HomPoint( m_offset->x() + m_vector->x(),
			m_offset->y() + m_vector->y() );
    }
  else
    {
      start = HomPoint( 0.0, 0.0 );
      end   = HomPoint( m_vector->x(), m_vector->y() );
    }

  context->move_to( start.x(), start.y() );
  context->line_to( end.x()  , end.y()   );
  context->arc( end.x(), end.y(), 0.06, 0.0, 2.0 * M_PI);
  context->fill();

  context->stroke();
  context->restore();
}