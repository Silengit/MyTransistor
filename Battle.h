#pragma once
#include"hero.h"
#include"monster.h"
using namespace std;
class Battle
{
public:
	void An_attack_in_one_Battle(Hero &hero, Monster *&monster, Skill skill_list[]);
	bool battle_is_over(Hero &hero, Monster *&monster);
	bool claim_the_result_of_the_battle(Hero &hero, Monster *&monster, Skill skill_list[]);
	bool one_battle(Hero &hero, Monster *&monster, Skill skill_list[]);
private:
};