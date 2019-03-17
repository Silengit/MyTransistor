#include"scene.h"
Scene *Scene::InitScene(const char* file_name, TiXmlElement *Map)
{
	Scene *head = NULL, *tail;
	TiXmlElement *scene_element = Map->FirstChildElement("scene");
	while(scene_element)
	{
		Scene *p = new Scene;
		NPC *npc = new NPC;
		Monster *monster = new Monster;
		TiXmlElement *scene_name = scene_element->FirstChildElement("name");
		TiXmlElement *scene_description = scene_element->FirstChildElement("description");
		TiXmlElement *scene_trace = scene_element->FirstChildElement("trace");
		p->npc_list=npc->InitNPC(file_name, scene_element);
		p->monster_list=monster->InitMonster(file_name, scene_element);
		p->name = scene_name->GetText();
		p->description = scene_description->GetText();
		p->trace= atoi(scene_trace->GetText());
		p->next = NULL;
		if (head == NULL)
			head = tail = p;
		else
		{
			tail->next = p;
			tail = p;
		}
		scene_element = scene_element->NextSiblingElement("scene");
	}
	return head;
}
void Scene::output(Scene *scene_list)
{
	cout << "ÄãÎ»ÓÚ" << scene_list->name<<endl;
	cout << scene_list->description << endl;
}
bool Scene::output_NPC(string NPC_name, Scene *head)
{
	for (Scene *p = head; p; p = p->next)
	{
		if (p->npc_list->output(NPC_name, p->npc_list))
			return true;
	}
	return false;
}
