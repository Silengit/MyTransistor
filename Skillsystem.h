#pragma once
#include <iostream>
#include<string>
#include"tinystr.h"
#include"tinyxml.h"
#include <stdlib.h> 
#include <time.h>  
using namespace std;
/*int compute_the_skill_from_hero(int set)
{
	int state = 0;
	for (int i = 0; i < 14; i++)
	{
		if (skill_list[i].order == set)
		{
			if (skill_list[i].special == "dizzy")
				state = 1;
			else if (skill_list[i].special == "explode")
				state = 2;
			else if (skill_list[i].special == "skip")
				state = 3;
			else if (skill_list[i].special == "load")
				state = 4;
			else if (skill_list[i].special == "several")
				state = 5;
			else if (skill_list[i].special == "repeat_2")
				state = 6;
			else if (skill_list[i].special == "repeat_3")
				state = 7;
			else if (skill_list[i].special == "absorb")
				state = 8;
			else if (skill_list[i].special == "weaken")
				state = 9;
			else if (skill_list[i].special == "close")
				state = 10;
			else if (skill_list[i].special == "defeat")
				state = 11;
		}
		break;
	}
	return state;
}*/
class Skill
{
public:Skill *Init_skills(const char* file_name);
	   bool output_newskills(int level, Skill skill_list[]);
	   int  choose_the_skill(int index, int level, Skill skill_list[]);
	   void output_current_skills(Skill skill_list[]);
	   bool replace_the_index_skill(int index, int level, int i,Skill skill_list[],int num);
	   void set_the_order_of_new_skill(int set, int level, int i, Skill skill_list[],int num);
	   bool  skill_spot_is_full(Skill skill_list[]);
	   bool no_access_to_the_skill(Skill skill_list[],int set);
	   void delete_the_access_to_the_skill(Skill skill_list[], int i,int level, int num);
	   bool the_set_has_been_used(Skill skill_list[], int set);
	   int return_equip(Skill skill_list[], int index) { return skill_list[index].equiped; };
	   int return_order(Skill skill_list[], int index) { return skill_list[index].order; };
	   int return_have(Skill skill_list[], int index) { return skill_list[index].have; };
	string name;
	int attack;
	int consume;
	string special;
	bool equiped;
	int order;
	bool have;
}; 