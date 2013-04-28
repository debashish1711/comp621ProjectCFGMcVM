#pragma once
#include "SNode.h"

class SDoWhileNode : public SNode
{
public:
	SDoWhileNode(const NodeData& node): SNode(node)
	{
	}

	virtual ~SDoWhileNode(void);

	virtual bool ShouldCreateEdgeFromChildren() {
		return true;
	}
};
