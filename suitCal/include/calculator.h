#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <vector>
#include <iostream>
#include <functional>
#include <iterator>
#include <algorithm>

#include "attr.h"
#include "constraints.h"
#include "cartProduct.h"
#include "soul.h"

class Calculator{
public:
	Calculator(std::string const &username){
		souls = soul_loader(username);
	}

	//start calculating!
	void check_all(Constraints c){
		//set cp iterator
		CartProduct cp(souls, c);
		cp.print_by_loc();

		//reset static counters
		bad_comb = 0;
		bad_attr = 0;
		bad_product = 0;
		long total = cp.total_products();
		// if(total > 1e11){
		// 	std::cout << "warning: too much possible combinations. This computation is skipped." << std::endl;
		// 	return ;
		// }

		//if suit type is fixed, we set the combo attr here
		//or we have to do it in every check_one() call
		c.add_suit_attr(c.get_major_type());
		c.add_suit_attr(c.get_minor_type());
		is_soul_type_fixed = (c.get_major_type() != "" && c.get_minor_type() != "");

		long cnt = 0;
		int tenth = 1;
		while(cp.has_next()){
			auto next_comb = cp.next();
			check_one(c, next_comb);

			//print percent for each 10%
			if(total/10 * tenth == ++cnt){
				std::cout << "------ complete " << tenth*10 << " percent computing." << std::endl;
				++tenth;
			}
		}

		//print statistics
		std::cout << "check all " << cnt << " possible combinations" << std::endl;
		std::cout << "bad_combo: " << bad_comb << std::endl;
		std::cout << "bad_attr: " << bad_attr << std::endl;
		std::cout << "bad_product: " << bad_product << std::endl;
		std::cout << "good_result: " << cnt-bad_comb-bad_attr-bad_product << std::endl;
	}

private:
	std::vector<Soul> souls;
	bool is_soul_type_fixed = false;
	long bad_comb = 0;
	long bad_attr = 0;
	long bad_product = 0;

	bool check_one(Constraints c, std::vector<std::reference_wrapper<Soul>> const &comb){

		//check suit
		if(!check_suit(c, comb)){
			++bad_comb; 
			return false;
		}

		//update attrs
		update_attrs(c, comb);

		//only update suit attrs if soul type is not fixed
		if(!is_soul_type_fixed){
			update_suit_attrs(c, comb);
		}

		//check attr range
		if(!check_attrs(c)){
			++bad_attr;
			return false;
		}

		//check product range
		if(!check_products(c)){
			++bad_product;
			return false;
		}

		//print result
		std::cout << "***************************************************************" << std::endl;
		std::cout << "found one possible combination!" << std::endl;
		for(auto p: c.get_products()){
			double p_val = c.get_attr_val(p.attr1) * c.get_attr_val(p.attr2);
			std::cout << Attr::enum_to_str(p.attr1) << " * " << Attr::enum_to_str(p.attr2) << ": " << p_val << std::endl;
		}
		std::copy(comb.begin(), comb.end(), std::ostream_iterator<Soul>(std::cout, "\n"));
		std::cout << "***************************************************************" << std::endl;

		return true;
	}

	bool check_suit(Constraints const &c, std::vector<std::reference_wrapper<Soul>> const &comb){
		int major = c.get_major_type()==""? 0: 4;
		int minor = c.get_minor_type()==""? 0: 2;

		for(auto const &soul_ref: comb){
			auto const &soul = soul_ref.get();

			//compute soul type
			major -= (soul.get_type() == c.get_major_type());
			minor -= (soul.get_type() == c.get_minor_type());
		}

		return (major == 0 && minor == 0);
	}

	//update attrs in constraints and check completeness of soul suit 
	void update_attrs(Constraints &c, std::vector<std::reference_wrapper<Soul>> const &comb){
		for(auto const &soul_ref: comb){
			auto const &soul = soul_ref.get();

			//compute all attrs
			auto const &soul_attrs = soul.get_attrs();
			for(unsigned int idx = 0; idx<soul_attrs.size(); ++idx){
				if(idx == static_cast<int>(AttrEnum::defense_rate) ||
				   idx == static_cast<int>(AttrEnum::health_rate) ||
				   idx == static_cast<int>(AttrEnum::attack_rate)){
					c.add_attr_rate(static_cast<AttrEnum>(idx-3), soul_attrs[idx]);
				} else {
					c.add_attr_val(static_cast<AttrEnum>(idx), soul_attrs[idx]);
				}
			}
		}
	}

	void update_suit_attrs(Constraints &c, std::vector<std::reference_wrapper<Soul>> const &comb){
		std::unordered_map<std::string, int> soul_types;
		for(auto const &soul_ref: comb){
			//record soul types
			++soul_types[soul_ref.get().get_type()];
		}

		auto major_type = c.get_major_type(), minor_type = c.get_minor_type();
		if(major_type != ""){
			soul_types[major_type] -= 4;
		}
		if(minor_type != ""){
			soul_types[minor_type] -= 2;
		}

		for(auto const &kv: soul_types){
			if(kv.second == 6){	//in fact call set func 2 times when kv is 6
				c.add_suit_attr(kv.first);
			}
			if(kv.second >= 2){ //notice it is not a else branch
				c.add_suit_attr(kv.first);
			}
		}
	}

	bool check_attrs(Constraints const &c){
		for(auto const &attr: c.get_attrs()){
			auto attr_val = attr.current_val();

			if(attr_val < attr.get_minmax().min_val || attr_val > attr.get_minmax().max_val){
				return false;
			}
		}

		return true;
	}

	bool check_products(Constraints const &c){
		// auto const &products = c.products;
		for(auto const &p: c.get_products()){
			double p_val = c.get_attr_val(p.attr1) * c.get_attr_val(p.attr2);

			if(p_val < p.mm.min_val || p_val > p.mm.max_val){
				return false;
			}
		}

		return true;
	}
};

#endif