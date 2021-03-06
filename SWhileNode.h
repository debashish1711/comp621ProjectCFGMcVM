#pragma once
#include "SNode.h"

class SWhileNode : public SNode
{
public:
	SWhileNode(const NodeData& node): SNode(node)
	{
	}

	virtual ~SWhileNode(void);

	virtual bool ShouldCreateEdgeFromChildren() {
		return true;
	}
};
