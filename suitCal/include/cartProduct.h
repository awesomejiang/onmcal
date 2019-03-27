#ifndef CARTPRODUCT_H
#define CARTPRODUCT_H

#include <vector>
#include <iterator>
#include <functional>

#include "constraints.h"
#include "soul.h"

class CartProduct{
public:
	CartProduct(std::vector<Soul> const &souls, Constraints const &constraints)
	: index(6, 0), soulpool(6) {
		for(auto const &soul: souls){
			if(soul.type == constraints.major_soul ||
			   soul.type == constraints.minor_soul ||
			   (constraints.major_soul == "" && constraints.major_soul == "")){
				soulpool[soul.position-1].push_back(soul);
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

	int get_total(){
		return std::accumulate(max_size.begin(), max_size.end(), 1, [](int acc, int elt){return acc*elt;});
	}

	void print_by_loc(){
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