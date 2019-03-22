#ifndef CARTPRODUCT_H
#define CARTPRODUCT_H

#include <vector>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include "constraints.h"

class CartProduct{
public:
	CartProduct(mongocxx::cursor::iterator const &cursor, Constraints const &constraints){
		for(auto &&doc: cursor){
			if(doc["御魂类型"] == constraints.major_soul ||
			   doc["御魂类型"] == constraints.minor_soul ||
			   constraints.major_soul == "" && constraints.major_soul == "") {
				soulpool[doc["位置"].get_int32()-1] = doc;
			}
		}

		for(auto const &souls: soulpool){
			max_size.push_back(souls.size());
		}
	}

	bool hasNext() const{
		for(int pos=0; pos<6; ++pos){
			if(index[pos] < max_size[pos]-1){
				return true;
			}
		}

		return false;
	}

	//return empty if no next permutation
	std::vector<bsoncxx::document::view>> next(){
		std::vector<bsoncxx::document::view>> ret{};
		if(hasNext()){
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

private:
	std::vector<int> index(6, 0);
	std::vector<int> max_size;
	std::vector<std::vector<bsoncxx::document::view>> soulpool;
};

#endif