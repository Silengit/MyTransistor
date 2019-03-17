#include"Map.h"
Scene *Map::InitMap(const char* file_name)
{
	TiXmlDocument myDocument;
	myDocument.LoadFile(file_name);
	if (!myDocument.LoadFile(file_name))
	{
		cout << "初始化失败！" << endl;
	}
	TiXmlElement *game = myDocument.RootElement();
	TiXmlElement *Map = game->FirstChildElement("map");
	Scene *scene = new Scene;
	Scene *scene_list=scene->InitScene(file_name, Map);
	delete scene;
	return scene_list;
}
void Map::output_scene(Scene *scene_list)
{
	scene_list->output(scene_list);
}
void Map::output_NPC(string name, Scene *head)
{
	if (!(scene_list->output_NPC(name, head)))
		cout << "查无此人！"<<endl;
}
