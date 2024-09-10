    int
    Constraint_Visitor::visit_and (ETCL_Binary_Expr *binary)
    {
      int return_value = -1;
      ACE_CDR::Boolean result = false;
      ETCL_Constraint *lhs = binary->lhs ();

      /// Call to accept() puts the lhs (or its evaluation) on our queue.
      if (lhs->accept (this) == 0)
        {
          ETCL_Literal_Constraint lhs_result;
          this->queue_.dequeue_head (lhs_result);
          result = (ACE_CDR::Boolean) lhs_result;

          /// Short-circuiting AND.
          if (result == true)
            {
              ETCL_Constraint *rhs = binary->rhs ();

              if (rhs->accept (this) == 0)
              {
                ETCL_Literal_Constraint rhs_result;
                this->queue_.dequeue_head (rhs_result);
                result = (ACE_CDR::Boolean) rhs_result;
                return_value = 0;
              }
            }
          else
            {
              return_value = 0;
            }
        }

      if (return_value == 0)
        {
          this->queue_.enqueue_head (ETCL_Literal_Constraint (result));
        }

      return return_value;
    }