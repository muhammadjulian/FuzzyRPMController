#include "FuzzySet.h"

FuzzySet::FuzzySet()
{
}
FuzzySet :: FuzzySet(int lowValue, int midValue, int upperValue ){
	this->lowValue = lowValue;
	this->midValue = midValue;
	this->upperValue = upperValue;
	
}
	
FuzzySet :: FuzzySet(int midValue, int upperValue){
	this->midValue = midValue;
	this->upperValue = upperValue;
}


float FuzzySet ::  getMembershipValue(int value){
	
	if(value < lowValue || value > upperValue){
		return 0;
	}
	float half;
	if(value < midValue){
		half = (value - lowValue);
		half = half /(midValue - lowValue);
	}else{
		half = (upperValue - value);
		half =  half/(upperValue - midValue);
	}
	return half;
	
	
	
}

float FuzzySet:: calculateArea(float height){
	float x = lowValue + (midValue - lowValue) * height;
	float y = upperValue - height * (upperValue - midValue);//-++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
	float area = ((upperValue - lowValue) + (y-x)) * height/2;
	return area;
}


float FuzzySet::getCOG(float height){
	
	float x = lowValue + (midValue - lowValue) * height;
	float y = upperValue - height * (upperValue - midValue);
	
	float area = calculateArea(1);
	float area_product = (area * (lowValue + midValue + upperValue))/3 -((area-calculateArea(height)) * 
			(x+y+midValue))/3;
	
	return area_product / (calculateArea(height));	
	
}

float FuzzySet::calculateAreaProduct(float height){
	float x = lowValue + (midValue - lowValue) * height;
		float y = upperValue - height * (upperValue - midValue);
		
		float area = calculateArea(1);
		float area_product = (area * (lowValue + midValue + upperValue))/3 -((area-calculateArea(height)) * 
				(x+y+midValue))/3;
	
		return area_product;
}
	

FuzzySet::~FuzzySet()
{
}
