	void CreateChildren(UBehaviorTree* BTAsset, UBTCompositeNode* RootNode, const UBehaviorTreeGraphNode* RootEdNode, uint16* ExecutionIndex, uint8 TreeDepth)
	{
		if (RootEdNode == NULL)
		{
			return;
		}

		RootNode->Children.Reset();
		RootNode->Services.Reset();

		// collect services
		if (RootEdNode->Services.Num())
		{
			for (int32 i = 0; i < RootEdNode->Services.Num(); i++)
			{
				UBTService* ServiceInstance = RootEdNode->Services[i] ? Cast<UBTService>(RootEdNode->Services[i]->NodeInstance) : NULL;
				if (ServiceInstance)
				{
					if (Cast<UBehaviorTree>(ServiceInstance->GetOuter()) == NULL)
					{
						ServiceInstance->Rename(NULL, BTAsset);
					}
					ServiceInstance->InitializeNode(RootNode, *ExecutionIndex, 0, TreeDepth);
					*ExecutionIndex += 1;

					RootNode->Services.Add(ServiceInstance);
				}
			}
		}

		// gather all nodes
		int32 ChildIdx = 0;
		for (int32 PinIdx = 0; PinIdx < RootEdNode->Pins.Num(); PinIdx++)
		{
			UEdGraphPin* Pin = RootEdNode->Pins[PinIdx];
			if (Pin->Direction != EGPD_Output)
			{
				continue;
			}

			// sort connections so that they're organized the same as user can see in the editor
			Pin->LinkedTo.Sort(FCompareNodeXLocation());

			for (int32 Index = 0; Index < Pin->LinkedTo.Num(); ++Index)
			{
				UBehaviorTreeGraphNode* GraphNode = Cast<UBehaviorTreeGraphNode>(Pin->LinkedTo[Index]->GetOwningNode());
				if (GraphNode == NULL)
				{
					continue;
				}

				UBTTaskNode* TaskInstance = Cast<UBTTaskNode>(GraphNode->NodeInstance);
				if (TaskInstance && Cast<UBehaviorTree>(TaskInstance->GetOuter()) == NULL)
				{
					TaskInstance->Rename(NULL, BTAsset);
				}

				UBTCompositeNode* CompositeInstance = Cast<UBTCompositeNode>(GraphNode->NodeInstance);
				if (CompositeInstance && Cast<UBehaviorTree>(CompositeInstance->GetOuter()) == NULL)
				{
					CompositeInstance->Rename(NULL, BTAsset);
				}

				if (TaskInstance == NULL && CompositeInstance == NULL)
				{
					continue;
				}

				// collect decorators
				TArray<UBTDecorator*> DecoratorInstances;
				TArray<FBTDecoratorLogic> DecoratorOperations;
				CollectDecorators(BTAsset, GraphNode, DecoratorInstances, DecoratorOperations, true, RootNode, ExecutionIndex, TreeDepth, ChildIdx);

				// store child data
				RootNode->Children.AddZeroed();
				FBTCompositeChild& ChildInfo = RootNode->Children[ChildIdx];
				ChildInfo.ChildComposite = CompositeInstance;
				ChildInfo.ChildTask = TaskInstance;
				ChildInfo.Decorators = DecoratorInstances;
				ChildInfo.DecoratorOps = DecoratorOperations;
				ChildIdx++;

				UBTNode* ChildNode = CompositeInstance ? (UBTNode*)CompositeInstance : (UBTNode*)TaskInstance;
				if (ChildNode && Cast<UBehaviorTree>(ChildNode->GetOuter()) == NULL)
				{
					ChildNode->Rename(NULL, BTAsset);
				}

				InitializeInjectedNodes(GraphNode, RootNode, *ExecutionIndex, TreeDepth, ChildIdx);
				
				// special case: subtrees
				UBTTask_RunBehavior* SubtreeTask = Cast<UBTTask_RunBehavior>(TaskInstance);
				if (SubtreeTask)
				{
					*ExecutionIndex += SubtreeTask->GetInjectedNodesCount();
				}

				ChildNode->InitializeNode(RootNode, *ExecutionIndex, 0, TreeDepth);
				*ExecutionIndex += 1;

				VerifyDecorators(GraphNode);

				if (CompositeInstance)
				{
					CreateChildren(BTAsset, CompositeInstance, GraphNode, ExecutionIndex, TreeDepth + 1);

					CompositeInstance->InitializeComposite((*ExecutionIndex) - 1);
				}
			}
		}
	}