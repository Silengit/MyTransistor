#pragma once
#include"Skillsystem.h" 
using namespace std;
class Monster
{
public:
	Monster *InitMonster(const char* file_name, TiXmlElement *scene_element);
	void One_Attack_by_Hero(int Hero_attack, int set, Skill skill_list[]);
	int get_attack();
	bool is_win();
	bool is_defeated();
	string get_name();
	int get_return_exp();
	Monster *find_the_monster(string monster_name, Monster *head)
	{
		for (Monster *p = head; p != NULL; p = p->next)
		{
			if (p->name == monster_name)
			{
				if (p->rebirth == 1)
				{
					TiXmlDocument myDocument;
					myDocument.LoadFile("game.xml");
					TiXmlElement *game = myDocument.RootElement();
					TiXmlElement *Map = game->FirstChildElement("map");
					TiXmlElement *scene_element = Map->FirstChildElement("scene");
					while (scene_element)
					{
						TiXmlElement *monsters = scene_element->FirstChildElement("monsters");
						if (monsters)
						{
							TiXmlElement *monster = monsters->FirstChildElement("monster");
							while (monster)
							{
								TiXmlElement *monster_name_element = monster->FirstChildElement("name");
								string the_name = monster_name_element->GetText();
								if (the_name == monster_name)
								{
									TiXmlElement *monster_name = monster->FirstChildElement("name");
									TiXmlElement *monster_rebirth = monster->FirstChildElement("rebirth");
									TiXmlElement *monster_atk = monster->FirstChildElement("atk");
									TiXmlElement *monster_def = monster->FirstChildElement("def");
									TiXmlElement *monster_hp = monster->FirstChildElement("hp");
									TiXmlElement *whenKilled = monster->FirstChildElement("whenKilled");
									TiXmlElement *exp = whenKilled->FirstChildElement("exp");
									TiXmlElement *monster_special = whenKilled->FirstChildElement("special");
									p->name = monster_name->GetText();
									p->HP = atoi(monster_hp->GetText());
									p->Attack = atoi(monster_atk->GetText());
									p->Defense = atoi(monster_def->GetText());
									p->return_exp = atoi(exp->GetText());
									p->rebirth = atoi(monster_rebirth->GetText());
									dizzy=0;
									load=0;
									repeat_2_remain = 0;
									repeat_3_remain = 0;
									weaken = 0;
									skip = 0;
									return p;
								}
								monster = monster->NextSiblingElement("monster");
							}
						}
						scene_element = scene_element->NextSiblingElement("scene");
					}	
					
				}
			return p;
			}
		}
		return NULL;
	}
	bool the_game_is_over(Monster *a_monster);
	void change_monster_state_and_attack(int set,int actual_output, Skill skill_list[]);
protected:
	string name;
	int HP;
	int Attack;
	int Defense;
	int return_exp;
	int rebirth;
	string special;
	Monster *next;
	bool dizzy;
	int load;
	int repeat_2_remain;
	int repeat_3_remain;
	int weaken;
	bool skip;
};