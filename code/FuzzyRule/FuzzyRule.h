#ifndef FUZZYRULE_H_
#define FUZZYRULE_H_

class FuzzyRule
{
public:
	FuzzyRule();
	
	FuzzyRule(int ifId, int andId, int resultId);
	
	
	int ifId;
	int andId;
	int resultId;
	
	virtual ~FuzzyRule();
};

#endif /*FUZZYRULE_H_*/
