int main ()
{
  printf ("Results of animation1_test:\n");
  
  try
  {  
    AnimationManager manager;
    
    manager.LoadResource ("data/test.xanim");

    Node::Pointer node = Node::Create (), target1 = Node::Create (), target2 = Node::Create ();
    
    target1->SetName ("target1");
    target2->SetName ("target2");

    target1->BindToParent (*node);

    Animation animation = manager.PlayAnimation ("animation1", *node);
    
    target2->BindToParent (*node);    
    
    printf ("f(0):\n");

    node->Update (TimeValue (2, 1));

    dump (*target1);
    dump (*target2);
    
    printf ("f(1):\n");    
    
    node->Update (TimeValue (3, 1));    
    
    dump (*target1);
    dump (*target2);    
  }
  catch (std::exception& e)
  {
    printf ("%s\n", e.what ());
  }

  return 0;
}