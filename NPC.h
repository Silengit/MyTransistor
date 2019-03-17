#pragma once
#include"tinystr.h"
#include"tinyxml.h"
#include <iostream>
#include<string>
using namespace std;
class NPC
{
public:
	NPC *InitNPC(const char* file_name, TiXmlElement *scene_element);
	bool output(string NPC_name,NPC *head);
private:
	string name;
	string talk;
	NPC *next;
};

