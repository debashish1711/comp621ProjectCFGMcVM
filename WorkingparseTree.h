void parseTree(const xmlpp::Node* xml_tree,  NodeData* root,SNode* snd)
{
        
	   NodeData* P=createNode(getType(xml_tree));

	  // P->m_name = xml_tree->get_name();
           P->m_type=getType(xml_tree);
           printf( " Node type   %d\n",P->m_type); 

    
           //cout << "  node name  " << P->m_name;
	   //P->name = xml_tree->name;
	   //P->val = xml_tree->val;

           

        

       /* void SNode::AddChild(SNode* P) 
        {
	root.push_back(P);                            //     root->addChild(P);   
        }*/
        //SyntaxNodeFactory *factory = new SyntaxNodeFactory();
	
     /*   std::ostringstream os;
        SNode* L=SyntaxNodeFactory::the().createNode(P);

        printf(" In the SNode format \n");
        L->printType(os);
        printf("%s\n",os.str().c_str());

        //FlowPoint::FlowPoint( L,os.str().c_str()); 

        std::string xy;

        xy=os.str().c_str();
        CFG *flgraph=new CFG();
        //FlowPoint* M=flgraph->AddFlowPoint(L ,xy);

        Syntax2CFG *chk=new Syntax2CFG(L,*flgraph);
        chk->execute();

       */
        
           
//printf(" The flow point on the CFG \n %s ",flgraph->getName(M).c_str()); 
        
        
        // Creating new childnode for nodeData* 
        appendChild(root, P);

      /* Flow FlowPoint::FlowPoint( SNode* _node, const std::string& _name ) : 
        m_name(_name),
        m_node(_node) */
      

        xmlpp::Node::NodeList list = xml_tree->get_children();
        for(xmlpp::Node::NodeList::iterator iter = list.begin(); iter != list.end(); ++iter)
        {
         parseTree(*iter,P); //recursive
        }
        printf( "  Number of Children %d\n",P->m_childCount);
  } 
	
