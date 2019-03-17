#include"Monster.h"
Monster *Monster::InitMonster(const char* file_name, TiXmlElement *scene_element)
{
	Monster *head = NULL, *tail;
	TiXmlElement *monsters = scene_element->FirstChildElement("monsters");
	if (!monsters)
		return NULL;
	else {
		TiXmlElement *monster = monsters->FirstChildElement("monster");
		while (monster)
		{
			Monster *p = new Monster;
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
			p->dizzy = 0;
			p->load = 0;
			p->repeat_2_remain = 0;
			p->repeat_3_remain = 0;
			p->weaken = 0;
			p->skip = 0;
			if(monster_special)
				p->special = monster_special->GetText();
			p->next = NULL;
			if (head == NULL)
				head = tail = p;
			else
			{
				tail->next = p;
				tail = p;
			}
			monster = monster->NextSiblingElement("monster");
		}
		return head;
	}
}
void Monster::One_Attack_by_Hero(int Hero_attack,int set, Skill skill_list[])
{
	int before_Hp = HP;
	if (weaken != 0)
	{
		Defense = Defense * 3 / 4;
		Attack = Attack * 3 / 4;
		weaken--;
		if (weaken == 0)
		{
			Defense = Defense * 4 / 3;
			Attack = Attack * 4 / 3;
		}
	}
	if (skip != 1)
	{
		int actual_output = (rand() % ((Hero_attack - Defense) * 3 - (Hero_attack - Defense) / 2 + 1)) + (Hero_attack - Defense) / 2;
		if (set == 0)
		{
			HP -= actual_output;
			if (actual_output < (Hero_attack - Defense) * 3 / 5)
				cout << "你向进程打了个哈欠，进程感到了困倦，失去了" << actual_output << "点耐久度。（进程还剩"
				<< HP << "点耐久度)" << endl;
			else if (actual_output < (Hero_attack - Defense) * 3 / 4)
				cout << "你对进程扔出了一块石头，进程失去了" << actual_output << "点耐久度。（进程还剩"
				<< HP << "点耐久度)" << endl;
			else if (actual_output < (Hero_attack - Defense) * 3 / 2)
				cout << "你接住了进程发射的动感光波，并弹了回去，进程损失了" << actual_output << "点耐久度。（进程还剩"
				<< HP << "点耐久度)" << endl;
			else if (actual_output < (Hero_attack - Defense) * 5 / 2)
				cout << "你微微一笑，使出了奥义必杀，优雅地将晶体管向Process丢去，进程吓了一跳后损失了" << actual_output << "点耐久度。（进程还剩"
				<< HP << "点耐久度，你趁进程没缓过来又将晶体管捡回来)" << endl;
			else
				cout << "你运用毕生所学，在十五秒内写出了一个脚本并安装到进程身上，对方躲闪不及，出了一大堆BUG，损失了" << actual_output << "点耐久度。（进程还剩"
				<< HP << "点耐久度)" << endl;

		}
		else change_monster_state_and_attack(set, actual_output, skill_list);
		if (load != 0&& before_Hp != HP)
		{
			HP -= 250*load;
			cout << "你的攻击引爆了进程身上的数据包，只见进程被爆炸力和冲击波震上了天，失去了" << 250 * load << "点耐久度。（进程还剩"
				<< HP << "点耐久度)" << endl;
			load = 0;
		}
		if (repeat_2_remain != 0)
		{
			if (repeat_2_remain == 2);
			else {
				HP -= 60;
				cout << "你的Flood()函数继续裹挟着进程，进程再次失去了" << 60 << "点耐久度。（进程还剩"
					<< HP << "点耐久度)" << endl;
			}
			repeat_2_remain--;
		}
		if (repeat_3_remain != 0)
		{
			if (repeat_3_remain == 3);
			else{
			HP -= 40;
			repeat_3_remain--;
			cout << "你的Purge()函数制造的病毒继续蚕食着进程，进程几乎故障，失去了" << 60 << "点耐久度。（进程还剩"
				<< HP << "点耐久度)" << endl;
			}
			repeat_3_remain--;
		}
	}
	else
		cout << "你躲在面具下仔细的研究着进程的构造。" << endl;
	skip = 0;
}
int Monster::get_attack()
{
	return Attack;
}
bool Monster::is_win()
{
	if (HP > 0)
		return true;
	else
		return false;
}
bool Monster::is_defeated()
{
	if (HP <= 0)
		return true;
	else
		return false;
}
string Monster::get_name()
{
	return name;
}
int Monster::get_return_exp()
{
	return return_exp;
}
bool Monster::the_game_is_over(Monster *a_monster)
{
	if (a_monster->special == "GAME_VICTORY")
		return true;
	else 
	{
		cout << a_monster->special << endl;
		return false;
	}
}
void Monster::change_monster_state_and_attack(int set, int actual_output, Skill skill_list[])
{
	for (int i = 0; i < 14; i++)
	{
		if (skill_list[i].order == set)
		{
			if (skill_list[i].name == "Crash()")
			{
				dizzy = 1;
				actual_output += skill_list[i].attack;
				HP -= actual_output;
				cout << "你消耗了"<< skill_list[i] .consume<<"点规划值，用晶体管向进程发动了" << skill_list[i].name << ",进程在噩梦般的橙光中感到一阵晕厥,失去了" << actual_output << "点耐久度。（进程还剩"
					<< HP << "点耐久度)" << endl;
			}
			else if (skill_list[i].name == "Breach()")
			{
				actual_output += skill_list[i].attack;
				HP -= actual_output;
				cout << "你消耗了" << skill_list[i].consume << "点规划值，用晶体管向进程发动了" << skill_list[i].name << ",发现了进程的弱点，并远远地向它的弱点射了一束高能量子炮,进程在一阵抽搐后失去了" << actual_output << "点耐久度。（进程还剩"
					<< HP << "点耐久度)" << endl;
			}
			else if (skill_list[i].name == "Spark()")
			{
				actual_output += skill_list[i].attack;
				HP -= actual_output;
				cout << "你消耗了" << skill_list[i].consume << "点规划值，用晶体管向进程发动了" << skill_list[i].name << ",随着晶体管喷射出一团巨大的蓝色能量团，进程被击中后失去了" << actual_output << "点耐久度。（进程还剩"
					<< HP << "点耐久度)" << endl;
				srand((unsigned)time(NULL));
				int chance = rand() % 100;
				if (chance <= 50)
				{
					HP -= 20;
					cout << "蓝色能量落地分裂成了无数小能量团，进程再次被击中，失去了" << 20 << "点耐久度。（进程还剩"
						<< HP << "点耐久度)" << endl;
				}
			}
			else if (skill_list[i].name == "Mask()")
			{
				cout << "你消耗了" << skill_list[i].consume << "点规划值，用晶体管向进程发动了" << skill_list[i].name << ",你借助晶体管的伪透明技术在近处观察进程的构造，进程有些摸不着头脑。" << endl;
				skip = 1;
			}
			else if (skill_list[i].name == "Help()")
			{
				actual_output += skill_list[i].attack;
				HP -= actual_output;
				cout << "你消耗了" << skill_list[i].consume << "点规划值，用晶体管向进程发动了" << skill_list[i].name << ",你的晶体管不知从哪儿召唤出了一只进程狗狗，它发出了重金属乐般的吠叫声向敌对进程狠狠冲了过去，敌方措手不及，被远远撞飞后失去了" << actual_output << "点耐久度。（进程还剩"
					<< HP << "点耐久度)" << endl;
			}
			else if (skill_list[i].name == "Load()")
			{
				load++;
				cout << "你消耗了" << skill_list[i].consume << "点规划值，向进程发动了" << skill_list[i].name << ",进程被你加载了一个数据包,即将引爆（进程还剩"
					<< HP << "点耐久度)" << endl;
			}
			else if (skill_list[i].name == "Ping()")
			{
				actual_output += (skill_list[i].attack * 4);
				HP -= actual_output;
				cout << "你消耗了" << skill_list[i].consume << "点规划值，用晶体管向进程发动了" << skill_list[i].name << ",晶体管迅速发射出四道次声脉冲波，进程的拟耳被震得粉碎，进程失去了" << actual_output << "点耐久度。（进程还剩"
					<< HP << "点耐久度)" << endl;
			}
			else if (skill_list[i].name == "Cull()")
			{
				actual_output += skill_list[i].attack;
				HP -= actual_output;
				cout << "你消耗了" << skill_list[i].consume << "点规划值，用晶体管向进程发动了" << skill_list[i].name << ",凭空跃起，晶体管的一端随着你的臂摆全速上升，重重地打在进程身上，进程失去了" << actual_output << "点耐久度。（进程还剩"
					<< HP << "点耐久度)" << endl;
			}
			else if (skill_list[i].name == "Flood()")
			{
				actual_output += skill_list[i].attack;
				HP -= actual_output;
				repeat_2_remain += 2;
				cout << "你消耗了" << skill_list[i].consume << "点规划值，用晶体管向进程发动了" << skill_list[i].name << ",晶体管制造了一个溢出的纯黑实体栈，并向着进程的CPU飞去，转眼间，进程都被实体栈所包裹，失去了" << actual_output << "点耐久度。（进程还剩"
					<< HP << "点耐久度)" << endl;
			}
			else if (skill_list[i].name == "Purge()")
			{
				actual_output += skill_list[i].attack;
				HP -= actual_output;
				repeat_3_remain += 3;
				cout << "你消耗了" << skill_list[i].consume << "点规划值，用晶体管向进程发动了" << skill_list[i].name << ",晶体管喷射出一束浅粉色的病毒团，病毒寄生在了进程身上，进程失去了" << actual_output << "点耐久度。（进程还剩"
					<< HP << "点耐久度)" << endl;
			}
			else if (skill_list[i].name == "Tap()")
			{
				actual_output += skill_list[i].attack;
				HP -= actual_output;
				cout << "你消耗了" << skill_list[i].consume << "点规划值，用晶体管向进程发动了" << skill_list[i].name << ",晶体管制造出一个七彩缤纷的能量场，进程被卷入其中，失去了" << actual_output << "点耐久度。（进程还剩"
					<< HP << "点耐久度)" << endl;//这儿涉及对英雄的操作
			}
			else if (skill_list[i].name == "Void()")
			{
				weaken += 3;
				cout << "你消耗了" << skill_list[i].consume << "点规划值，用晶体管向进程发动了" << skill_list[i].name << ",进程的鲁棒性被晶体管发出的无线电波所扰乱,各属性值均下降。" << endl;
			}
			else if (skill_list[i].name == "Get()")
			{
				skip = 1;
				actual_output += skill_list[i].attack;
				HP -= actual_output;
				cout << "你消耗了" << skill_list[i].consume << "点规划值，用晶体管向进程发动了" << skill_list[i].name << ",随着晶体管释放出一个强大的白色磁场，进程被吸附到了你的身边，并被强磁力损坏了硬件，失去了" << actual_output << "点耐久度。（进程还剩"
					<< HP << "点耐久度)" << endl;
			}
			else if (skill_list[i].name == "Kill()")
			{
				srand((unsigned)time(NULL));
				int chance = rand() % 100;
				if (chance <= 50)
				{
					actual_output += skill_list[i].attack;
					HP -= actual_output;
					cout << "你消耗了" << skill_list[i].consume << "点规划值，用晶体管向进程发动了" << skill_list[i].name << ",你化身超级用户，背部生出天使之翼，迅速通过了晶体管的root权限后，获得了一只KILL魔杖，向进程念了一句古老的咒语，电光火石之间，一阵魔法光束击中了进程，进程失去了" << actual_output << "点耐久度。（进程还剩"
						<< HP << "点耐久度)" << endl;
				}
				else
					cout << "你消耗了" << skill_list[i].consume << "点规划值，用晶体管向进程发动了" << skill_list[i].name << "，却忘记了管理员密码，晶体管与进程都没有丝毫反应。（进程还剩"
					<< HP << "点耐久度)" << endl;
			}
		}
	}
}
