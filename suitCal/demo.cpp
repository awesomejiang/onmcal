#include <iostream>
#include <typeinfo>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include "constraints.h"
#include "calculator.h"

using namespace std;

int main(int, char**) {
    Constraints con("my_cons");

    //soul type
    con.set_major_type("破势");
    // con.set_minor_type("荒骷髅");
    con.set_type_range({"三味", "针女", "网切", "伤魂鸟", "破势", "镇墓兽"});

    //set main attrs for position 2/4/6
    con.set_main_attrs(2, {{"攻击加成", 0.55}});
    con.set_main_attrs(4, {{"攻击加成", 0.55}});
    con.set_main_attrs(6, {{"暴击伤害", 0.89}});

    //attr bases
    con.set_base("攻击", 3323);
    con.set_base("速度", 112);
    con.set_base("暴击", 0.15);
    con.set_base("暴击伤害", 1.5);

    //attr limits
    con.set_limit("速度", 1);
    con.set_limit("暴击", 1);

    //target product
    con.set_product("攻击", "暴击伤害", 23000);

    //validate con before compute
    //con.validate();

    //begin computing
    Calculator cal("souls");
    cal.check_all(con);

    return 0;
}