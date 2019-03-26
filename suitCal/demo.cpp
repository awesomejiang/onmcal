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
    con.set_major_soul("破势");
    con.set_minor_soul("荒骷髅");

    //attr bases
    con.set_base("攻击", 3323);
    con.set_base("速度", 112);
    con.set_base("暴击", 0.1);
    con.set_base("暴击伤害", 1.5);

    //attr limits
    con.set_limit("速度", 118, 128);
    con.set_limit("暴击", 1);

    //target product
    con.set_product("攻击", "暴击伤害", 20000);

    //validate con before compute
    con.validate();

    //begin computing
    Calculator cal("souls");
    cal.check_all(con);

    return 0;
}