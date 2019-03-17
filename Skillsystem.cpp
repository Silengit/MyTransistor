#include"Skillsystem.h"
Skill *Skill::Init_skills(const char* file_name)
{
	Skill *skill_list=new Skill[14];
	TiXmlDocument myDocument;
	myDocument.LoadFile(file_name);
	if (!myDocument.LoadFile(file_name))
	{
		cout << "��ʼ��ʧ�ܣ�" << endl;
	}
	TiXmlElement *game = myDocument.RootElement();
	TiXmlElement *skills = game->FirstChildElement("skills");
	TiXmlElement *skill = skills->FirstChildElement("skill");
	int index = 0;
	while (skill)
	{
		TiXmlElement *skill_name = skill->FirstChildElement("name");
		TiXmlElement *skill_damage = skill->FirstChildElement("damage");
		TiXmlElement *skill_consume = skill->FirstChildElement("consume");
		TiXmlElement *skill_special = skill->FirstChildElement("special");
		skill_list[index].name = skill_name->GetText();
		skill_list[index].attack = atoi(skill_damage->GetText());
		skill_list[index].consume = atoi(skill_consume->GetText());
		if (skill_special)
			skill_list[index].special = skill_special->GetText();
		skill_list[index].equiped = 0;
		skill_list[index].order = 0;
		skill_list[index].have = 0;
		index++;
		skill = skill->NextSiblingElement("skill");
	}
	return skill_list;
}
bool Skill::output_newskills(int level,Skill skill_list[])
{
	if (level == 2)
		cout << "1.Crash():�����˺�50�����Ĺ滮ֵ20������Ч����ѣ�ν���һ�غ�" << endl
		<< "2.Breach():�����˺�100�����Ĺ滮ֵ42������Ч������Զ���빥����" << endl;
	else if (level == 3)
		cout << "1.Spark():�����˺�60�����Ĺ滮ֵ20������Ч������ը����Ƭ��Խ�����ɶ����˺�" << endl
		<< "2.Mask():�����˺�0�����Ĺ滮ֵ0������Ч��������һ�غ�" << endl;
	else if (level == 4)
		cout << "1.Help():�����˺�75�����Ĺ滮ֵ25������Ч�����ٻ�һ�����̻����Э����" << endl
		<< "2.Load():�����˺�0�����Ĺ滮ֵ50������Ч��������һ�غ��������Խ������250���˺�" << endl;
	else if (level == 5)
		cout << "1.Ping():�����˺�15�����Ĺ滮ֵ10������Ч������һ���غ����������Ĵ�" << endl
		<< " 2.Cull():�����˺�225�����Ĺ滮ֵ70������Ч���������˺���" << endl;
	else if (level == 6)
		cout << "1.Flood():�����˺�60�����Ĺ滮ֵ25������Ч���������̹�Ю�����غ�" << endl
		<< "2.Purge():�����˺�40�����Ĺ滮ֵ20������Ч�����ڽ����ڼ��������غ�" << endl;
	else if (level == 7)
		cout << "1.Tap():�����˺�150�����Ĺ滮ֵ35������Ч������ȡ����1%�Ĵ�����ת��Ϊ��������" << endl
		<< "2.Void():�����˺�0�����Ĺ滮ֵ15������Ч�����������̣����������½�25%������4�غ�" << endl;
	else if (level == 8)
		cout << "1.Get():�����˺�150�����Ĺ滮ֵ10������Ч�����ú����Ὣ���������Լ����" << endl
		<< "2.Kill():�����˺�500�����Ĺ滮ֵ80������Ч������һ�����ʹ���" << endl;
	else
	{
		int ctr = 0;
		for (int i = 0; i < 14; i++)
		{
			if (ctr == 2)
				break;
			if (skill_list[i].have == 0)
			{
				ctr++;
				cout << ctr << "." << skill_list[i].name << ":�����˺�:" << skill_list[i].attack << "�����Ĺ滮ֵ" << skill_list[i].consume << "������Ч��:" << skill_list[i].special << endl;
			}
		}
		if (ctr == 0)
		{
			cout << "û���¼��ܿɻ�á�(��������ָ��)" << endl;
			return false;
		}
	}
	return true;
}
int  Skill::choose_the_skill(int index, int level, Skill skill_list[])
{
	if (level == 2)
	{
		if (index == 1)
		{
			skill_list[0].equiped = 1;
			skill_list[0].have = 1;
		}
		else {
			skill_list[1].equiped = 1;
			skill_list[1].have = 1;
		}
	}
	else if (level == 3)
	{
		if (index == 1) {
			skill_list[2].equiped = 1;
			skill_list[2].have = 1;
		}
		else {
			skill_list[3].equiped = 1;
			skill_list[3].have = 1;
		}
	}
	else if (level == 4)
	{
		if (index == 1) {
			skill_list[4].equiped = 1;
			skill_list[4].have = 1;
		}
		else {
			skill_list[5].equiped = 1;
			skill_list[5].have = 1;
		}
	}
	else if (level == 5)
	{
		if (index == 1) {
			skill_list[6].equiped = 1;
			skill_list[6].have = 1;
		}
		else {
			skill_list[7].equiped = 1;
			skill_list[7].have = 1;
		}
	}
	else if (level == 6)
	{
		if (index == 1) {
			skill_list[8].equiped = 1;
			skill_list[8].have = 1;
		}
		else {
			skill_list[9].equiped = 1;
			skill_list[9].have = 1;
		}
	}
	else if (level == 7)
	{
		if (index == 1) {
			skill_list[10].equiped = 1;
			skill_list[10].have = 1;
		}
		else {
			skill_list[11].equiped = 1;
			skill_list[11].have = 1;
		}
	}
	else if (level == 8)
	{
		if (index == 1) {
			skill_list[12].equiped = 1;
			skill_list[12].have = 1;
		}
		else {
			skill_list[13].equiped = 1;
			skill_list[13].have = 1;
		}
	}
	else
	{
		int ctr = 0;
		for (int i = 0; i < 14; i++)
		{
			if (ctr == 2)
				break;
			if (skill_list[i].have == 0)
			{
				ctr++;
				if (index == ctr)
				{
					skill_list[i].have = 1; 
					skill_list[i].equiped = 1;
					return i;
				}
				else continue;
			}
		}
	}
}
void Skill::output_current_skills(Skill skill_list[])
{
	int index = 0;
	for (int i = 0; i < 14; i++)
	{
		if (skill_list[i].equiped == 1&& skill_list[i].order!=0)
		{
			index++;
			cout << index << ".    ���ܺ������:" << i
				<< ".    ���ܺ�����:" << skill_list[i].name
				<< "   �����˺�ֵ��" << skill_list[i].attack
				<< "   ���Ĺ滮ֵ��" << skill_list[i].consume
				<< "  ���ܼ�λ��" << skill_list[i].order << endl;
		}
	}
}
bool Skill::replace_the_index_skill(int index, int level, int i, Skill skill_list[],int num)
{
	if (skill_list[index].equiped != 1)
		return false;
	else if (level <= 8) 
	{
		skill_list[index].equiped = 0;
		skill_list[level * 2 + i - 5].equiped = 1;
		skill_list[level * 2 + i - 5].order = skill_list[index].order;
		skill_list[index].order = 0;
	}
	else
	{
		skill_list[index].equiped = 0;
		skill_list[num].equiped = 1;
		skill_list[num].order = skill_list[index].order;
		skill_list[index].order = 0;
	}
	return true;
}
void Skill::set_the_order_of_new_skill(int set, int level, int i, Skill skill_list[],int num)
{
	if(level <= 8)
		skill_list[level * 2 + i - 5].order = set;
	else
		skill_list[num].order = set;
}
bool  Skill::skill_spot_is_full(Skill skill_list[])
{
	int sum = 0;
	for (int i = 0; i < 14; i++)
	{
		if (skill_list[i].equiped == 1)
			sum++;
	}
	if (sum == 5)
		return true;
	else
		return false;
}
bool Skill::no_access_to_the_skill(Skill skill_list[], int set)
{
	for (int i = 0; i < 14; i++)
	{
		if (skill_list[i].order == set)
			return false;
	}
	return true;
}
void Skill::delete_the_access_to_the_skill(Skill skill_list[], int i,int level,int num)
{
	if (level <= 8)
		skill_list[level * 2 + i - 5].equiped = 0;
	else
		skill_list[num].equiped = 0;
}
bool Skill::the_set_has_been_used(Skill skill_list[], int set)
{
	for (int i = 0; i < 14; i++)
	{
		if (skill_list[i].order == set)
			return true;
	}
	return false;
}