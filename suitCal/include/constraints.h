#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

#include <string>
#include <unordered_map>
#include <vector>

#include "attr.h"


class Constraints {
public:
	Constraints(std::string const &name = ""): name{name} {}

	//set parameters
	void set_major_type(std::string const &type){
		major_type = type;
	}

	void set_minor_type(std::string const &type){
		minor_type = type;
	}

	void set_base(std::string const &attr_name, double const &val){
		attrs[attr_name].set_base(val);
	}

	void set_limit(std::string const &attr_name, double const &min_val = 0.0, double const &max_val = 1e6){
		attrs[attr_name].set_limit(min_val, max_val);
	}

	void set_product(std::string const &attr1, std::string const &attr2, double const &min_val = 0.0, double const &max_val = 1e10){
		products.push_back({attr1, attr2, {min_val, max_val}});
	}

	//add to final combo parameters
	void add_suit_attr(std::string const &type){
		if(is_in_list(type, {"蚌精", "火灵"})){
			attrs["效果命中"].add_val(0.15);
		} else if(is_in_list(type, {"幽谷响", "魍魉之匣", "骰子鬼", "反魂香"})) {
			attrs["效果抵抗"].add_val(0.15);
		} else if(is_in_list(type, {"三味", "针女", "网切", "伤魂鸟", "破势", "镇墓兽"})) {
			attrs["暴击"].add_val(0.15);
		} else if(is_in_list(type, {"蝠翼", "狂骨", "狰", "鸣屋", "轮入道", "心眼", "阴摩罗"})) {
			attrs["攻击"].add_rate(0.15);
		} else if(is_in_list(type, {"雪幽魂", "魅妖", "珍珠", "招财猫", "反枕", "日女", "木魅"})) {
			attrs["防御"].add_rate(0.15);
		} else if(is_in_list(type, {"涅槃之火", "地藏像", "镜姬", "钟灵", "被服", "树妖", "薙魂"})) {
			attrs["生命"].add_rate(0.15);
		}
	}

	void add_attr_rate(std::string const &attr_name, double const &val){
		attrs[attr_name].add_rate(val);
	}

	void add_attr_val(std::string const &attr_name, double const &val){
		attrs[attr_name].add_val(val);
	}

	//get private members
	std::string const &get_major_type() const {
		return major_type;
	}

	std::string const &get_minor_type() const {
		return minor_type;
	}

	std::unordered_map<std::string, Attr> const &get_attrs() const {
		return attrs;
	}

	std::vector<Product> const &get_products() const {
		return products;
	}

	double get_attr_val(std::string const &attr_name) const {
		return attrs.at(attr_name).current_val();
	}

private:
	std::string name = "";
	std::string major_type = "", minor_type = "";
	//attr_name could be : "攻击" "生命" "防御" "速度" "效果命中" "效果抵抗" "暴击" "暴击伤害" 
	std::unordered_map<std::string, Attr> attrs;
	std::vector<Product> products;

	bool is_in_list(std::string const &str, std::vector<std::string> const &list){
		for(auto elt: list){
			if(str == elt){
				return true;
			}
		}

		return false;
	}
};

#endif