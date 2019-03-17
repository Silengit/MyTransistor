#pragma once
#include"NPC.h"
#include"monster.h"
using namespace std;
class Scene
{
public:
	Scene *InitScene(const char* file_name, TiXmlElement *Map);
	void output(Scene *scene_list);
	bool output_NPC(string NPC_name, Scene *head);
	Scene *GoTo(string scene_name, Scene *head)
	{
		int sum=0;
		for (Scene *p = head; p != NULL; p = p->next)
		{
			if (sum == 2)
				break;
			sum++;
			if (p->name == scene_name)
			{
				cout << "ÄãÀ´µ½[" << p->name << "]" << endl;
				return p;
			}
		}
		return NULL;
	}
	Monster *find_the_monster(string monster_name, Scene *head)
	{
		return monster_list->find_the_monster(monster_name, monster_list);
	}
	string get_name() { return name; };
	string name;
	string description;
	NPC *npc_list;
	Monster *monster_list;
	bool trace;
	Scene *next;
};
