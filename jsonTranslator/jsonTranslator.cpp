#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>

using namespace std;

// string utf8_to_english(string){
// 	static unordered_map<string, string> dict = {
// 		//keys
// 		{"御魂ID", "soul_id"}, {"御魂类型", "soul_type"}, {"位置", "position"},
// 		{"御魂等级", "soul_level"}, {"御魂星级", "soul_star"},
// 		//attributes
// 		{"速度", "speed"},
// 		{"防御", "defense"}, {"防御加成", "defense_rate"},
// 		{"生命", "health"}, {"生命加成", "health_rate"},
// 		{"攻击", "attack"}, {"攻击加成", "attack_rate"},
// 		{"暴击", "critical_rate"}, {"暴击伤害", "critical_damage"},
// 		{"效果抵抗", "resistance"}, {"效果命中", "accuracy"},
// 		//souls
// 		{"阴摩罗", "harpy"}, {"心眼", "watcher"}, {"鸣屋", "house_imp"},
// 		{"狰", "scarlet"}, {"轮入道", "soultaker"}, {"蝠翼", "nightwing"},
// 		{"狂骨", "kyoukotsu"}, {"镇墓兽", "tomb_guard"}, {"破势", "shadow"},
// 		{"网切", "claws"}, {"三味", "samisen"}, {"针女", "seductress"},
// 		{"树妖", "tree_spirit"}, {"薙魂", "soul_edge"}, {"钟灵", "priestess"},
// 		{"镜姬", "mirror_lady"}, {"被服", "boroboroton"}, {"涅槃之火", "holy_flame"},
// 		{"地藏像", "jizo_statue"}, {"木魅", "tree_nymph"}, {"日女巳时", "dawn_fairy"},
// 		{"反枕", "shy_soul"}, {"招财猫", "fortune_cat"}, {"雪幽魂", "snow_spirit"},
// 		{"魅妖", "temptress"}, {"珍珠", "pearl"}, {"火灵", "azure_basan"},
// 		{"蚌精", "sea_sprite"}, {"魍魉之匣", "mimic"}, {"幽谷响", "yamabiko"},
// 		{"反魂香", "senecio"}, {"骰子鬼", "dice_sprite"}, {"蜃气楼", "shinkiro"},
// 		{"地震鲶", "jishin_namazu"}, {"荒骷髅", "gashadokuro"}, {"胧车", "oboroguruma"},
// 		{"土蜘蛛", "tsuchigumo"}
// 	};

// 	return "";
// }

int main(int argc, char **argv){
	if(argc != 3){
		cout << "error: wrong parameters." << endl;
		exit(1);
	}
	//input and output files
	ifstream ifs(argv[1]);
	if(!ifs.is_open()){
		cout << "error: invalid input file." << endl;
	}
	ofstream ofs(argv[2]);
	if(!ofs.is_open()){
		cout << "error: invalid output file." << endl;
	}

	string line;
	while(getline(ifs, line)){
		if(line.find("[") != string::npos ||
		   line.find("]") != string::npos ||
		   line.find("yuhun_ocr") != string::npos){	//ignore this 3 lines
			continue;
		} else {
			auto found = line.find("},");
			if(found != string::npos){	//delete ',' after each json object
				line = line.substr(0, found+1) + "\n";
			}
			ofs << line;
		}
	}

	return 0;
}


//to import json into mongodb
//mongoimport -d db -c collection file