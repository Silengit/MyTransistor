#include"NPC.h"
NPC *NPC:: InitNPC(const char* file_name, TiXmlElement *scene_element)
{
	NPC *head = NULL, *tail;
	TiXmlElement *NPCs = scene_element->FirstChildElement("NPCs");
	if (!NPCs)
		return NULL;
	else{
	TiXmlElement *NPC_element = NPCs->FirstChildElement("NPC");
	while(NPC_element)
	{
		NPC *p = new NPC;
		TiXmlElement *NPC_name = NPC_element->FirstChildElement("name");
		TiXmlElement *NPC_talk = NPC_element->FirstChildElement("talk");
		p->name = NPC_name->GetText();
		p->talk = NPC_talk->GetText();
		p->next = NULL;
		if (head == NULL)
			head = tail = p;
		else
		{
			tail->next = p;
			tail = p;
		}
		NPC_element = NPC_element->NextSiblingElement("NPC");
	}
	return head;
	}
}
bool NPC::output(string NPC_name,NPC *head)
{
	for (NPC *p = head; p; p = p->next)
	{
		if (p->name == NPC_name)
		{
			cout << p->talk << endl;
			return true;
		}
	}
	return false;
}