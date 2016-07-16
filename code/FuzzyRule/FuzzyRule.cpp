#include "FuzzyRule.h"

FuzzyRule::FuzzyRule()
{
}


FuzzyRule::FuzzyRule(int ifId, int andId, int resultId)
{
	this->ifId = ifId;
	this->andId = andId;
	this->resultId = resultId;
}

FuzzyRule::~FuzzyRule()
{
}
