#ifndef CARTPRODUCT_H
#define CARTPRODUCT_H

#include <vector>

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
		for(int pos=0; pos<6; ++pos){
			if(index[pos] < max_size[pos]-1){
				return true;
			}
		}

		return false;
	}

	//return empty if no next permutation
	std::vector<Soul> next(){
		std::vector<Soul> ret{};
		if(has_next()){
			for(int pos=0; pos<6; ++pos){
				if(index[pos] < max_size[pos]-1){
					++index[pos];
					fill(index.begin(), index.begin()+pos, 0);
					break;
				}
			}
			for(int pos=0; pos<6; ++pos){
				ret.push_back(soulpool[pos][index[pos]]);
			}
		}

		return ret;
	}

	int get_total(){
		return std::accumulate(max_size.begin(), max_size.end(), 1, [](int acc, int elt){return acc*elt;});
	}

private:
	std::vector<int> index;
	std::vector<int> max_size;
	std::vector<std::vector<Soul>> soulpool;
};


#endif