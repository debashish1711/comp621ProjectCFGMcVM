#pragma once
#include "SNode.h"

class SForNode : public SNode
{
public:
	SForNode(const NodeData& node): SNode(node)
	{
	}

	virtual ~SForNode(void);

	virtual bool ShouldCreateEdgeFromChildren() {
		return true;
	}
};
