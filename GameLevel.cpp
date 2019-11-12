#include"SudoKu.h"
#include<random>
#include<ctime>
#include<iostream>
using namespace std;
static std::default_random_engine e(time(0));

Level::GameLevel(int alevel):level(a),how_to_show(9,vbool(9,0)),ways(9,0)
{
	setlevel();
	show_sudo();
}

void Level::easylevel()	//简单难度
{
	std::uniform_int_distribution<int> us(4, 6);
	ways[0] = ways[3] = ways[6] = us(e);
	std::uniform_int_distribution<int> um(3, 4);
	ways[1] = ways[7] = um(e);
	ways[2] = ways[5] = ways[8] = int((33 - (3 * ways[0] + 2 * ways[1])) / 3);
	std::uniform_int_distribution<int> un(4, 6);
	ways[4] = un(e);
}

void Level::midlevel()	//中等难度
{
	std::uniform_int_distribution<int> us(3, 6);
	ways[0] = ways[3] = ways[6] = us(e);
	std::uniform_int_distribution<int> um(2, 3);
	ways[1] = ways[7] = um(e);
	ways[2] = ways[5] = ways[8] = int((28 - (3 * ways[0] + 2 * ways[1])) / 3);
	std::uniform_int_distribution<int> un(3, 5);
	ways[4] = un(e);
}

void Level::hardlevel()	//困难难度
{
	std::uniform_int_distribution<int> us(3, 5);
	ways[0] = ways[8] = us(e);
	ways[1] = ways[7] = 7 - ways[0];
	std::uniform_int_distribution<int> um(2, 3);
	ways[2] = ways[6] = um(e);
	ways[3] = ways[5] = 7 - ways[2];
	std::uniform_int_distribution<int> un(1, 3);
	ways[4] = un(e);
}

void Level::setlevel()	//用level变量设置数独难度
{
	if (1 == level)	easylevel();
	else if (2 == level)	midlevel();
	else if (3 == level)	hardlevel();
}

void Level::show_sudo()	//用于构造how_to_show变量
{
	if (level <= 2)
		for (int a = 0; a < 9; ++a)
			changeRow(how_to_show[a], ways[a]);
	else
	{
		for (int a = 0; a < 5; ++a)
		{
			changeRow(how_to_show[a], ways[a]);
		}
		for (int a = 5; a < 9; ++a)
			how_to_show[a] = how_to_show[8 - a];
	}
}

void Level::changeRow(std::vector<bool>& a, int num)
{
	int s = 0;	//设置为1的数字个数
	if (num == 0)
		return;
	std::uniform_int_distribution<int> un(1, 9 - s);	//范围
	int n = un(e);
	int temp = 0;
	std::vector<bool>::iterator i = a.begin();
	do {
		if (0 == *i)
			temp++;
		if (temp == n)
		{
			*i = 1;
			if (++s == num)	break;
			i = a.begin();	//继续从头开始循环
			std::uniform_int_distribution<int>ud(1, 9 - s);
			n = ud(e); temp = 0;
		}
		else
		{
			if (i == a.end())
				i = a.begin();
			else
				++i;
		}
	} while (1);
}