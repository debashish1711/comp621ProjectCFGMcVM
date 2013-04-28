#include "stdlib.h"
#include "SyntaxParserInterface.h"
#include <libxml++/libxml++.h>
#include <iostream>
#include <string>
#include "glib.h"
#include "XMLtoAST.cpp"
#include "SyntaxNodeFactory.h"
#include "SNode.h"
#include "SyntaxTree.h"
#include "SNode.h"
#include "FlowPoint.h"
#include "CFG.h"
#include "AST2CFG.h"

#include <glibmm/ustring.h>


//using namespace std;

class SNode;


using namespace std;
using namespace Glib;

//Namespace trySNode{NodeData* p}
      
nodeType getType(const xmlpp::Node* xml_tree)
{
     const Glib::ustring nodename = xml_tree->get_name();
     std::stringstream s;
     //std::cout << " name for nodename" << nodename <<"is in nodedata*";
     
    // std::string node_string=const Glib::locale_from_utf8(*nodename);
    // Glib::ustring myname("Testing");

     //cout<<"Testing with testing "<<myname.compare("testi");
    // cout<<"Testing with testing 2  "<<myname.compare("Testing");
     
     if(nodename.compare("IfStmt") == 0)
     {
     printf("\nIF STATEMENT");
     return SELECTION_STATEMENT;
     }
     else if(nodename.compare("Function")==0)
     {
        printf("\n FUNCTION ");
      return NONE;
     }
     else if(nodename.compare("CompilationUnits")==0)
     {
        printf("\n COMPILATION UNITS");
      return BLOCK;
     }
     else if(nodename.compare("FunctionList")==0)
     {
        printf("\n FUNCTION LIST");
      return BLOCK;
     }
     else if(nodename.compare("LTExpr")==0)
     {
        printf("\n LESS_THAN_EXPR ");
     	return STATEMENT;
     }
     else if(nodename.compare("InputParamList")==0)
     {
         printf("\n PARAM_LIST");
         return PARAM_LIST;
     }
     else if(nodename.compare("WhileStmt")==0)
     {
         printf("\n WHILE_LOOP ");
         return WHILE_LOOP;
     }
     else if(nodename.compare("AssignStmt")==0)
     {
         printf("\n ASSIGNMENT_EXPR STATEMENT");
         return EXPRESSION_STATEMENT ;
     }
     else if(nodename.compare("IfBlock")==0)
     {     
          printf("\n IF ELSE ");
          return COMPOUND_STATEMENT;
     }
     else if(nodename.compare("ElseBlock")==0)
     {     
          printf("\n ELSE ");
          return COMPOUND_STATEMENT;
     }
     else if(nodename.compare("GTExpr")==0)
     {
          printf("\n GREATER_THAN_EXPR ");
          return GREATER_THAN_EXPR;
     }
     else if(nodename.compare("StmtList")==0)
    {
          printf("\n STATEMENT_LIST");
          return STATEMENT_LIST;
    }
     else if(nodename.compare("ForStmt")==0)
     {
           printf("\n FOR_LOOP");
           return FOR_LOOP;
     }
   /* else if(nodename.compare("NameExpr")==TRUE)
     {
           printf("\nNAME EXPRESSION");
           return ID;
     }*/
     else if(nodename.compare("EqExpr")==0)
     {
            printf("\n EQUAL_EXPR ");
            return EQUAL_EXPR;
     }
     else if(nodename.compare("GEExpr")==0)
     {
            printf("\n GREATER_EQ_THAN_EXPR");
            return GREATER_EQ_THAN_EXPR;
     }
     else if(nodename.compare("LEExpr")==0)
     {
            printf("\n LESS_EQ_THAN_EXPR");
            return LESS_EQ_THAN_EXPR;
     }
     else if(nodename.compare("PlusExpr")==0)
     {
            printf("\n ADD_EXPR");
            return ADD_EXPR;
     }
     else if(nodename.compare("MinusExpr")==0)
     {
            printf("\n SUB_EXPR ");
            return SUB_EXPR;
     }
     else if(nodename.compare("AndExpr")==0)
     {
            printf("\n AND_EXPR ");
            return AND_EXPR;
     }
     else if(nodename.compare("NameExpr")==0)
     {
           printf("\nNAME EXPRESSION STATEMENT");
           return EXPRESSION;
     }
      else if(nodename.compare("Expr")==0)
     {
           printf("\nEXPRESSION");
           return EXPRESSION;
     }
     else if(nodename.compare("Name")==0)
     {
        
           printf("\nNAME IDENTIFIER");
           return STATEMENT;    // should be ID
    
      }
}

        

 NodeData* parseTree(const xmlpp::Node* xml_tree)                     //,SNode* snd)
{
      NodeData* P=createNode(getType(xml_tree));  

      // The Code below is an attemp to get the name inside the node name which is of the type ID
      /*const Glib::ustring nodename = xml_tree->get_name();
      if(nodename.compare("Name")==0)
      {
          const xmlpp::Element* nodeElement = dynamic_cast<const xmlpp::Element*>(xml_tree);
        const xmlpp::Element::AttributeList& attributes = nodeElement->get_attributes();
         for(xmlpp::Element::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter)
         {
            
            const xmlpp::Attribute* attribute = *iter;
            const Glib::ustring getname=attribute->get_name();
            

            if(getname.compare("nameID")==0)
            {
               Glib::ustring getval;
              getval=attribute->get_value();
              string someval = getname;
              string someval2(getval.c_str());

              char* chMessage = ( char *)malloc(300);
              strcpy(chMessage,someval2.c_str());
              P->m_name= chMessage;

            }
         }

        

      }*/
      //P->m_type=getType(xml_tree);
      //printf( " Node type   %d\n",P->m_type);  pNode
     // P->m_name = xml_tree->get_name().str().c_str();
     // printf( " Node name   %s\n",P->m_name);                                                                          
      //appendChild(root, P);                                                                         // P->m_name = xml_tree->get_name();
      return P;
} 
	
  

void GenerateNodeTree(NodeData* Parnt, const xmlpp::Node* pNode )
{
                                                
        

         xmlpp::Node::NodeList list = pNode->get_children();
        //printf("Number of children %d\n", getChildsCount();
         
        for(xmlpp::Node::NodeList::iterator iter = list.begin(); iter != list.end(); ++iter)
        {
        const xmlpp::Node* xml_tree=*iter;  
        const Glib::ustring nodename = xml_tree->get_name();
        const xmlpp::ContentNode* nodeContent = dynamic_cast<const xmlpp::ContentNode*>(*iter);
        const xmlpp::TextNode* nodeText = dynamic_cast<const xmlpp::TextNode*>(*iter);
        const xmlpp::CommentNode* nodeComment = dynamic_cast<const xmlpp::CommentNode*>(*iter);
          if(!nodeText && !nodeComment && !nodename.empty()) //Let's not say "name: text".
          {
          
         
         NodeData* chld=parseTree(*iter); //recursive    // The node for node* assigned to NodeData* 
         
         
         SNode* sn=new SNode(*Parnt);
         
         size_t level=2;
        // sn->print(os,level);
         appendChild(Parnt, chld);
        printf("Number of children %d\n", getChildsCount(Parnt));
       // std::cout << os.str().c_str();

           
                                                                       //  printf("working3!!");
         CFG* flgraph=new CFG();
                                                                       //  printf("working0!!");
         AST2CFG* chk=new AST2CFG(sn,*flgraph);     
                                                                       //   printf("working1!!");
         chk->execute();
         std::cout<< "The Flow graph \n";
         std::ostringstream os;                             //      printf("working2!!");
         flgraph->printForDot(os);
                                                                       //     printf("working!!");
         
        // flgraph->printForDot();
        std::cout << os.str().c_str();
         GenerateNodeTree(chld,*iter);
         }
        }                                                      // Call the parsetree to create NodeData*
      
      return;
}


int main(int argc, char* argv[])
{
  // Set the global C++ locale to the user-configured locale,
  // so we can use std::cout with UTF-8, via Glib::ustring, without exceptions.
  std::locale::global(std::locale(""));

  bool validate = false;
  bool set_throw_messages = false;
  bool throw_messages = false;
  bool substitute_entities = true;

  int argi = 1;
  while (argc > argi && *argv[argi] == '-') // option
  {
    switch (*(argv[argi]+1))
    {
      case 'v':
        validate = true;
        break;
      case 't':
       set_throw_messages = true;
       throw_messages = true;
       break;
      case 'e':
       set_throw_messages = true;
       throw_messages = false;
       break;
      case 'E':
        substitute_entities = false;
        break;
     default:
       std::cout << "Usage: " << argv[0] << " [-v] [-t] [-e] [filename]" << std::endl
                 << "       -v  Validate" << std::endl
                 << "       -t  Throw messages in an exception" << std::endl
                 << "       -e  Write messages to stderr" << std::endl
                 << "       -E  Do not substitute entities" << std::endl;
       return EXIT_FAILURE;
     }
     argi++;
  }
  std::string filepath;
  if(argc > argi)
    filepath = argv[argi]; //Allow the user to specify a different XML file to parse.
  else
    filepath = "example.xml";
 
  try
  {
    xmlpp::DomParser parser;
    if (validate)
      parser.set_validate();
    //We can have the text resolved/unescaped automatically.
    parser.set_substitute_entities(substitute_entities);
    parser.parse_file(filepath);
   // NodeData* Parnt=createNode(BLOCK);
   // SNode* Orig=SyntaxNodeFactory::the().createNode(Root);
   
    //cout << Parnt->m_name ;
    if(parser)
    {
      //Walk the tree:
     
         
      const xmlpp::Node* pNode = parser.get_document()->get_root_node();           // Create a root node of type Node*  
      NodeData* root=parseTree(pNode);   
       
      GenerateNodeTree(root,pNode);

      SNode* sn=new SNode(*root);

      printf("root is coming");
      //printf("Number of children of root %d\n", getChildsCount(root));
       
      
                                        // Call the parsetree to create NodeData*
      std::ostringstream ost;
         size_t level=20;
        printf("Printing the root in main");
         sn->print(ost,level);
         std::cout << ost.str().c_str();

       std::ostringstream osr;
    /// Create an instance of the CFG class
       CFG* flgraph=new CFG();                  
        std::vector<SNode*> m_children;
        m_children=sn->children();
        size_t nChilds = m_children.size();
      for(size_t i = 0; i < nChilds; i++) {
       /*  if (m_Parent)  {
      for(size_t j = 0; j < level+1; j++) {
        if (j == level)
        {
          ostr << ("|---");
        }
        else
        {
          ostr << ("    ");
        }
      }
    }*/
    //  m_children[i]->print(ostr, level+1);
     //std::ostringstream os;
     // CFG* flgraph=new CFG();
      AST2CFG* chk2=new AST2CFG(m_children[i],*flgraph);
      chk2->execute();
      std::cout<< "The Flow graph is\n"; 
      flgraph->printForDot(osr);
      
      std::cout << osr.str().c_str();
  }

                                        // Call the parsetree to create NodeData*
      std::ostringstream os;
      //CFG* flgraph=new CFG();
      AST2CFG* chk=new AST2CFG(sn,*flgraph);
      chk->execute();
      std::cout<< "The Flow graph is\n"; 
      flgraph->printForDot(os);
      
      std::cout << os.str().c_str();
        
     // parseTree(pNode,Root);
    //  SNode* SyntaxNodeFactory::createNode(NodeData* n);
      //print_node(pNode);
    }
    
  }
  catch(const std::exception& ex)
  {
    std::cerr << "Exception caught: " << ex.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}








