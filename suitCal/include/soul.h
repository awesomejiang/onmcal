#ifndef SOUL_H
#define SOUL_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>


#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>


class Soul {
public:
	Soul(bsoncxx::document::view doc){
		for(auto elt: doc){
			if(elt.key().compare("御魂ID")){
				id = elt.get_utf8().value.to_string();
			} else if(elt.key().compare("御魂类型")){
				type = elt.get_utf8().value.to_string();
			} else if(elt.key().compare("位置")){
				position = elt.get_int64();
			} else if(elt.key().compare("御魂等级")){
				level = elt.get_int64();
			} else if(elt.key().compare("御魂星级")){
				star = elt.get_int64();
			} else{
				attrs[elt.key()] = elt.get_double();
			}
		}
	}

	friend std::ostream &operator<<(std::ostream &out, Soul const &soul){
		auto ret = 
			"id: " + soul.id +
			"\ntype: " + soul.type +
			"\nposition: " + std::to_string(soul.postion)
			"\nlevel: " + std::to_string(soul.level)
			"\ntype: " + std::to_string(soul.type);
		for(auto const &kv: attrs){
			ret += "\n" + kv.first + "\t" + kv.second;
		}
		return out << ret << std::endl;
	}

	std::string id;
	std::string type;
	int position;
	int level;
	int star;
	std::unordered_map<std::string, double> attrs;
	std::vector<std::string> suits;
};


std::vector<Soul> soul_loader(std::string username){
    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{}};

    auto collection = conn["onmyoji"][username];

    auto cursor = collection.find({});

	std::vector<Soul> souls;

	for(auto &&doc: cursor){
		souls.emplace_back(doc);
	}

	return souls;
}


#endif