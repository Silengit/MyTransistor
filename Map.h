#pragma once
#include"scene.h"
class Map
{
public:
	Scene *InitMap(const char* file_name);
	void output_scene(Scene *scene_list);
	void output_NPC(string name, Scene *head);
	Scene *GoTo(string scene_name, Scene *head)
	{
		return scene_list->GoTo(scene_name,head);
	}
	Monster *find_the_monster(string monster_name, Scene *head)
	{
		return head->find_the_monster(monster_name, head);
	}
private:
	Scene *scene_list;
};