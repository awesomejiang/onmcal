#include <iostream>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

using namespace std;

int main(int, char**) {
    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{}};

    auto collection = conn["onmyoji"]["souls"];

    auto cursor = collection.find({});

    for (auto&& doc : cursor) {
    	cout << bsoncxx::to_json(doc) << endl;
    	auto element = doc["御魂ID"];
    	if(element.type() != bsoncxx::type::k_utf8) {
		  // Error
    		cout << "error" << endl;
		} else {
	    	cout << element.get_utf8().value.to_string() << endl;
		}

    	cout << endl;
    }
}