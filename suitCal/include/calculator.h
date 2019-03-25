#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "constraints.h"
#include "cartProduct.h"
#include "soul.h"

class Calculator{
public:
	Calculator(std::string username){
		souls = soul_loader(username);
	}

	//start calculating!
	void compute(Constraints const &constraints){
		//int major = major_soul==""? 0: 4;
		//int minor = minor_soul==""? 0: 2;

		cartProduct cp(souls, constraints);
		while(cp.hasNext()){
			auto souls = cp.next();
		}

	}
private:
	std::vector<Soul> souls;
};

#endif