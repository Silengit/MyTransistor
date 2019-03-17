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
		cout << "游戏初始化完成。开始新游戏。" << endl;
		cout << "游戏操作指令集:ShowStatus+SCENE/BATTLE；Talk+人物；GoTo+地点（场景不可回溯）；Attack+怪物" << endl;
		cout << endl;
		cout << "Red,你醒了吗...(请输入指令ShowStatus SCENE)" << endl;
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
			cout << "查无此怪！" << endl;
		else if (battle.one_battle(hero, monster, skill_list))
			init = 1;
	}
	else if (order == "load" || order == "LOAD" || order == "Load")
	{
		cout << "请输入文件名：";
		char file_name[20];
		cin >> file_name;
		TiXmlDocument myDocument;
		myDocument.LoadFile(file_name);
		if (!myDocument.LoadFile(file_name))
		{
			cout << "初始化失败！" << endl;
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
		cout << "请输入你需要保存的文件名:";
		char file_name[20];
		cin >> file_name;
		ofstream out_file(file_name, ios::out);
		if (!out_file) cout << "文件无法打开!";
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
			<description>（这儿是你生活的地方，四处空无一人，除了...不远处倚靠在墙上的的那个[男人]。（请输入指令：Talk 男人））</description>\
\
			<NPCs>\
\
				<NPC>\
\
					<name>男人</name>\
\
					<talk>（[男人]身上插着一把宝剑般的[晶体管]，血液早已停止了流淌。你有些迷茫.，眼神复杂，却想不起来发生了什么。（（请输入指令：Talk 晶体管）））</talk>\
\
				</NPC>\
\
				<NPC>\
\
					<name>晶体管</name>\
\
					<talk>（你运足气力，将[晶体管]从[男人]的身上一把拔出。你有些犹豫，又望了一眼[男人]，想开口说话，却一个字也说不出来。你不惊讶，缓缓地转过身，拖着笨重的[晶体管]，走向[外面]...（请输入指令Goto 外面））</talk>\
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
			<name>外面</name>\
\
			<description>（这儿停放着一辆[摩托车]。夜已深，你看着高耸的摩天大厦，心里有一股说不出来的滋味。）</description>\
\
			<NPCs>\
\
				<NPC>\
\
					<name>摩托车</name>\
\
					<talk>（你看着这个宝贝，觉得可以骑上它通过眼前的[高架桥],顺便还能兜会儿风。）</talk>\
\
				</NPC>\
\
			</NPCs>\
\
			<trace>";
		if (Scene_list->get_name() == "外面")

			out_file << "1";

		else out_file << "0";


		out_file << "</trace>\
\
		</scene>\
\
		<scene>\
\
			<name>高架桥</name>\
\
			<description>（Hello, world! 你疾行于傍晚的风中，周围的建筑物一闪而过。背后的[晶体管]有些异动。）</description>\
\
			<NPCs>\
\
				<NPC>\
\
					<name>晶体管</name>\
\
					<talk>你好，Red。我存在于你的头脑里，[晶体管]将我的声音储存了下来。你知道我是谁吧，Red。你当然知道。下面，我们去哪呢。[街道]说不定会有乐子。</talk>\
\
				</NPC>\
\
			</NPCs>\
\
			<trace>";

		if (Scene_list->get_name() == "高架桥")

			out_file << "1";

		else out_file << "0";

		out_file << "</trace>\
\
		</scene>\
\
		<scene>\
\
			<name>街道</name>\
\
			<description>Red，停下，那儿好像有什么东西，是个损坏的[核心]？（（请输入指令：Attack 核心））</description>\
\
			<monsters>\
\
			<monster>\
\
					<name>核心</name>\
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
						<special>（[核心]奄奄一息，后面出现了更多的伙伴，还有一个[进程机器人1]。）嘿，Red，别去惹那个怪家伙，我们回去吧。</special>\
\
					</whenKilled>\
\
				</monster>\
\
				<monster>\
\
					<name>进程机器人1</name>\
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
						<special>Red，我要你别去惹他的。我还以为你会听我的话。如果我现在说去[剧院]呢？</special>\
\
					</whenKilled>\
\
				</monster>\
\
			</monsters>\
\
			 <trace>";
		if (Scene_list->get_name() == "街道")

			out_file << "1";

		else out_file << "0";

		out_file << "</trace>\
\
		</scene>\
\
		<scene>\
\
			<name>剧院</name>\
\
			<description>（剧院的门口贴着一张你的大幅[海报]）Red，我们好像又被包围了..这下可不只是[核心]和[进程机器人2]了,甚至还有...[照相机]？</description>\
\
			<NPCs>\
\
				<NPC>\
\
					<name>海报</name>\
\
					<talk>（你看着海报里举着话筒的自己，背影惆怅而动人。）</talk>\
\
				</NPC>\
\
			</NPCs>\
\
			<monsters>\
\
				<monster>\
\
					<name>核心</name>\
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
						<special>（损坏的核心仿佛暗示着这个城市正在经历一些可怕的事）</special>\
\
					</whenKilled>\
\
				</monster>\
\
				<monster>\
\
					<name>照相机</name>\
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
						<special>卡擦!（一张Red的照片应声而落，照片上的你穿着一身落地礼服，仿佛随时准备上台演出）</special>\
\
					</whenKilled>\
\
				</monster>\
\
				<monster>\
\
					<name>进程机器人2</name>\
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
						<special>Red,我们进去吧，到剧院的[舞台]上去，你应该会记起些什么的。</special>\
\
					</whenKilled>\
\
				</monster>\
\
			</monsters>\
\
			 <trace>";
		if (Scene_list->get_name() == "剧院")

			out_file << "1";

		else out_file << "0";

		out_file << "</trace>\
\
		</scene>\
\
		<scene>\
\
			<name>舞台</name>\
\
			<description>（舞台的中央立着一只[话筒]，舞台下面的观众席空无一人。）Red，去做你想做的事吧，别害怕，这没什么难的，不是吗。</description>\
\
			<NPCs>\
\
				<NPC>\
\
					<name>话筒</name>\
\
					<talk>（你拿起了话筒，沉浸其中。你的声线优美动人，底下的观众发出阵阵欢呼。突然，一个[黑影]闪到了你背后。一切消失了。你从回忆中清醒过来，神色黯然。）</talk>\
\
				</NPC>\
\
				<NPC>\
\
					<name>黑影</name>\
\
					<talk>Red,你想起来了，对吗?那么我们继续往前吧，看看[观众席]有什么线索。</talk>\
\
				</NPC>\
\
			</NPCs>\
\
			 <trace>";
		if (Scene_list->get_name() == "舞台")

			out_file << "1";

		else out_file << "0";

		out_file << "</trace>\
\
		</scene>\
\
		<scene>\
\
			<name>观众席</name>\
\
			<description>[Sybil]？她看上去有点怪怪的。好吧，不只是有点。</description>\
\
			<NPCs>\
\
				<NPC>\
\
					<name>Sybil</name>\
\
					<talk>呀！</talk>\
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
						<special>她像是被进程控制了？可怜的Sybil。Red,去[摩天大厦]找找线索吧。</special>\
\
					</whenKilled>\
\
				</monster>\
\
			</monsters>\
\
			 <trace>";
		if (Scene_list->get_name() == "观众席")

			out_file << "1";

		else out_file << "0";

		out_file << "</trace>\
\
		</scene>\
\
		<scene>\
\
			<name>摩天大厦</name>\
\
			<description>（这儿是CloudBank的地标建筑，说它高耸入云毫不夸张）Fuck,又是那些该死的[进程机器人3]！种类越来越多了，连[轰炸鸡]和[进程犬]也加入了这场Party。</description>\
\
			<monsters>\
\
				<monster>\
\
					<name>进程机器人3</name>\
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
						<special>可恶，怎么打不完。Red,直接乘[电梯]去顶楼，我们没时间了。</special>\
\
					</whenKilled>\
\
				</monster>\
\
				<monster>\
\
					<name>轰炸鸡</name>\
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
					<name>进程犬</name>\
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
		if (Scene_list->get_name() == "摩天大厦")

			out_file << "1";

		else out_file << "0";

		out_file << "</trace>\
\
		</scene>\
\
		<scene>\
\
			<name>电梯</name>\
\
			<description>（电梯内发出奇怪的声响。一大堆[鞭挞者]从地底钻出来。）啊哈，我就知道，[进程机器人4]也在。</description>\
\
			<monsters>\
\
				<monster>\
\
					<name>进程机器人4</name>\
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
						<special>到[顶楼]了吗。真希望那儿能清净一点。</special>\
\
					</whenKilled>\
\
				</monster>\
\
				<monster>\
\
					<name>鞭挞者</name>\
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
		if (Scene_list->get_name() == "电梯")

			out_file << "1";

		else out_file << "0";

		out_file << "</trace>\
\
		</scene>\
\
		<scene>\
\
			<name>顶楼</name>\
\
			<description>（一个恐怖的[超级进程]晃动着它的大脑袋盯着Red,仿佛随时准备将她撕碎）该死！Red，别逞强！</description>\
\
			<monsters>\
\
				<monster>\
\
					<name>超级进程</name>\
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
						<special>Red，我喜欢你的行事风格，单枪匹马，横扫千军。现在我们去这家伙的[内腔]看看。</special>\
\
					</whenKilled>\
\
				</monster>\
\
			</monsters>\
\
			 <trace>";
		if (Scene_list->get_name() == "顶楼")

			out_file << "1";

		else out_file << "0";

		out_file << "</trace>\
\
		</scene>\
\
		<scene>\
\
			<name>内腔</name>\
\
			<description>（一个硕大的[机械心脏]在跳动着，速率大概为每分钟20下。）Red,你知道该怎么做！</description>\
\
			<monsters>\
\
				<monster>\
\
					<name>机械心脏</name>\
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
						<special>Red，这儿有坐标！我想我们很快就能揪出幕后主使了。坐标是...[海景房]。</special>\
\
					</whenKilled>\
\
				</monster>\
\
			</monsters>\
\
			 <trace>";
		if (Scene_list->get_name() == "内腔")

			out_file << "1";

		else out_file << "0";

		out_file << "</trace>\
\
		</scene>\
\
		<scene>\
\
			<name>海景房</name>\
\
			<description>（一个[半人]突然冒了出来，头发凌乱，蹲伏在地上。）Red,瞧瞧他们都做了什么。</description>\
\
			<monsters>\
\
				<monster>\
\
					<name>半人</name>\
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
						<special>(半人的头颅上写着下一个坐标地址[办公室])Red。我想，结束之后我们或许可以私奔。</special>\
\
					</whenKilled>\
\
				</monster>\
\
			</monsters>\
\
			 <trace>";
		if (Scene_list->get_name() == "海景房")

			out_file << "1";

		else out_file << "0";

		out_file << "</trace>\
\
		</scene>\
\
		<scene>\
\
			<name>办公室</name>\
\
			<description>[Grant]坐在高高的指挥台上，脸上挂着绅士的微笑,看着Red。</description>\
\
			<NPCs>\
\
				<NPC>\
\
					<name>Grant</name>\
\
					<talk>这儿很安全,Red，至少目前是这样。别害怕，我们或许可以谈一谈。你知道的，他们失去了控制，全部的进程。但我想我已经弄清楚了原因。[晶体管]，Red，把[晶体管]交给我。只要它一关闭，这个城市就会恢复到他原来的样子。</talk>\
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
		if (Scene_list->get_name() == "办公室")

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