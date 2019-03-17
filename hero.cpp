#include "hero.h"
bool Hero::InitHero(const char* file_name)
{
	TiXmlDocument myDocument;
	myDocument.LoadFile(file_name);
	if (!myDocument.LoadFile(file_name))
	{
		cout << "初始化失败！"<<endl;
		return false;
	}
	TiXmlElement *game = myDocument.RootElement();
	TiXmlElement *hero = game->FirstChildElement("hero");
	TiXmlElement *hero_name=hero->FirstChildElement("name");
	TiXmlElement *hero_level = hero->FirstChildElement("level");
	TiXmlElement *hero_MAX_HP = hero->FirstChildElement("MAX_HP");
	TiXmlElement *hero_current_HP = hero->FirstChildElement("current_HP");
	TiXmlElement *hero_MAX_MP = hero->FirstChildElement("MAX_MP");
	TiXmlElement *hero_current_MP = hero->FirstChildElement("current_MP");
	TiXmlElement *hero_Attack = hero->FirstChildElement("atk");
	TiXmlElement *hero_Defense = hero->FirstChildElement("def");
	TiXmlElement *hero_exp = hero->FirstChildElement("exp");
	TiXmlElement *hero_exp_for_per_level_up = hero->FirstChildElement("expPerLvl");
	TiXmlElement *hero_increse_of_Attack_per_level_up = hero->FirstChildElement("atkPerLvl");
	TiXmlElement *hero_increse_of_Defense_per_level_up = hero->FirstChildElement("defPerLvl");
	TiXmlElement *hero_increse_of_HP_per_level_up = hero->FirstChildElement("hpPerLvl");
	TiXmlElement *hero_increse_of_MP_per_level_up = hero->FirstChildElement("mpPerLvl");
	name = hero_name->GetText();
	level = atoi(hero_level->GetText());
	MAX_HP = atoi(hero_MAX_HP->GetText());
	current_HP = atoi(hero_current_HP->GetText());
	MAX_MP = atoi(hero_MAX_MP->GetText());
	current_MP = atoi(hero_current_MP->GetText());
	Attack = atoi(hero_Attack->GetText());
	Defense = atoi(hero_Defense->GetText());
	exp = atoi(hero_exp->GetText());
	increse_of_HP_per_level_up = atoi(hero_increse_of_HP_per_level_up->GetText());
	increse_of_MP_per_level_up = atoi(hero_increse_of_MP_per_level_up->GetText());
	increse_of_Attack_per_level_up = atoi(hero_increse_of_Attack_per_level_up->GetText());
	increse_of_Defense_per_level_up = atoi(hero_increse_of_Defense_per_level_up->GetText());
	exp_for_per_level_up = atoi(hero_exp_for_per_level_up->GetText());
	skip=0;
	dizzy = 0;
	weaken = 0;
}
void Hero::Show_Status_Of_Battle()
{
	cout << "Hi,"<<name<<"，你已经到达了"<<level<<"级，剩余体力为" << current_HP << ",剩余规划值为" << current_MP << ",当前基础伤害" << Attack << ",抵御力" << Defense<<
		",经验值"<<exp<<"。祝您在代码世界玩的愉快！"<<endl;
}
void Hero::One_Attack_by_Monster(int Monster_attack,int set, Skill skill_list[])
{
	if (set != 0)
	{
		for (int i = 0; i < 14; i++)
		{
			if (skill_list[i].order == set)
			{
				current_MP -= skill_list[i].consume;
				if (skill_list[i].special == "skip" )
				{
					skip = 1;
					break;
				}
				else if (skill_list[i].special == "dizzy")
				{
					dizzy = 1;
					break;
				} 
				else if (skill_list[i].special == "absorb")
				{
					current_HP += 5;
					break;
				}
				break;
			}
		}
	}
	if (weaken != 0)
	{
		Monster_attack = Monster_attack * 3 / 4;
		weaken--;
		if (weaken == 0)
		{
			Monster_attack = Monster_attack * 4 / 3;
		}
	}
	if(skip==0&&dizzy==0)
	{ 
		int actual_output = (rand() % ((Monster_attack - Defense) * 3- (Monster_attack - Defense) / 2 + 1)) + (Monster_attack - Defense) / 2;
		current_HP -= actual_output;
		if(actual_output<(Monster_attack - Defense) * 3/5)
			cout << "进程机器人挠了你一下，你被逗得哈哈大笑，顺带失去了" << actual_output << "点体力。（你还剩"
			<< current_HP << "点体力," << current_MP << "规划值)" << endl;
		else if(actual_output<(Monster_attack - Defense)*3/4)
			cout << "进程机器人轻轻撞了你一下，你失去了" << actual_output << "点体力。（你还剩"
			<< current_HP << "点体力,"<< current_MP<<"规划值)" << endl;
		else if(actual_output<(Monster_attack - Defense) * 3 / 2)
			cout << "进程机器人向你使出了一记重拳，你损失了" << actual_output << "点体力。（你还剩"
			<< current_HP << "点体力," << current_MP << "规划值)" << endl;
		else if ( actual_output<(Monster_attack - Defense) * 5/ 2)
			cout << "进程机器人向你发出了动感光波，你受到了重创，损失了" << actual_output << "点体力。（你还剩"
			<< current_HP << "点体力," << current_MP << "规划值)" << endl;
		else
			cout << "进程机器人凝神屏气，全力打出了雷霆一击，你被击倒在地，损失了" << actual_output << "点体力。（你还剩"
			<< current_HP << "点体力," << current_MP << "规划值)" << endl;
	}
	if (skip == 1)
	{
		cout << "进程机器人看不见你，看上去有些摸不着头脑。" << endl;
		skip = 0;
	}
	if (dizzy == 1)
	{
		cout<< "进程机器人被你打晕了，一动不动。" << endl;
		dizzy = 0;
	}
}
void Hero::victory(int exp_of_Monster)
{
	exp += exp_of_Monster;
}
void Hero::level_up(Skill skill_list[])
{
	Skill skillsystem;
	cout << "恭喜您。升到了"<< level+1<<"级！您的属性得到了大幅提高，请查看您的属性。" << endl;
	level++;
	MAX_HP += increse_of_HP_per_level_up;
	current_HP = MAX_HP;
	MAX_MP += increse_of_MP_per_level_up;
	current_MP = MAX_MP;
	Attack += increse_of_Attack_per_level_up;
	Defense += increse_of_Defense_per_level_up;
	if (level <= 8)
	{
		if (level <= 5)
			cout << "您获得了一个新的技能槽！" << endl;
		cout << "下面是两个新的技能函数，请选择其中一个：(输入序号)" << endl;
		skillsystem.output_newskills(level, skill_list);
		int i;
		cin >> i;
		while (i != 1 && i != 2)
		{
			cout << "Red,你只有两种选择。重新读取：";
			cin >> i;
		}
		int num;
		num=skillsystem.choose_the_skill(i, level, skill_list);
		if (skillsystem.skill_spot_is_full(skill_list))
		{
			cout << "您的技能槽已满，需要替换吗？(0:不替换；1：替换)" << endl;
			int yes;
			cin >> yes;
			while (yes != 1 && yes != 0)
			{
				cout << "Red,输入错误。重新读取：";
				cin >> yes;
			}
			if (yes==1)
			{
				skillsystem.output_current_skills(skill_list);
				cout << "请选择您要替换的技能函数序号：" << endl;
				int index;
				cin >> index;
				while (!skillsystem.replace_the_index_skill(index, level, i, skill_list, num))
				{
					cout << "Red,请选择已装备的技能函数！重新读取：";
					cin >> index;
				}
			}
			else
				skillsystem.delete_the_access_to_the_skill(skill_list, i, level,num);
		}
		else
		{
			cout << "请设置新技能的使用键（1到4）" << endl;
			int set;
			cin >> set;
			while (skillsystem.the_set_has_been_used(skill_list, set))
			{
				cout << "Red,我们已经设置过同样的按键了。重新读取：";
				cin >> set;
			}
			while (set != 1 && set != 2 && set != 3 && set != 4)
			{
				cout << "Red,不要超出你的操作权限。重新读取：" ;
				cin >> set;
			}
			skillsystem.set_the_order_of_new_skill(set, level, i, skill_list,num);
		}
	}
	else
	{
		cout << "下面是两个新的技能函数，请选择其中一个：(输入序号)" << endl;
		if (skillsystem.output_newskills(level, skill_list))
		{
			int i;
			cin >> i;
			int num;
			num=skillsystem.choose_the_skill(i, level, skill_list);
			cout << "您的技能槽已满，需要替换吗？(0:不替换；1：替换)" << endl;
			int yes;
			cin >> yes;
			while (yes != 1 && yes != 0)
			{
				cout << "Red,输入错误。重新读取：";
				cin >> yes;
			}
			if (yes==1)
			{
				skillsystem.output_current_skills(skill_list);
				cout << "请选择您要替换的技能函数序号：" << endl;
				int index;
				cin >> index;
				skillsystem.replace_the_index_skill(index, level, i, skill_list,num);
			}
			else
				skillsystem.delete_the_access_to_the_skill(skill_list, i, level,num);
		}
	}
}

bool Hero::is_level_up()
{
	if (exp >= exp_for_per_level_up*level )
		return true;
	else return false;
}
int Hero::get_attack()
{
	return Attack;
}
bool Hero::is_win()
{
	if (current_HP > 0)
		return true;
	else
		return false;
}
bool Hero::is_defeated()
{
	if (current_HP <= 0)
		return true;
	else
		return false;
}
bool Hero::MP_IS_ENOUGH(int set,Skill skill_list[])
{
	for (int i = 0; i < 14; i++)
	{
		if (skill_list[i].order == set)
		{
			if (current_MP < skill_list[i].consume)
				return false;
			else
				return true;
		}
	}
}

