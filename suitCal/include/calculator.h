#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "constraints.h"
#include "cartProduct.h"

class Calculator{
public:
	Calculator(std::string username){
	    mongocxx::instance inst{};
	    mongocxx::client conn{mongocxx::uri{}};

	    auto collection = conn["onmyoji"][username];

	    cursor = collection.find({});
	}

	//start calculating!
	void compute(Constraints const &constraints){
		int major = major_soul==""? 0: 4;
		int minor = minor_soul==""? 0: 2;

		cartProduct cp(cursor, constraints);
		while(cp.hasNext()){
			auto souls = cp.next();
		}

	}
private:
	mongocxx::cursor::iterator const &cursor;
};

#endif