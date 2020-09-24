#pragma once

#include "date.h"
#include <string>

class Node {
public:
	virtual int Evaluate(const Date & date, const string & event) const = 0;
};

class EmptyNode : public Node {

};
class onNode : public Node {

};
