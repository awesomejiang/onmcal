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
			if(!elt.key().compare("_id")){
				mongodb_id = elt.get_oid().value.to_string();
			} else if(!elt.key().compare("御魂ID")){
				id = elt.get_utf8().value.to_string();
			} else if(!elt.key().compare("御魂类型")){
				type = elt.get_utf8().value.to_string();
			} else if(!elt.key().compare("位置")){
				position = elt.get_int32().value;
			} else if(!elt.key().compare("御魂等级")){
				level = elt.get_int32();
			} else if(!elt.key().compare("御魂星级")){
				star = elt.get_int32();
			} else{
				attrs[std::string(elt.key())] = elt.get_double();
			}
		}
	}

	friend std::ostream &operator<<(std::ostream &out, Soul const &soul){
		auto ret = 
			"id: " + soul.id +
			"\ntype: " + soul.type +
			"\tposition: " + std::to_string(soul.position) +
			"\tlevel: " + std::to_string(soul.level) +
			"\tstar: " + std::to_string(soul.star);
		for(auto const &kv: soul.attrs){
			ret += "\n" + kv.first + "\t" + std::to_string(kv.second);
		}
		return out << ret << std::endl;
	}

	std::string mongodb_id, id, type;
	int position, level, star;
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