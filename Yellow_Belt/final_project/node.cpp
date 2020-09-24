#include "date.h"
#include "condition_parser.h"
class Node {
	virtual int Evaluate(const Date & date, const string & event) const = 0;
};

class EmptyNode : public Node {

};
class onNode : public Node {

};
class EventComparisonNode : public Node {
	Comparison cmp;

};
class LogicalOperationNode : public Node {
	Comparison cmp;
	LogicalOperation logicalOperation;
			logical_operation, left, ParseExpression(current, end, current_precedence)
};