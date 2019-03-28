#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

#include <string>
#include <vector>

#include "attr.h"


class Constraints {
public:
	Constraints(std::string const &name = "")
	: name{name},
	  type_range{"阴摩罗", "心眼", "鸣屋", "狰", "轮入道", "蝠翼", "狂骨", "镇墓兽", "破势",
		"网切", "三味", "针女", "树妖", "薙魂", "钟灵", "镜姬", "被服", "涅槃之火",
		"地藏像", "木魅", "日女巳时", "反枕", "招财猫", "雪幽魂", "魅妖", "珍珠",
		"火灵", "蚌精", "魍魉之匣", "幽谷响", "反魂香", "骰子鬼", "蜃气楼", "地震鲶",
		"荒骷髅", "胧车", "土蜘蛛"},
	  main_attrs(3), attrs(static_cast<int>(AttrEnum::count)) {}

	//set parameters
	void set_major_type(std::string const &type){
		major_type = type;
	}

	void set_minor_type(std::string const &type){
		minor_type = type;
	}

		//if we do not call this at driver, type_range would be all souls by default
	void set_type_range(std::vector<std::string> const &types){
		type_range.assign(types.begin(), types.end());
	}

	void set_main_attrs(int const &pos, std::vector<std::pair<std::string, double>> const &candidate_attrs){
		for(auto const &ca: candidate_attrs){
			main_attrs[pos/2-1].emplace_back(Attr::str_to_enum(ca.first), ca.second);
		}
	}

	void set_base(std::string const &attr_name, double const &val){
		auto ae = Attr::str_to_enum(attr_name);
		attrs[static_cast<int>(ae)].set_base(val);
	}

	void set_limit(std::string const &attr_name, double const &min_val = 0.0, double const &max_val = 1e6){
		auto ae = Attr::str_to_enum(attr_name);
		attrs[static_cast<int>(ae)].set_limit(min_val, max_val);
	}

	void set_product(std::string const &attr1, std::string const &attr2, double const &min_val = 0.0, double const &max_val = 1e10){
		products.push_back({Attr::str_to_enum(attr1), Attr::str_to_enum(attr2), {min_val, max_val}});
	}

	//add to final comb parameters
	void add_suit_attr(std::string const &type){
		for(int idx = 0; idx<6; ++idx){
			auto const &sub_types = soul_types[idx];
			if(std::find(sub_types.begin(), sub_types.end(), type) != sub_types.end()){	//found
				if(idx<3){	//idx= 0, 1, 2 -> AttrEnum::resistance, accuracy, cr_rate. Should add_val()
					attrs[idx].add_val(0.15);
				} else {	//def, hlt, att. Should add_rate()
					attrs[idx].add_rate(0.15);
				}
				break;
			}
		}
	}

	void add_attr_rate(AttrEnum const &attr_enum, double const &val){
		attrs[static_cast<int>(attr_enum)].add_rate(val);
	}

	void add_attr_val(AttrEnum const &attr_enum, double const &val){
		attrs[static_cast<int>(attr_enum)].add_val(val);
	}

	//get private members
	std::string const &get_major_type() const {
		return major_type;
	}

	std::string const &get_minor_type() const {
		return minor_type;
	}

	std::vector<std::string> const &get_type_range() const {
		return type_range;
	}

	std::vector<std::pair<AttrEnum, double>> const &get_main_attrs(int const &pos) const{
		return main_attrs.at(pos/2-1);
	}

	std::vector<Attr> const &get_attrs() const {
		return attrs;
	}

	std::vector<Product> const &get_products() const {
		return products;
	}

	double get_attr_val(AttrEnum const &attr_enum) const {
		return attrs.at(static_cast<int>(attr_enum)).current_val();
	}

private:
	std::string name = "";
	std::string major_type = "", minor_type = "";
	std::vector<std::string> type_range;
	std::vector<std::vector<std::pair<AttrEnum, double>>> main_attrs;
	std::vector<Attr> attrs;
	std::vector<Product> products;

	bool is_in_list(std::string const &str, std::vector<std::string> const &list){
		for(auto elt: list){
			if(str == elt){
				return true;
			}
		}

		return false;
	}

	//type order is based on enum order:
	//resistance, accuracy, critical_rate, defense, health, attack
	std::vector<std::vector<std::string>> soul_types{
		{"幽谷响", "魍魉之匣", "骰子鬼", "反魂香"},
		{"蚌精", "火灵"},
		{"三味", "针女", "网切", "伤魂鸟", "破势", "镇墓兽"},
		{"雪幽魂", "魅妖", "珍珠", "招财猫", "反枕", "日女", "木魅"},
		{"涅槃之火", "地藏像", "镜姬", "钟灵", "被服", "树妖", "薙魂"},
		{"蝠翼", "狂骨", "狰", "鸣屋", "轮入道", "心眼", "阴摩罗"}
	};
};


#endif