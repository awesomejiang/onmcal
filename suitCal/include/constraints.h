#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

#include <string>
#include <unordered_map>
#include <vector>

#include "attr.h"


class Constraints {
public:
	Constraints(std::string name = ""): name{name} {}

	//set parameters
	void set_major_soul(std::string soul){
		major_soul = soul;
	}
	void set_minor_soul(std::string soul){
		minor_soul = soul;
	}

	void set_base(std::string attr_name, double val){
		attrs[attr_name].set_base(val);
	}

	void set_limit(std::string attr_name, double min_val = 0.0, double max_val = 1e6){
		attrs[attr_name].set_limit(min_val, max_val);
	}

	void set_product(std::string attr1, std::string attr2, double min_val = 0.0, double max_val = 1e10){
		products.push_back({attr1, attr2, {min_val, max_val}});
	}

	//add 2 combo attrs for target soul suits
	void validate(){
		for(auto type: {major_soul, minor_soul}){
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
	}

	std::string name = "";
	std::string major_soul = "", minor_soul = "";
	//attr_name could be : "攻击" "生命" "防御" "速度" "效果命中" "效果抵抗" "暴击" "暴击伤害" 
	std::unordered_map<std::string, Attr> attrs;
	struct Product{
		std::string attr1, attr2;
		MinMax mm;
	};
	std::vector<Product> products;

private:
	bool is_in_list(std::string str, std::vector<std::string> list){
		for(auto elt: list){
			if(str == elt){
				return true;
			}
		}

		return false;
	}
};

#endif