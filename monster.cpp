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
				cout << "������̴��˸���Ƿ�����̸е������룬ʧȥ��" << actual_output << "���;öȡ������̻�ʣ"
				<< HP << "���;ö�)" << endl;
			else if (actual_output < (Hero_attack - Defense) * 3 / 4)
				cout << "��Խ����ӳ���һ��ʯͷ������ʧȥ��" << actual_output << "���;öȡ������̻�ʣ"
				<< HP << "���;ö�)" << endl;
			else if (actual_output < (Hero_attack - Defense) * 3 / 2)
				cout << "���ס�˽��̷���Ķ��йⲨ�������˻�ȥ��������ʧ��" << actual_output << "���;öȡ������̻�ʣ"
				<< HP << "���;ö�)" << endl;
			else if (actual_output < (Hero_attack - Defense) * 5 / 2)
				cout << "��΢΢һЦ��ʹ���˰����ɱ�����ŵؽ��������Process��ȥ����������һ������ʧ��" << actual_output << "���;öȡ������̻�ʣ"
				<< HP << "���;öȣ���ý���û�������ֽ�����ܼ����)" << endl;
			else
				cout << "�����ñ�����ѧ����ʮ������д����һ���ű�����װ���������ϣ��Է���������������һ���BUG����ʧ��" << actual_output << "���;öȡ������̻�ʣ"
				<< HP << "���;ö�)" << endl;

		}
		else change_monster_state_and_attack(set, actual_output, skill_list);
		if (load != 0&& before_Hp != HP)
		{
			HP -= 250*load;
			cout << "��Ĺ��������˽������ϵ����ݰ���ֻ�����̱���ը���ͳ�����������죬ʧȥ��" << 250 * load << "���;öȡ������̻�ʣ"
				<< HP << "���;ö�)" << endl;
			load = 0;
		}
		if (repeat_2_remain != 0)
		{
			if (repeat_2_remain == 2);
			else {
				HP -= 60;
				cout << "���Flood()����������Ю�Ž��̣������ٴ�ʧȥ��" << 60 << "���;öȡ������̻�ʣ"
					<< HP << "���;ö�)" << endl;
			}
			repeat_2_remain--;
		}
		if (repeat_3_remain != 0)
		{
			if (repeat_3_remain == 3);
			else{
			HP -= 40;
			repeat_3_remain--;
			cout << "���Purge()��������Ĳ���������ʳ�Ž��̣����̼������ϣ�ʧȥ��" << 60 << "���;öȡ������̻�ʣ"
				<< HP << "���;ö�)" << endl;
			}
			repeat_3_remain--;
		}
	}
	else
		cout << "������������ϸ���о��Ž��̵Ĺ��졣" << endl;
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
				cout << "��������"<< skill_list[i] .consume<<"��滮ֵ���þ��������̷�����" << skill_list[i].name << ",������ج�ΰ�ĳȹ��ие�һ������,ʧȥ��" << actual_output << "���;öȡ������̻�ʣ"
					<< HP << "���;ö�)" << endl;
			}
			else if (skill_list[i].name == "Breach()")
			{
				actual_output += skill_list[i].attack;
				HP -= actual_output;
				cout << "��������" << skill_list[i].consume << "��滮ֵ���þ��������̷�����" << skill_list[i].name << ",�����˽��̵����㣬��ԶԶ����������������һ������������,������һ��鴤��ʧȥ��" << actual_output << "���;öȡ������̻�ʣ"
					<< HP << "���;ö�)" << endl;
			}
			else if (skill_list[i].name == "Spark()")
			{
				actual_output += skill_list[i].attack;
				HP -= actual_output;
				cout << "��������" << skill_list[i].consume << "��滮ֵ���þ��������̷�����" << skill_list[i].name << ",���ž���������һ�ž޴����ɫ�����ţ����̱����к�ʧȥ��" << actual_output << "���;öȡ������̻�ʣ"
					<< HP << "���;ö�)" << endl;
				srand((unsigned)time(NULL));
				int chance = rand() % 100;
				if (chance <= 50)
				{
					HP -= 20;
					cout << "��ɫ������ط��ѳ�������С�����ţ������ٴα����У�ʧȥ��" << 20 << "���;öȡ������̻�ʣ"
						<< HP << "���;ö�)" << endl;
				}
			}
			else if (skill_list[i].name == "Mask()")
			{
				cout << "��������" << skill_list[i].consume << "��滮ֵ���þ��������̷�����" << skill_list[i].name << ",���������ܵ�α͸�������ڽ����۲���̵Ĺ��죬������Щ������ͷ�ԡ�" << endl;
				skip = 1;
			}
			else if (skill_list[i].name == "Help()")
			{
				actual_output += skill_list[i].attack;
				HP -= actual_output;
				cout << "��������" << skill_list[i].consume << "��滮ֵ���þ��������̷�����" << skill_list[i].name << ",��ľ���ܲ�֪���Ķ��ٻ�����һֻ���̹��������������ؽ����ְ�ķͽ�����жԽ��̺ݺݳ��˹�ȥ���з����ֲ�������ԶԶײ�ɺ�ʧȥ��" << actual_output << "���;öȡ������̻�ʣ"
					<< HP << "���;ö�)" << endl;
			}
			else if (skill_list[i].name == "Load()")
			{
				load++;
				cout << "��������" << skill_list[i].consume << "��滮ֵ������̷�����" << skill_list[i].name << ",���̱��������һ�����ݰ�,�������������̻�ʣ"
					<< HP << "���;ö�)" << endl;
			}
			else if (skill_list[i].name == "Ping()")
			{
				actual_output += (skill_list[i].attack * 4);
				HP -= actual_output;
				cout << "��������" << skill_list[i].consume << "��滮ֵ���þ��������̷�����" << skill_list[i].name << ",�����Ѹ�ٷ�����ĵ��������岨�����̵��������÷��飬����ʧȥ��" << actual_output << "���;öȡ������̻�ʣ"
					<< HP << "���;ö�)" << endl;
			}
			else if (skill_list[i].name == "Cull()")
			{
				actual_output += skill_list[i].attack;
				HP -= actual_output;
				cout << "��������" << skill_list[i].consume << "��滮ֵ���þ��������̷�����" << skill_list[i].name << ",ƾ��Ծ�𣬾���ܵ�һ��������ı۰�ȫ�����������صش��ڽ������ϣ�����ʧȥ��" << actual_output << "���;öȡ������̻�ʣ"
					<< HP << "���;ö�)" << endl;
			}
			else if (skill_list[i].name == "Flood()")
			{
				actual_output += skill_list[i].attack;
				HP -= actual_output;
				repeat_2_remain += 2;
				cout << "��������" << skill_list[i].consume << "��滮ֵ���þ��������̷�����" << skill_list[i].name << ",�����������һ������Ĵ���ʵ��ջ�������Ž��̵�CPU��ȥ��ת�ۼ䣬���̶���ʵ��ջ��������ʧȥ��" << actual_output << "���;öȡ������̻�ʣ"
					<< HP << "���;ö�)" << endl;
			}
			else if (skill_list[i].name == "Purge()")
			{
				actual_output += skill_list[i].attack;
				HP -= actual_output;
				repeat_3_remain += 3;
				cout << "��������" << skill_list[i].consume << "��滮ֵ���þ��������̷�����" << skill_list[i].name << ",����������һ��ǳ��ɫ�Ĳ����ţ������������˽������ϣ�����ʧȥ��" << actual_output << "���;öȡ������̻�ʣ"
					<< HP << "���;ö�)" << endl;
			}
			else if (skill_list[i].name == "Tap()")
			{
				actual_output += skill_list[i].attack;
				HP -= actual_output;
				cout << "��������" << skill_list[i].consume << "��滮ֵ���þ��������̷�����" << skill_list[i].name << ",����������һ���߲��ͷ׵������������̱��������У�ʧȥ��" << actual_output << "���;öȡ������̻�ʣ"
					<< HP << "���;ö�)" << endl;//����漰��Ӣ�۵Ĳ���
			}
			else if (skill_list[i].name == "Void()")
			{
				weaken += 3;
				cout << "��������" << skill_list[i].consume << "��滮ֵ���þ��������̷�����" << skill_list[i].name << ",���̵�³���Ա�����ܷ��������ߵ粨������,������ֵ���½���" << endl;
			}
			else if (skill_list[i].name == "Get()")
			{
				skip = 1;
				actual_output += skill_list[i].attack;
				HP -= actual_output;
				cout << "��������" << skill_list[i].consume << "��滮ֵ���þ��������̷�����" << skill_list[i].name << ",���ž�����ͷų�һ��ǿ��İ�ɫ�ų������̱��������������ߣ�����ǿ��������Ӳ����ʧȥ��" << actual_output << "���;öȡ������̻�ʣ"
					<< HP << "���;ö�)" << endl;
			}
			else if (skill_list[i].name == "Kill()")
			{
				srand((unsigned)time(NULL));
				int chance = rand() % 100;
				if (chance <= 50)
				{
					actual_output += skill_list[i].attack;
					HP -= actual_output;
					cout << "��������" << skill_list[i].consume << "��滮ֵ���þ��������̷�����" << skill_list[i].name << ",�㻯�����û�������������ʹ֮��Ѹ��ͨ���˾���ܵ�rootȨ�޺󣬻����һֻKILLħ�ȣ����������һ����ϵ��������ʯ֮�䣬һ��ħ�����������˽��̣�����ʧȥ��" << actual_output << "���;öȡ������̻�ʣ"
						<< HP << "���;ö�)" << endl;
				}
				else
					cout << "��������" << skill_list[i].consume << "��滮ֵ���þ��������̷�����" << skill_list[i].name << "��ȴ�����˹���Ա���룬���������̶�û��˿����Ӧ�������̻�ʣ"
					<< HP << "���;ö�)" << endl;
			}
		}
	}
}
