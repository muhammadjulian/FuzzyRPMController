#include "FuzzySystem.h"
#include "../Data/data.h"

#include <Arduino.h>
//constants for symbols
#define NM 0
#define NS 1
#define ZE 2
#define PS 3
#define PM 4

#define ZE_OUT 0
#define PS_OUT 1
#define PM_OUT 2
#define PB_OUT 3

//
#define SIZE_ERROR 5
#define SIZE_DERIV 5

#define SIZE_RULE 4
#define SIZE_OUTPUT 3

//rule lookup

short ruleTable[SIZE_ERROR][SIZE_DERIV] = { 
		
		{ PB_OUT, PB_OUT, PB_OUT, PS_OUT,ZE_OUT },
{ PM_OUT, PM_OUT, PS_OUT, ZE_OUT, ZE_OUT }, 
{ PM_OUT, PS_OUT,ZE_OUT, ZE_OUT, ZE_OUT },
{ PS_OUT, PS_OUT, PS_OUT, PS_OUT, PS_OUT }, {
	PS_OUT, PS_OUT, PM_OUT, ZE_OUT, ZE_OUT } };

//


FuzzySet errorSets[SIZE_ERROR];

FuzzySet derivateErrorSets[SIZE_DERIV];

FuzzySet resultSets[SIZE_OUTPUT];

FuzzyRule ruleSet[SIZE_RULE];

float resultMembershipValues[SIZE_OUTPUT];

void initSets() {
	//ZE
	errorSets[ZE].id = ZE;
	errorSets[ZE].lowValue = -120;
	errorSets[ZE].midValue = 0;
	errorSets[ZE].upperValue = 120;

	//PS
	errorSets[PS].id = PS;
	errorSets[PS].lowValue = 0;
	errorSets[PS].midValue = 120;
	errorSets[PS].upperValue = 240;
	//PM
	errorSets[PM].id = PM;
	errorSets[PM].lowValue = 120;
	errorSets[PM].midValue = 240;
	errorSets[PM].upperValue = 360;
	//NS

	errorSets[NS].id = NS;
	errorSets[NS].lowValue = 0;
	errorSets[NS].midValue = -120;
	errorSets[NS].upperValue = -240;
	//	NM

	errorSets[NM].id = NM;
	errorSets[NM].lowValue = -120;
	errorSets[NM].midValue = -240;
	errorSets[NM].upperValue = -360;
	////////////////////////////
	//////// Derivative.........

	//ZE
	derivateErrorSets[ZE].id = ZE;
	derivateErrorSets[ZE].lowValue = -120;
	derivateErrorSets[ZE].midValue = 0;
	derivateErrorSets[ZE].upperValue = 120;

	//PS
	derivateErrorSets[PS].id = PS;
	derivateErrorSets[PS].lowValue = 0;
	derivateErrorSets[PS].midValue = 120;
	derivateErrorSets[PS].upperValue = 240;
	//PM
	derivateErrorSets[PM].id = PM;
	derivateErrorSets[PM].lowValue = 120;
	derivateErrorSets[PM].midValue = 240;
	derivateErrorSets[PM].upperValue = 360;
	//NS

	derivateErrorSets[NS].id = NS;
	derivateErrorSets[NS].lowValue = 0;
	derivateErrorSets[NS].midValue = -120;
	derivateErrorSets[NS].upperValue = -240;
	//	NM

	derivateErrorSets[NM].id = NM;
	derivateErrorSets[NM].lowValue = -120;
	derivateErrorSets[NM].midValue = -240;
	derivateErrorSets[NM].upperValue = -360;

	//////////////////////////////

	resultSets[ZE_OUT].id = ZE_OUT;
	resultSets[ZE_OUT].lowValue = 0;
	resultSets[ZE_OUT].midValue = 50;
	resultSets[ZE_OUT].upperValue = 100;

	resultSets[PS_OUT].id = PS_OUT;
	resultSets[PS_OUT].lowValue = 50;
	resultSets[PS_OUT].midValue = 100;
	resultSets[PS_OUT].upperValue = 150;

	resultSets[PM_OUT].id = PM_OUT;
	resultSets[PM_OUT].lowValue = 100;
	resultSets[PM_OUT].midValue = 150;
	resultSets[PM_OUT].upperValue = 200;

	resultSets[PB_OUT].id = PB_OUT;
	resultSets[PB_OUT].lowValue = 150;
	resultSets[PB_OUT].midValue = 200;
	resultSets[PB_OUT].upperValue = 250;

	////////////////////////////////////
	// rules.

	ruleSet[0].ifId = NM;
	ruleSet[0].andId = NM;
	ruleSet[0].resultId = PB_OUT;

	ruleSet[1].ifId = NM;
	ruleSet[1].andId = NS;
	ruleSet[1].resultId = PM_OUT;

	ruleSet[2].ifId = NM;
	ruleSet[2].andId = ZE;
	ruleSet[2].resultId = PM_OUT;

	ruleSet[3].ifId = NM;
	ruleSet[3].andId = PS;
	ruleSet[3].resultId = PS_OUT;

	ruleSet[4].ifId = NM;
	ruleSet[4].andId = PM;
	ruleSet[4].resultId = ZE_OUT;

	//NS
	ruleSet[5].ifId = NS;
	ruleSet[5].andId = NM;
	ruleSet[5].resultId = PM_OUT;

	ruleSet[5].ifId = NS;
	ruleSet[5].andId = NM;
	ruleSet[5].resultId = PM_OUT;

}

void clearOut() {

	for (int i = 0; i < SIZE_OUTPUT; i++) {
		resultMembershipValues[i] = 0;
	}
}

float getMax(float f1, float f2) {
	return f1 > f2 ? f1 : f2;
}

float getMin(float f1, float f2) {
	return f1 < f2 ? f1 : f2;
}

void calculateOutput() {

	clearOut();

	int firstIndex, secondIndex, resultIndex;
	float totalResult = 0;
	for (int i = 0; i < SIZE_ERROR; i++) {
		//
		for (int j = 0; j < SIZE_DERIV; j++) {
			
			firstIndex = i; //if
			secondIndex = j; //and
			resultIndex = ruleTable[i][j]; //then


			totalResult = getMin(
					errorSets[firstIndex].getMembershipValue(error),
					derivateErrorSets[secondIndex].getMembershipValue(derror));

			resultMembershipValues[resultIndex] = getMax(
					resultMembershipValues[resultIndex], totalResult);

			//Serial.print(resultIndex); Serial.print(" -- >  "); Serial.println(resultMembershipValues[resultIndex]);
		}
	}
	//defuzzify...
	float area = 0;
	float area_product = 0;
	for (int i = 0; i < SIZE_OUTPUT; i++) {

		if (resultMembershipValues[i] > 0) {
			//Serial.print(i);
			//Serial.println("=fired. ");

			area = area
					+ resultSets[i].calculateArea(resultMembershipValues[i]);
			area_product
					= area_product
							+ resultSets[i].calculateAreaProduct(resultMembershipValues[i]);
		}
		//calculate area * center of gravity / (sum of area.)
	}
	if (area != 0) {
		out = area_product / area;
		//rightMotor.setSpeed();
		//Serial.print("==> ");
		//Serial.println(out);
	}
}

