#include <iostream>
#include "Game.h"
#include"windows.h"
int main()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |

		FOREGROUND_GREEN | BACKGROUND_GREEN | BACKGROUND_BLUE);
	system("color 3A");
	cout << "              游戏名:*Transistor* （感谢汉化组^_+）"<<endl;
	cout << "请输入“initgame”"<<endl;
	Skill *skill_list;
	Skill skillsystem;
	skill_list=skillsystem.Init_skills("game.xml");
	Game new_story;
	Hero hero;
	hero.InitHero("game.xml");
	Map map;
	Scene *all_the_scenes;
	all_the_scenes=map.InitMap("game.xml");
	Battle battle;
	new_story.Initialize();
	string order;
	cin >> order;
	Scene *current_scene = all_the_scenes;
	while (!new_story.Game_is_over())
	{
		Monster *monster=new Monster;
		current_scene=new_story.receive_the_order(order,hero,map,battle,monster, current_scene, skill_list);
		delete monster;
		if(!new_story.Game_is_over())
			cin >> order;
		else break;
	}
	return 0;
}

