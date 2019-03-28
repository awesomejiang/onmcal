#ifndef SOUL_H
#define SOUL_H

#include <iostream>
#include <string>
#include <vector>


#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include "attr.h"

class Soul {
public:
	Soul(bsoncxx::document::view const &doc): attrs(static_cast<int>(AttrEnum::count)) {
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
				auto ae = Attr::str_to_enum(std::string{elt.key()});
				attrs[static_cast<int>(ae)] = elt.get_double();
			}
		}
	}

	std::vector<double> const &get_attrs() const{
		return attrs;
	}

	std::string const &get_type() const {
		return type;
	}

	int const &get_position() const {
		return position;
	}

	friend std::ostream &operator<<(std::ostream &out, Soul const &soul){
		auto const &soul_attrs = soul.attrs;
		auto ret = 
			"id: " + soul.id +
			"\ntype: " + soul.type +
			"\tposition: " + std::to_string(soul.position) +
			"\tlevel: " + std::to_string(soul.level) +
			"\tstar: " + std::to_string(soul.star);
		for(unsigned int idx=0; idx<soul_attrs.size(); ++idx){
			auto attr_val = soul_attrs[idx];
			if(attr_val > 0.0){
				ret += "\n" + Attr::enum_to_str(static_cast<AttrEnum>(idx)) + 
					   ": " + std::to_string(attr_val);
			}
		}
		return out << ret << std::endl;
	}

private:
	std::string mongodb_id, id, type;
	int position, level, star;
	std::vector<double> attrs;
	std::vector<std::string> suits;
};


std::vector<Soul> soul_loader(std::string const &username){
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