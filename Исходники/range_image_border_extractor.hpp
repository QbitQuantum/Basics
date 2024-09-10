float RangeImageBorderExtractor::updatedScoreAccordingToNeighborValues(int x, int y, const float* border_scores) const
{
  float max_score_bonus = 0.5f;
  
  float border_score = border_scores[y*range_image_->width+x];
  
  // Check if an update can bring the score to a value higher than the minimum
  if (border_score + max_score_bonus*(1.0f-border_score) < parameters_.minimum_border_probability)
    return border_score;
  
  float average_neighbor_score=0.0f, weight_sum=0.0f;
  for (int y2=y-1; y2<=y+1; ++y2)
  {
    for (int x2=x-1; x2<=x+1; ++x2)
    {
      if (!range_image_->isInImage(x2, y2) || (x2==x&&y2==y))
        continue;
      average_neighbor_score += border_scores[y2*range_image_->width+x2];
      weight_sum += 1.0f;
    }
  }
  average_neighbor_score /=weight_sum;
  
  if (average_neighbor_score*border_score < 0.0f)
    return border_score;
  
  float new_border_score = border_score + max_score_bonus * average_neighbor_score * (1.0f-fabsf(border_score));
  
  //std::cout << PVARC(border_score)<<PVARN(new_border_score);
  return new_border_score;
}