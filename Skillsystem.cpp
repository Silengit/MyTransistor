#include"Skillsystem.h"
Skill *Skill::Init_skills(const char* file_name)
{
	Skill *skill_list=new Skill[14];
	TiXmlDocument myDocument;
	myDocument.LoadFile(file_name);
	if (!myDocument.LoadFile(file_name))
	{
		cout << "初始化失败！" << endl;
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
		cout << "1.Crash():基础伤害50，消耗规划值20，特殊效果：眩晕进程一回合" << endl
		<< "2.Breach():基础伤害100，消耗规划值42，特殊效果：超远距离攻击！" << endl;
	else if (level == 3)
		cout << "1.Spark():基础伤害60，消耗规划值20，特殊效果：爆炸的碎片会对进程造成额外伤害" << endl
		<< "2.Mask():基础伤害0，消耗规划值0，特殊效果：隐身一回合" << endl;
	else if (level == 4)
		cout << "1.Help():基础伤害75，消耗规划值25，特殊效果：召唤一个进程伙伴来协助你" << endl
		<< "2.Load():基础伤害0，消耗规划值50，特殊效果：在下一回合引爆后会对进程造成250点伤害" << endl;
	else if (level == 5)
		cout << "1.Ping():基础伤害15，消耗规划值10，特殊效果：在一个回合连续喷射四次" << endl
		<< " 2.Cull():基础伤害225，消耗规划值70，特殊效果：大量伤害！" << endl;
	else if (level == 6)
		cout << "1.Flood():基础伤害60，消耗规划值25，特殊效果：将进程裹挟两个回合" << endl
		<< "2.Purge():基础伤害40，消耗规划值20，特殊效果：在进程内寄生三个回合" << endl;
	else if (level == 7)
		cout << "1.Tap():基础伤害150，消耗规划值35，特殊效果：吸取进程1%的代码量转化为自身体力" << endl
		<< "2.Void():基础伤害0，消耗规划值15，特殊效果：削弱进程，各项属性下降25%，持续4回合" << endl;
	else if (level == 8)
		cout << "1.Get():基础伤害150，消耗规划值10，特殊效果：该函数会将进程拉到自己身边" << endl
		<< "2.Kill():基础伤害500，消耗规划值80，特殊效果：有一定几率过载" << endl;
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
				cout << ctr << "." << skill_list[i].name << ":基础伤害:" << skill_list[i].attack << "，消耗规划值" << skill_list[i].consume << "，特殊效果:" << skill_list[i].special << endl;
			}
		}
		if (ctr == 0)
		{
			cout << "没有新技能可获得。(不用输入指令)" << endl;
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
			cout << index << ".    技能函数序号:" << i
				<< ".    技能函数名:" << skill_list[i].name
				<< "   基础伤害值：" << skill_list[i].attack
				<< "   消耗规划值：" << skill_list[i].consume
				<< "  技能键位：" << skill_list[i].order << endl;
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