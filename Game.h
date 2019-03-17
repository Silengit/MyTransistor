#pragma once
#include"Battle.h"
#include"Map.h"
#include<fstream>
using namespace std;
class Game
{
public:
	Game();
	void Initialize();
	bool Game_is_over() { return init; };
	Scene *receive_the_order(string order, Hero &hero, Map &map,
		Battle &battle, Monster *monster, Scene *Scene_list,Skill skill_list[]) ;
	//void update_the_data(Hero hero, Scene *Scene_list, Skill skill_list[], const char * file_name);
private:
	bool init;
	Hero hero;
	Map *map;
};