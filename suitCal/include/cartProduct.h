#ifndef CARTPRODUCT_H
#define CARTPRODUCT_H

#include <vector>

#include "constraints.h"
#include "soul.h"

class CartProduct{
public:
	CartProduct(std::vector<Soul> const &souls, Constraints const &constraints){
		for(auto const &soul: souls){
			if(soul.type == constraints.major_soul ||
			   soul.type == constraints.minor_soul ||
			   (constraints.major_soul == "" && constraints.major_soul == "")){
				soulpool[soul.position-1] = soul;
			}
		}

		for(auto const &sub_pool: soulpool){
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
	std::vector<Soul&> next(){
		std::vector<Soul&> ret{};
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
				std::cout << index[pos] << "\t";
			}
			std::cout << std::endl;
		}

		return ret;
	}

private:
	std::vector<int> index(6);
	std::vector<int> max_size;
	std::vector<Soul> soulpool;
};


#endif