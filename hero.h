#pragma once
#include"Skillsystem.h" 
using namespace std;
class Hero
{
public:
	bool InitHero(const char* file_name);
	void Show_Status_Of_Battle();
	void One_Attack_by_Monster(int Monster_attack, int set, Skill skill_list[]);
	void victory(int exp_of_Monster);
	void level_up(Skill skill_list[]);
	bool is_level_up();
	int get_attack();
	bool is_win();
	bool is_defeated();
	bool MP_IS_ENOUGH(int set, Skill skill_list[]);
	int get_level() { return level; };
	int get_MAX_HP() { return MAX_HP; };
	int get_current_HP() { return current_HP; };
	int get_MAX_MP() { return MAX_MP; };
	int get_current_MP() { return current_MP; };
	int get_defense () { return Defense; };
	int get_exp() { return exp; };
private:
	string name;
	int level;
	int MAX_HP;
	int current_HP;
	int MAX_MP;
	int current_MP;
	int Attack;
	int Defense;
	int exp;
	int increse_of_HP_per_level_up;
	int increse_of_MP_per_level_up;
	int increse_of_Attack_per_level_up;
	int increse_of_Defense_per_level_up;
	int exp_for_per_level_up;
	bool skip;
	bool dizzy;
	int weaken;
	Skill skill[4];
};
