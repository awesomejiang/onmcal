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
	Calculator(std::string username){
		souls = soul_loader(username);
	}

	//start calculating!
	void check_all(Constraints const &constraints){
		CartProduct cp(souls, constraints);
		cp.print_by_loc();
		int total = cp.get_total();
		int tenth = 1;
		int cnt = 0;

		while(cp.has_next()){
			auto next_comb = cp.next();
			check_one(constraints, next_comb);

			//print percent for each 10%
			//if(total/1000 == cnt) break;
			if(total/10 * tenth == ++cnt){
				std::cout << "------ complete " << tenth*10 << " percent computing." << std::endl;
				++tenth;
			}
		}

		std::cout << "check all " << cnt << " possible combinations" << std::endl;
		std::cout << "bad_combo: " << bad_comb << std::endl;
		std::cout << "bad_attr: " << bad_attr << std::endl;
		std::cout << "bad_product: " << bad_product << std::endl;
		std::cout << "good_result: " << cnt-bad_comb-bad_attr-bad_product << std::endl;
	}

private:
	std::vector<Soul> souls;
	int bad_comb = 0;
	int bad_attr = 0;
	int bad_product = 0;

	bool check_one(Constraints c, std::vector<std::reference_wrapper<Soul>> const &comb){

		//check suit
		if(!update_attrs(c, comb)){
			++bad_comb; 
			return false;
		}

		//check attr range
		for(auto kv: c.attrs){
			auto const &attr = kv.second;
			auto attr_val = attr.get_val();

			if(attr_val < attr.mm.min_val || attr_val > attr.mm.max_val){
				++bad_attr;
				return false;
			}
		}

		//check product range
		for(auto p: c.products){
			double p_val = c.attrs[p.attr1].get_val() * c.attrs[p.attr2].get_val();

			if(p_val < p.mm.min_val || p_val > p.mm.max_val){
				++bad_product;
				return false;
			}
		}

		//print result
		std::cout << "***************************************************************" << std::endl;
		std::cout << "found one possible combo!" << std::endl;
		for(auto p: c.products){
			double p_val = c.attrs[p.attr1].get_val() * c.attrs[p.attr2].get_val();
			std::cout << p.attr1 << " * " << p.attr2 << ": " << p_val << std::endl;
		}
		std::copy(comb.begin(), comb.end(), std::ostream_iterator<Soul>(std::cout, "\n"));
		std::cout << "***************************************************************" << std::endl;

		return true;
	}

	//update attrs in constraints and check completeness of soul suit 
	bool update_attrs(Constraints &c, std::vector<std::reference_wrapper<Soul>> const &comb){
		int major = c.major_soul==""? 0: 4;
		int minor = c.minor_soul==""? 0: 2;

		for(auto const &soul_ref: comb){
			auto const &soul = soul_ref.get();

			//compute all attrs
			for(auto const &attr: soul.attrs){
				auto attr_name = attr.first;
				auto attr_val = attr.second;
				bool is_rate = attr_name.find("加成") != std::string::npos;
				if(is_rate){
					attr_name = attr_name.substr(0, attr_name.find("加成"));
				}
				if(c.attrs.find(attr_name) != c.attrs.end()){
					if(is_rate){
						c.attrs[attr_name].add_rate(attr_val);
					} else {
						c.attrs[attr_name].add_val(attr_val);
					}
				}
			}

			//compute soul type
			major -= (soul.type == c.major_soul);
			minor -= (soul.type == c.minor_soul);
		}

		return (major == 0 && minor == 0);
	}
};

#endif