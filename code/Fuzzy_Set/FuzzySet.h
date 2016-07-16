#ifndef FUZZYSET_H_
#define FUZZYSET_H_

class FuzzySet
{
public:
	FuzzySet();
	
	FuzzySet(int lowValue, int midValue, int upperValue );
	
	FuzzySet(int midValue, int upperValue);
	
	
	float getMembershipValue(int value);

	float calculateArea(float height);
	
	float getCOG(float height);
	
	float calculateAreaProduct(float height);
	
	int id;
	int lowValue;
	int midValue;
	int upperValue;
	bool isACornerSet;

	
	
	virtual ~FuzzySet();
	
	
	
};

#endif /*FUZZYSET_H_*/
