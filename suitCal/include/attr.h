#ifndef ATTR_H
#define ATTR_H

#include <type_traits>
#include <string>
#include <unordered_map>

enum class AttrEnum: int {
	speed,
	defense,
	defense_rate,
	health,
	health_rate,
	attack,
	attack_rate,
	critical_rate,
	critical_damage,
	resistance,
	accuracy,
	count
};


struct MinMax{
	MinMax(double _min_val = 0.0, double _max_val = 99999999.0)
	: min_val{_min_val}, max_val{_max_val} {}
	double min_val, max_val;
};


class Attr {
public:
	void set_base(double const &_val){
		base = _val;
	}
	void set_limit(double const &_min_val, double _max_val){
		mm = {_min_val, _max_val};
	}

	void add_val(double const &_val){
		addon_val += _val;
	}

	void add_rate(double const &_rate){
		addon_rate += _rate;
	}

	double current_val() const {
		return base*(1.0+addon_rate) + addon_val;
	}

	MinMax const &get_minmax() const {
		return mm;
	}


	static AttrEnum str_to_enum(std::string const &attr_name){
		static std::unordered_map<std::string, int> m{
			{"速度", static_cast<int>(AttrEnum::speed)},
			{"防御", static_cast<int>(AttrEnum::defense)}, {"防御加成", static_cast<int>(AttrEnum::defense_rate)},
			{"生命", static_cast<int>(AttrEnum::health)}, {"生命加成", static_cast<int>(AttrEnum::health_rate)},
			{"攻击", static_cast<int>(AttrEnum::attack)}, {"攻击加成", static_cast<int>(AttrEnum::attack_rate)},
			{"暴击", static_cast<int>(AttrEnum::critical_rate)}, {"暴击伤害", static_cast<int>(AttrEnum::critical_damage)},
			{"效果抵抗", static_cast<int>(AttrEnum::resistance)}, {"效果命中", static_cast<int>(AttrEnum::accuracy)}
		};

		return static_cast<AttrEnum>(m[attr_name]);
	}

	static std::string enum_to_str(AttrEnum const &attr_enum){
		static std::unordered_map<int, std::string> m{
			{static_cast<int>(AttrEnum::speed), "速度"},
			{static_cast<int>(AttrEnum::defense), "防御"}, {static_cast<int>(AttrEnum::defense_rate), "防御加成"},
			{static_cast<int>(AttrEnum::health), "生命"}, {static_cast<int>(AttrEnum::health_rate), "生命加成"},
			{static_cast<int>(AttrEnum::attack), "攻击"}, {static_cast<int>(AttrEnum::attack_rate), "攻击加成"},
			{static_cast<int>(AttrEnum::critical_rate), "暴击"}, {static_cast<int>(AttrEnum::critical_damage), "暴击伤害"},
			{static_cast<int>(AttrEnum::resistance), "效果抵抗"}, {static_cast<int>(AttrEnum::accuracy), "效果命中"}
		};

		return m[static_cast<int>(attr_enum)];
	}

private:
	double base = 0.0;
	double addon_rate = 0;
	double addon_val = 0;
	MinMax mm;
};


struct Product{
	AttrEnum attr1, attr2;
	MinMax mm;
};


#endif