#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

#include <string>
#include <unordered_map>
#include <vector>


class Attr {
public:
	void set_base(double _val){
		base = _val;
	}
	void set_range(double _min_val, double _max_val){
		min_val = _min_val;
		max_val = _max_val;
	}

	void add_val(double _val){
		addon_val += _val;
	}

	void add_rate(double _rate){
		addon_rate += _rate;
	}

	double base = 0.0;
	double addon_rate = 0;
	double addon_val = 0;
	double min_val = 0.0;
	double max_val = 99999.0;
};


class Constraints {
public:
	Constraints(std::string name = ""): name{name} {}

	//set parameters
	void set_major_soul(std::string soul){
		major_soul = soul;
	}
	void set_minor_soul(std::string soul){
		minor_soul = soul;
	}

	void set_base(std::string attr_name, double _val){
		attrs[attr_name].set_base(val);
	}

	void set_range(std::string attr_name, double _min_val, double _max_val){
		attrs[attr_name].set_range(_min_val, _max_val);
	}

	void set_product_range(std::string attr1, std::string attr2, double _min_val, double _max_val){
		product_attrs[attr1+"*"+attr2].set_range(_min_val, _max_val);
	}



private:
	std::string name = "";
	std::string major_soul = "", minor_soul = "";
	std::unordered_map<std::string, Attr> attrs;
	std::unordered_map<std::string, Attr> product_attrs;

};

#endif