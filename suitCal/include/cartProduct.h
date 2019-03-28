#ifndef CARTPRODUCT_H
#define CARTPRODUCT_H

#include <vector>
#include <iterator>
#include <functional>

#include "constraints.h"
#include "soul.h"

class CartProduct{
public:
	CartProduct(std::vector<Soul> const &souls, Constraints const &c)
	: index(6, 0), soulpool(6) {
		auto const &major_type = c.get_major_type();
		auto const &minor_type = c.get_minor_type();
		auto const &type_range = c.get_type_range();
		//for each soul
		for(auto const &soul: souls){
			auto const &soul_type = soul.get_type();
			auto const &soul_pos = soul.get_position();

			//check if it's in correct type
			bool is_cadidate = false;
			//there's 3 possible case for a correct type
			//1. soul is in major type
			//2. soul is in minor type
			//3. at least 1 of major/minor is empty, and soul is found in type_range
			if(soul_type == major_type ||
			   soul_type == minor_type ||
			   ((major_type == "" || minor_type == "") &&
			    std::find(type_range.begin(), type_range.end(), soul_type) != type_range.end())) {
			   	//if it's in correct main attrs
			   	if(soul_pos == 2 || soul_pos == 4 || soul_pos == 6){
			   		for(auto const &p: c.get_main_attrs(soul_pos)){
			   			if(soul.get_attrs()[static_cast<int>(p.first)] >= p.second){
			   				is_cadidate = true;
			   				break;
			   			}
			   		}
			   	} else {
			   		is_cadidate = true;
			   	}
			}
			
			//push into soul pool if all conditions are satisfied
		   	if(is_cadidate){
				soulpool[soul.get_position()-1].push_back(soul);
		   	}
		}

		for(auto const &sub_pool: soulpool){
			// std::cout << sub_pool.size() << " at this positon" << std::endl;
			max_size.push_back(sub_pool.size());
		}
	}

	bool has_next() const{
		return index[5] < max_size[5];
	}

	//return empty if no next permutation
	std::vector<std::reference_wrapper<Soul>> next(){
		std::vector<std::reference_wrapper<Soul>> ret{};
		if(has_next()){
			//construct one product
			for(int pos=0; pos<6; ++pos){
				ret.push_back(soulpool[pos][index[pos]]);
			}

			//then move backward for one

			int pos = 0;
			while(++index[pos] == max_size[pos] && pos < 5){
				index[pos++] = 0;
			}
		}

		return ret;
	}

	long total_products() const{
		return std::accumulate(max_size.begin(), max_size.end(), 1l, [](long acc, long elt){return acc*elt;});
	}

	void print_by_loc() const{
		std::cout << "souls by loc: ";
		std::copy(max_size.begin(), max_size.end(), std::ostream_iterator<int>(std::cout, "\t"));
		std::cout << std::endl;
	}

private:
	std::vector<int> index;
	std::vector<int> max_size;
	std::vector<std::vector<Soul>> soulpool;
};


#endif