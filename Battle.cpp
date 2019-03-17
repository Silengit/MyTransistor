#include"Battle.h"
void wait(int m_seconds)
{
	clock_t endwait;
	endwait = clock() + m_seconds / 1000.0*CLOCKS_PER_SEC;
	while (clock() < endwait) {};
}
void Battle::An_attack_in_one_Battle(Hero &hero, Monster *&monster,Skill skill_list[])
{
	Skill skillsystem;
	cout << "请规划你的动作：(使用技能键或是普通攻击（普通攻击按0）)" << endl;
	skillsystem.output_current_skills(skill_list);
	int set;
	cin >> set;
	while ((set != 0)&&(skillsystem.no_access_to_the_skill(skill_list,set)))
	{
		cout << "Red,仔细想想，你似乎没有这种操作。换个指令吧：";
		cin >> set;
	}
	while ((set!=0)&&(!hero.MP_IS_ENOUGH(set, skill_list)))
	{
		cout << "Red,你的规划值不够你调用这个函数了!请重新规划:"<<endl;
		cin >> set;
	}
	int mon_atc = monster->get_attack();
	int hero_atc = hero.get_attack();
	monster->One_Attack_by_Hero(hero_atc, set, skill_list);
	//wait(1000);
	if (!(battle_is_over(hero, monster)))
		hero.One_Attack_by_Monster(mon_atc, set, skill_list);
	//wait(1000);
}
bool Battle::battle_is_over(Hero &hero, Monster *&monster)
{
	if (hero.is_win() || monster->is_win())
	{
		return true;
	}
}
bool Battle::claim_the_result_of_the_battle(Hero &hero, Monster *&monster, Skill skill_list[])
{
	if (hero.is_win())
	{
		cout << "你击败了[" << monster->get_name() << "],获得经验" << monster->get_return_exp()<<endl;
		hero.victory(monster->get_return_exp());
		if (hero.is_level_up())
		{
			hero.level_up(skill_list);
		}
		if (monster->the_game_is_over(monster))
		{
			cout << "（打败Grant后，Red操作晶体管通过指挥台恢复了城市的原貌，进程们终于开始正常工作了）Red,你做到了。我为你骄傲。可是接下来呢，我们去哪呢？先去金色大街？还是回到旅馆？等等，Red,你不能这样。听我说，Red，你怎么敢。（Red操纵晶体管刺向自己，和男人以同样的姿势永远地依靠在了墙角边。）不，你做了什么,Red..." << endl;
			return 1;
		}
		else return 0;
	}
	else
	{
		if (monster->get_name() == "Grant")
		{
			cout << "Grant从你手中夺过了晶体管。你误解他了，他还是用晶体管恢复了城市的秩序。他只是想要你的声音，从一开始就是这样。结果你滥用晶体管，使得越来越多的进程失去控制，甚至一些进程还发生了可怕的变异！后来，Grant在城市里将你描述成了可怕的疯子，而他自己则是救世主。你郁郁寡欢，终于有一天，男人的声音也离你而去...ByeBye..world..." << endl;
			return 1;
		}
		else{
		cout << "你被[" << monster->get_name() << "]打败了。" << endl;
		cout << "你被怪物打败了。" << endl;
		cout << "游戏结束。"<<endl;
		return 1;
		}
	}
}
bool Battle::one_battle(Hero &hero, Monster *&monster,Skill skill_list[])
{
	srand((unsigned)time(NULL));
	while (!hero.is_defeated()&&!monster->is_defeated())
	{
		An_attack_in_one_Battle(hero, monster, skill_list);
	}
	if (battle_is_over(hero, monster))
	{
		if (claim_the_result_of_the_battle(hero, monster, skill_list))
			return 1;
		else
			return 0;
	}
}
