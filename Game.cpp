#include"Game.h"
Game::Game()
{
	init = 0;
}
void Game::Initialize()
{
	string str;
	cin >> str;
	if (str == "InitGame" || str == "initgame" || str == "INITGAME")
	{
		cout << "��Ϸ��ʼ����ɡ���ʼ����Ϸ��" << endl;
		cout << "��Ϸ����ָ�:ShowStatus+SCENE/BATTLE��Talk+���GoTo+�ص㣨�������ɻ��ݣ���Attack+����" << endl;
		cout << endl;
		cout << "Red,��������...(������ָ��ShowStatus SCENE)" << endl;
	}
}
Scene *Game::receive_the_order(string order, Hero &hero, Map &map, Battle &battle, Monster *monster, Scene *Scene_list, Skill skill_list[])
{
	string object;
	if (order == "ShowStatus" || order == "showstatus" || order == "Showstatus" || order == "showStatus" || order == "SHOWSTATUS")
	{
		cin >> object;
		{
			if (object == "SCENE" || object == "scene" || object == "Scene")
				map.output_scene(Scene_list);
			else if (object == "BATTLE" || object == "battle" || object == "Battle")
				hero.Show_Status_Of_Battle();
		}
	}
	else if (order == "Talk" || order == "talk" || order == "TALK")
	{
		cin >> object;
		map.output_NPC(object, Scene_list);
	}
	else if (order == "GoTo" || order == "goto" || order == "GOTO" || order == "Goto" || order == "goTo")
	{
		cin >> object;
		Scene *new_scene;
		while (!(new_scene = map.GoTo(object, Scene_list)))
		{
			cout << "Goto:";
			cin >> object;
		}
		return new_scene;
	}
	else if (order == "Attack" || order == "attack" || order == "ATTACK")
	{
		cin >> object;
		monster = map.find_the_monster(object, Scene_list);
		if (!monster)
			cout << "���޴˹֣�" << endl;
		else if (battle.one_battle(hero, monster, skill_list))
			init = 1;
	}
	else if (order == "load" || order == "LOAD" || order == "Load")
	{
		cout << "�������ļ�����";
		char file_name[20];
		cin >> file_name;
		TiXmlDocument myDocument;
		myDocument.LoadFile(file_name);
		if (!myDocument.LoadFile(file_name))
		{
			cout << "��ʼ��ʧ�ܣ�" << endl;
		}
		TiXmlElement *game = myDocument.RootElement();
		TiXmlElement *Map = game->FirstChildElement("map");
		TiXmlElement *scene_element = Map->FirstChildElement("scene");
		while (scene_element)
		{
			Scene *p = new Scene;
			TiXmlElement *scene_name = scene_element->FirstChildElement("name");
			TiXmlElement *scene_trace = scene_element->FirstChildElement("trace");
			p->name = scene_name->GetText();
			p->trace = atoi(scene_trace->GetText());
			if (p->trace == 1)
			{
				for (Scene *q = Scene_list; p != NULL; p = p->next)
				{
					if (q->get_name() == p->name)
					{
						Scene_list = q;
						break;
					}
				}
				break;
			}
			hero.InitHero(file_name);
			Skill skillsystem;
			skill_list = skillsystem.Init_skills(file_name);
			scene_element = scene_element->NextSiblingElement("scene");
		}
	}
	else if (order == "Save" || order == "SAVE" || order == "save")
	{
		cout << "����������Ҫ������ļ���:";
		char file_name[20];
		cin >> file_name;
		ofstream out_file(file_name, ios::out);
		if (!out_file) cout << "�ļ��޷���!";
		out_file <<
			"<?xml version=\"1.0\" encoding=\"GB2312\"?>\
\
<game>\
\
	<map>\
		<scene>\
\
			<name>CloudBank</name>\
\
			<description>�������������ĵط����Ĵ�����һ�ˣ�����...��Զ���п���ǽ�ϵĵ��Ǹ�[����]����������ָ�Talk ���ˣ���</description>\
\
			<NPCs>\
\
				<NPC>\
\
					<name>����</name>\
\
					<talk>��[����]���ϲ���һ�ѱ������[�����]��ѪҺ����ֹͣ�����ʡ�����Щ��ã.�������ӣ�ȴ�벻����������ʲô������������ָ�Talk ����ܣ�����</talk>\
\
				</NPC>\
\
				<NPC>\
\
					<name>�����</name>\
\
					<talk>����������������[�����]��[����]������һ�Ѱγ�������Щ��ԥ��������һ��[����]���뿪��˵����ȴһ����Ҳ˵���������㲻���ȣ�������ת�������ű��ص�[�����]������[����]...��������ָ��Goto ���棩��</talk>\
\
				</NPC>\
\
			</NPCs>\
			\
			<trace>";
		if (Scene_list->get_name() == "CloudBank")

			out_file << "1";

		else out_file << "0";

		out_file << "</trace>\
\
		</scene>\
\
		<scene>\
\
			<name>����</name>\
\
			<description>�����ͣ����һ��[Ħ�г�]��ҹ����㿴�Ÿ��ʵ�Ħ����ã�������һ��˵����������ζ����</description>\
\
			<NPCs>\
\
				<NPC>\
\
					<name>Ħ�г�</name>\
\
					<talk>���㿴��������������ÿ���������ͨ����ǰ��[�߼���],˳�㻹�ܶ�����硣��</talk>\
\
				</NPC>\
\
			</NPCs>\
\
			<trace>";
		if (Scene_list->get_name() == "����")

			out_file << "1";

		else out_file << "0";


		out_file << "</trace>\
\
		</scene>\
\
		<scene>\
\
			<name>�߼���</name>\
\
			<description>��Hello, world! �㼲���ڰ���ķ��У���Χ�Ľ�����һ�������������[�����]��Щ�춯����</description>\
\
			<NPCs>\
\
				<NPC>\
\
					<name>�����</name>\
\
					<talk>��ã�Red���Ҵ��������ͷ���[�����]���ҵ�������������������֪������˭�ɣ�Red���㵱Ȼ֪�������棬����ȥ���ء�[�ֵ�]˵�����������ӡ�</talk>\
\
				</NPC>\
\
			</NPCs>\
\
			<trace>";

		if (Scene_list->get_name() == "�߼���")

			out_file << "1";

		else out_file << "0";

		out_file << "</trace>\
\
		</scene>\
\
		<scene>\
\
			<name>�ֵ�</name>\
\
			<description>Red��ͣ�£��Ƕ�������ʲô�������Ǹ��𻵵�[����]������������ָ�Attack ���ģ���</description>\
\
			<monsters>\
\
			<monster>\
\
					<name>����</name>\
\
					<rebirth>1</rebirth>\
\
					<atk>30</atk>\
\
					<def>5</def>\
\
					<hp>100</hp>\
\
					<whenKilled>\
\
						<exp>20</exp>\
\
						<special>��[����]����һϢ����������˸���Ļ�飬����һ��[���̻�����1]�����٣�Red����ȥ���Ǹ��ּһ���ǻ�ȥ�ɡ�</special>\
\
					</whenKilled>\
\
				</monster>\
\
				<monster>\
\
					<name>���̻�����1</name>\
\
					<rebirth>1</rebirth>\
\
					<atk>60</atk>\
\
					<def>20</def>\
\
					<hp>300</hp>\
\
					<whenKilled>\
\
						<exp>100</exp>\
\
						<special>Red����Ҫ���ȥ�����ġ��һ���Ϊ������ҵĻ������������˵ȥ[��Ժ]�أ�</special>\
\
					</whenKilled>\
\
				</monster>\
\
			</monsters>\
\
			 <trace>";
		if (Scene_list->get_name() == "�ֵ�")

			out_file << "1";

		else out_file << "0";

		out_file << "</trace>\
\
		</scene>\
\
		<scene>\
\
			<name>��Ժ</name>\
\
			<description>����Ժ���ſ�����һ����Ĵ��[����]��Red�����Ǻ����ֱ���Χ��..���¿ɲ�ֻ��[����]��[���̻�����2]��,��������...[�����]��</description>\
\
			<NPCs>\
\
				<NPC>\
\
					<name>����</name>\
\
					<talk>���㿴�ź�������Ż�Ͳ���Լ�����Ӱ�������ˡ���</talk>\
\
				</NPC>\
\
			</NPCs>\
\
			<monsters>\
\
				<monster>\
\
					<name>����</name>\
\
					<rebirth>1</rebirth>\
\
					<atk>30</atk>\
\
					<def>5</def>\
\
					<hp>100</hp>\
\
					<whenKilled>\
\
						<exp>20</exp>\
\
						<special>���𻵵ĺ��ķ·�ʾ������������ھ���һЩ���µ��£�</special>\
\
					</whenKilled>\
\
				</monster>\
\
				<monster>\
\
					<name>�����</name>\
\
					<rebirth>1</rebirth>\
\
					<atk>40</atk>\
\
					<def>10</def>\
\
					<hp>200</hp>\
\
					<whenKilled>\
\
						<exp>20</exp>\
\
						<special>����!��һ��Red����ƬӦ�����䣬��Ƭ�ϵ��㴩��һ�����������·���ʱ׼����̨�ݳ���</special>\
\
					</whenKilled>\
\
				</monster>\
\
				<monster>\
\
					<name>���̻�����2</name>\
\
					<rebirth>1</rebirth>\
\
					<atk>140</atk>\
\
					<def>50</def>\
\
					<hp>700</hp>\
\
					<whenKilled>\
\
						<exp>50</exp>\
\
						<special>Red,���ǽ�ȥ�ɣ�����Ժ��[��̨]��ȥ����Ӧ�û����Щʲô�ġ�</special>\
\
					</whenKilled>\
\
				</monster>\
\
			</monsters>\
\
			 <trace>";
		if (Scene_list->get_name() == "��Ժ")

			out_file << "1";

		else out_file << "0";

		out_file << "</trace>\
\
		</scene>\
\
		<scene>\
\
			<name>��̨</name>\
\
			<description>����̨����������һֻ[��Ͳ]����̨����Ĺ���ϯ����һ�ˡ���Red��ȥ�����������°ɣ����£���ûʲô�ѵģ�������</description>\
\
			<NPCs>\
\
				<NPC>\
\
					<name>��Ͳ</name>\
\
					<talk>���������˻�Ͳ���������С���������������ˣ����µĹ��ڷ������󻶺���ͻȻ��һ��[��Ӱ]�������㱳��һ����ʧ�ˡ���ӻ��������ѹ�������ɫ��Ȼ����</talk>\
\
				</NPC>\
\
				<NPC>\
\
					<name>��Ӱ</name>\
\
					<talk>Red,���������ˣ�����?��ô���Ǽ�����ǰ�ɣ�����[����ϯ]��ʲô������</talk>\
\
				</NPC>\
\
			</NPCs>\
\
			 <trace>";
		if (Scene_list->get_name() == "��̨")

			out_file << "1";

		else out_file << "0";

		out_file << "</trace>\
\
		</scene>\
\
		<scene>\
\
			<name>����ϯ</name>\
\
			<description>[Sybil]��������ȥ�е�ֵֹġ��ðɣ���ֻ���е㡣</description>\
\
			<NPCs>\
\
				<NPC>\
\
					<name>Sybil</name>\
\
					<talk>ѽ��</talk>\
\
				</NPC>\
\
			</NPCs>\
\
			<monsters>\
\
			<monster>\
\
					<name>Sybil</name>\
\
					<rebirth>1</rebirth>\
\
					<atk>200</atk>\
\
					<def>100</def>\
\
					<hp>1000</hp>\
\
					<whenKilled>\
\
						<exp>100</exp>\
\
						<special>�����Ǳ����̿����ˣ�������Sybil��Red,ȥ[Ħ�����]���������ɡ�</special>\
\
					</whenKilled>\
\
				</monster>\
\
			</monsters>\
\
			 <trace>";
		if (Scene_list->get_name() == "����ϯ")

			out_file << "1";

		else out_file << "0";

		out_file << "</trace>\
\
		</scene>\
\
		<scene>\
\
			<name>Ħ�����</name>\
\
			<description>�������CloudBank�ĵر꽨����˵���������ƺ������ţ�Fuck,������Щ������[���̻�����3]������Խ��Խ���ˣ���[��ը��]��[����Ȯ]Ҳ�������ⳡParty��</description>\
\
			<monsters>\
\
				<monster>\
\
					<name>���̻�����3</name>\
\
					<rebirth>1</rebirth>\
\
					<atk>150</atk>\
\
					<def>70</def>\
\
					<hp>800</hp>\
\
					<whenKilled>\
\
						<exp>40</exp>\
\
						<special>�ɶ���ô���ꡣRed,ֱ�ӳ�[����]ȥ��¥������ûʱ���ˡ�</special>\
\
					</whenKilled>\
\
				</monster>\
\
				<monster>\
\
					<name>��ը��</name>\
\
					<rebirth>1</rebirth>\
\
					<atk>150</atk>\
\
					<def>30</def>\
\
					<hp>500</hp>\
\
					<whenKilled>\
\
						<exp>30</exp>\
\
					</whenKilled>\
\
				</monster>\
\
				<monster>\
\
					<name>����Ȯ</name>\
\
					<rebirth>1</rebirth>\
\
					<atk>200</atk>\
\
					<def>40</def>\
\
					<hp>600</hp>\
\
					<whenKilled>\
\
						<exp>30</exp>\
\
					</whenKilled>\
\
				</monster>\
\
			</monsters>\
\
			 <trace>";
		if (Scene_list->get_name() == "Ħ�����")

			out_file << "1";

		else out_file << "0";

		out_file << "</trace>\
\
		</scene>\
\
		<scene>\
\
			<name>����</name>\
\
			<description>�������ڷ�����ֵ����졣һ���[��̢��]�ӵص�����������������Ҿ�֪����[���̻�����4]Ҳ�ڡ�</description>\
\
			<monsters>\
\
				<monster>\
\
					<name>���̻�����4</name>\
\
					<rebirth>1</rebirth>\
\
					<atk>250</atk>\
\
					<def>80</def>\
\
					<hp>1000</hp>\
\
					<whenKilled>\
\
						<exp>40</exp>\
\
						<special>��[��¥]������ϣ���Ƕ����徻һ�㡣</special>\
\
					</whenKilled>\
\
				</monster>\
\
				<monster>\
\
					<name>��̢��</name>\
\
					<rebirth>1</rebirth>\
\
					<atk>120</atk>\
\
					<def>50</def>\
\
					<hp>500</hp>\
\
					<whenKilled>\
\
						<exp>30</exp>\
\
					</whenKilled>\
\
				</monster>\
\
			</monsters>\
\
			 <trace>";
		if (Scene_list->get_name() == "����")

			out_file << "1";

		else out_file << "0";

		out_file << "</trace>\
\
		</scene>\
\
		<scene>\
\
			<name>��¥</name>\
\
			<description>��һ���ֲ���[��������]�ζ������Ĵ��Դ�����Red,�·���ʱ׼������˺�飩������Red�����ǿ��</description>\
\
			<monsters>\
\
				<monster>\
\
					<name>��������</name>\
\
					<rebirth>1</rebirth>\
\
					<atk>300</atk>\
\
					<def>150</def>\
\
					<hp>1800</hp>\
\
					<whenKilled>\
\
						<exp>100</exp>\
\
						<special>Red����ϲ��������·�񣬵�ǹƥ����ɨǧ������������ȥ��һ��[��ǻ]������</special>\
\
					</whenKilled>\
\
				</monster>\
\
			</monsters>\
\
			 <trace>";
		if (Scene_list->get_name() == "��¥")

			out_file << "1";

		else out_file << "0";

		out_file << "</trace>\
\
		</scene>\
\
		<scene>\
\
			<name>��ǻ</name>\
\
			<description>��һ��˶���[��е����]�������ţ����ʴ��Ϊÿ����20�¡���Red,��֪������ô����</description>\
\
			<monsters>\
\
				<monster>\
\
					<name>��е����</name>\
\
					<rebirth>1</rebirth>\
\
					<atk>0</atk>\
\
					<def>0</def>\
\
					<hp>3000</hp>\
\
					<whenKilled>\
\
						<exp>100</exp>\
\
						<special>Red����������꣡�������Ǻܿ���ܾ���Ļ����ʹ�ˡ�������...[������]��</special>\
\
					</whenKilled>\
\
				</monster>\
\
			</monsters>\
\
			 <trace>";
		if (Scene_list->get_name() == "��ǻ")

			out_file << "1";

		else out_file << "0";

		out_file << "</trace>\
\
		</scene>\
\
		<scene>\
\
			<name>������</name>\
\
			<description>��һ��[����]ͻȻð�˳�����ͷ�����ң��׷��ڵ��ϡ���Red,�������Ƕ�����ʲô��</description>\
\
			<monsters>\
\
				<monster>\
\
					<name>����</name>\
\
					<rebirth>1</rebirth>\
\
					<atk>250</atk>\
\
					<def>100</def>\
\
					<hp>1500</hp>\
\
					<whenKilled>\
\
						<exp>100</exp>\
\
						<special>(���˵�ͷ­��д����һ�������ַ[�칫��])Red�����룬����֮�����ǻ������˽����</special>\
\
					</whenKilled>\
\
				</monster>\
\
			</monsters>\
\
			 <trace>";
		if (Scene_list->get_name() == "������")

			out_file << "1";

		else out_file << "0";

		out_file << "</trace>\
\
		</scene>\
\
		<scene>\
\
			<name>�칫��</name>\
\
			<description>[Grant]���ڸ߸ߵ�ָ��̨�ϣ����Ϲ�����ʿ��΢Ц,����Red��</description>\
\
			<NPCs>\
\
				<NPC>\
\
					<name>Grant</name>\
\
					<talk>����ܰ�ȫ,Red������Ŀǰ�����������£����ǻ������̸һ̸����֪���ģ�����ʧȥ�˿��ƣ�ȫ���Ľ��̡����������Ѿ�Ū�����ԭ��[�����]��Red����[�����]�����ҡ�ֻҪ��һ�رգ�������оͻ�ָ�����ԭ�������ӡ�</talk>\
\
				</NPC>\
\
			</NPCs>\
\
			<monsters>\
\
				<monster>\
\
					<name>Grant</name>\
\
					<rebirth>1</rebirth>\
\
					<atk>400</atk>\
\
					<def>200</def>\
\
					<hp>2000</hp>\
\
					<whenKilled>\
\
						<exp>100</exp>\
\
						<special>GAME_VICTORY</special>\
\
					</whenKilled>\
\
				</monster>\
\
			</monsters>\
\
			 <trace>";
		if (Scene_list->get_name() == "�칫��")

			out_file << "1";

		else out_file << "0";

		out_file << "</trace>\
\
		</scene>\
\
	</map>\
\
	<hero>\
\
		<name>Red</name>\
\
		<level>" << hero.get_level() << "</level>\
\
		<MAX_HP>" << hero.get_MAX_HP() << "</MAX_HP>\
\
		<current_HP>" << hero.get_current_HP() << "</current_HP>\
\
		<MAX_MP>" << hero.get_MAX_MP() << "</MAX_MP>\
\
		<current_MP>" << hero.get_current_MP() << "</current_MP>\
\
		<atk>" << hero.get_attack() << "</atk>\
\
		<def>" << hero.get_defense() << "</def>\
\
		<exp>" << hero.get_exp() << "</exp>\
\
		<hpPerLvl>100</hpPerLvl>\
\
		<mpPerLvl>20</mpPerLvl>\
\
		<atkPerLvl>20</atkPerLvl>\
\
		<defPerLvl>20</defPerLvl>\
\
		<expPerLvl>100</expPerLvl>\
\
	</hero>\
\
	<skills>\
\
		<skill>\
\
			<name>Crash()</name>\
\
			<damage>50</damage>\
\
			<consume>20</consume>\
\
			<special>dizzy</special>\
\
			<equip>" << skill_list[0].return_equip(skill_list, 0) << "</equip>\
\
			<order>" << skill_list[0].return_order(skill_list, 0) << "</order>\
\
			<have>" << skill_list[0].return_have(skill_list, 0) << "</have>\
\
		</skill>\
\
		<skill>\
\
			<name>Breach()</name>\
\
			<damage>100</damage>\
\
			<consume>42</consume>\
			\
			<equip>" << skill_list[1].return_equip(skill_list, 1) << "</equip>\
\
			<order>" << skill_list[1].return_order(skill_list, 1) << "</order>\
\
			<have>" << skill_list[1].return_have(skill_list, 1) << "</have>\
\
		</skill>\
\
		<skill>\
\
			<name>Spark()</name>\
\
			<damage>60</damage>\
\
			<consume>20</consume>\
\
			<special>explode</special>\
\
			<equip>" << skill_list[2].return_equip(skill_list, 2) << "</equip>\
\
			<order>" << skill_list[2].return_order(skill_list, 2) << "</order>\
\
			<have>" << skill_list[2].return_have(skill_list, 2) << "</have>\
\
		</skill>\
\
		<skill>\
\
			<name>Mask()</name>\
\
			<damage>0</damage>\
\
			<consume>0</consume>\
\
			<special>skip</special>\
\
			<equip>" << skill_list[3].return_equip(skill_list, 3) << "</equip>\
\
			<order>" << skill_list[3].return_order(skill_list, 3) << "</order>\
\
			<have>" << skill_list[3].return_have(skill_list, 3) << "</have>\
\
		</skill>\
\
		<skill>\
\
			<name>Help()</name>\
\
			<damage>75</damage>\
\
			<consume>25</consume>\
\
			<equip>" << skill_list[4].return_equip(skill_list, 4) << "</equip>\
\
			<order>" << skill_list[4].return_order(skill_list, 4) << "</order>\
\
			<have>" << skill_list[4].return_have(skill_list, 4) << "</have>\
\
		</skill>\
\
		<skill>\
\
			<name>Load()</name>\
\
			<damage>0</damage>\
\
			<consume>50</consume>\
\
			<special>load</special>\
\
			<equip>" << skill_list[5].return_equip(skill_list, 5) << "</equip>\
\
			<order>" << skill_list[5].return_order(skill_list, 5) << "</order>\
\
			<have>" << skill_list[5].return_have(skill_list, 5) << "</have>\
\
		</skill>\
\
		<skill>\
\
			<name>Ping()</name>\
\
			<damage>15</damage>\
\
			<consume>10</consume>\
\
			<special>several</special>\
\
			<equip>" << skill_list[6].return_equip(skill_list, 6) << "</equip>\
\
			<order>" << skill_list[6].return_order(skill_list, 6) << "</order>\
\
			<have>" << skill_list[6].return_have(skill_list, 6) << "</have>\
\
		</skill>\
\
		<skill>\
\
			<name>Cull()</name>\
\
			<damage>225</damage>\
\
			<consume>70</consume>\
\
			<equip>" << skill_list[7].return_equip(skill_list, 7) << "</equip>\
\
			<order>" << skill_list[7].return_order(skill_list, 7) << "</order>\
\
			<have>" << skill_list[7].return_have(skill_list, 7) << "</have>\
\
		</skill>\
\
		<skill>\
\
			<name>Flood()</name>\
\
			<damage>60</damage>\
\
			<consume>25</consume>\
\
			<special>repeat_2</special>\
\
			<equip>" << skill_list[8].return_equip(skill_list, 8) << "</equip>\
\
			<order>" << skill_list[8].return_order(skill_list, 8) << "</order>\
\
			<have>" << skill_list[8].return_have(skill_list, 8) << "</have>\
\
		</skill>\
\
		<skill>\
\
			<name>Purge()</name>\
\
			<damage>40</damage>\
\
			<consume>20</consume>\
\
			<special>repeat_3</special>\
\
			<equip>" << skill_list[9].return_equip(skill_list, 9) << "</equip>\
\
			<order>" << skill_list[9].return_order(skill_list, 9) << "</order>\
\
			<have>" << skill_list[9].return_have(skill_list, 9) << "</have>\
\
		</skill>\
\
		<skill>\
\
			<name>Tap()</name>\
\
			<damage>150</damage>\
\
			<consume>35</consume> \
\
			<special>absorb</special>\
\
			<equip>" << skill_list[10].return_equip(skill_list, 10) << "</equip>\
\
			<order>" << skill_list[10].return_order(skill_list, 10) << "</order>\
\
			<have>" << skill_list[10].return_have(skill_list, 10) << "</have>\
\
		</skill>\
\
		<skill>\
\
			<name>Void()</name>\
\
			<damage>0</damage>\
\
			<consume>15</consume>\
\
			<special>weaken</special>\
\
			<equip>" << skill_list[11].return_equip(skill_list, 11) << "</equip>\
\
			<order>" << skill_list[11].return_order(skill_list, 11) << "</order>\
\
			<have>" << skill_list[11].return_have(skill_list, 11) << "</have>\
\
		</skill>\
\
		<skill>\
\
			<name>Get()</name>\
\
			<damage>150</damage>\
\
			<consume>10</consume>\
\
			<special>close</special>\
\
			<equip>" << skill_list[12].return_equip(skill_list, 12) << "</equip>\
\
			<order>" << skill_list[12].return_order(skill_list, 12) << "</order>\
\
			<have>" << skill_list[12].return_have(skill_list, 12) << "</have>\
\
		</skill>\
\
		<skill>\
\
			<name>Kill()</name>\
\
			<damage>500</damage>\
\
			<consume>80</consume>\
\
			<special>defeat</special>\
\
			<equip>" << skill_list[13].return_equip(skill_list, 13) << "</equip>\
\
			<order>" << skill_list[13].return_order(skill_list, 13) << "</order>\
\
			<have>" << skill_list[13].return_have(skill_list, 13) << "</have>\
\
		</skill>\
\
	</skills>\
\
</game>\
		";
	}
	return Scene_list;
}