#ifndef ATTR_H
#define ATTR_H

struct MinMax{
	MinMax(double _min_val = 0.0, double _max_val = 99999999.0)
	: min_val{_min_val}, max_val{_max_val} {}
	double min_val, max_val;
};

class Attr {
public:
	void set_base(double const &_val){
		base = _val;
	}
	void set_limit(double const &_min_val, double _max_val){
		mm = {_min_val, _max_val};
	}

	void add_val(double const &_val){
		addon_val += _val;
	}

	void add_rate(double const &_rate){
		addon_rate += _rate;
	}

	double current_val() const {
		return base*(1.0+addon_rate) + addon_val;
	}

	MinMax const &get_minmax() const {
		return mm;
	}

private:
	double base = 0.0;
	double addon_rate = 0;
	double addon_val = 0;
	MinMax mm;
};


struct Product{
	std::string attr1, attr2;
	MinMax mm;
};


#endif