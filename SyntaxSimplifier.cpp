#include "SyntaxSimplifier.h"
#include "SNode.h"

SyntaxSimplifier::SyntaxSimplifier(SNode* root) : m_root(root)
{
}

SyntaxSimplifier::~SyntaxSimplifier(void)
{
}

void SyntaxSimplifier::execute()
{
	reduceChildren(m_root);
	expandForLoops(m_root);
}

void SyntaxSimplifier::reduceChildren(SNode* node)
{
	std::vector<SNode*> children = node->children();      //node->children returns m_children
	size_t nChilds = children.size();                      
	for (size_t i = 0; i < nChilds; ++i) {
		reduceChildren(children[i]);
	}

	if (node->parent() && node->ShouldBeReduced()) {
		std::vector<SNode*>::iterator it = node->parent()->childIter(node);
		std::vector<SNode*>::iterator it1=node->children().begin();
                std::vector<SNode*>::iterator it2=node->children().end();   //Store all the children of node in parent and remove node
                node->parent()->AddChildren(it, it1, it2);
		for (size_t i = 0; i < node->children().size(); ++i) {
			node->children()[i]->SetParent(node->parent());
		}
		node->parent()->RemoveChild(node);
		node->children().clear();
		delete node;
	}
}

//TODO: I think this part is redundant, need to test this and remove function
// if it is so.
void SyntaxSimplifier::expandForLoops(SNode* node)
{
	std::vector<SNode*> children = node->children();
	size_t nChilds = children.size();
	for (size_t i = 0; i < nChilds; ++i) {
		expandForLoops(children[i]);
	}

	if (node->Type() == FOR_LOOP && node->parent())
	{
		//insert statement node instead of the for loop node, with the for loop
		//a single child under it.
		std::vector<SNode*>::iterator it = node->parent()->childIter(node);
		SNode* statement = new SNode(STATEMENT);
		statement->SetParent(node->parent());
		(*it) = statement;
		statement->children().push_back(node);
	}
}


