#ifndef _SUDOKU_H
#define _SUDOKU_H
#include<vector>
#include<set>
#include<cstdlib>
typedef std::vector<int>  vint;
typedef std::vector<vint> vvint;
typedef std::vector<bool> vbool;
typedef std::vector<vbool> vvbool;

class SudoKu
{
private:
    //const int hardclass;
    //以下是数独生成所需要的函数
    void change_value(int lhs,int rhs); //交换两个数的值
    void swap_col(int lhs,int rhs);  //交换行
    void swap_row(int lhs,int rhs); //交换列
    void swap_threecol(int lhs,int rhs); //交换三列数据
    void swap_threerow(int lhs,int rhs); //交换三列数据
    void creat_sudo(); //挖空生成游戏的数独

public:
    void change_Number();//初始化9×9格子
    SudoKu(int level_sudoku);
     bool judge_sudo(int num_btni,int num_btnj,int n);

    vvint vvnum; //生成的游戏数独
    vvint result; //游戏数独的答案

};

class Level
{
private:
	//数独难度选择函数,设置成员变量ways
	void setlevel();	//难度选择函数
	void easylevel();	//简单难度
	void midlevel();	//中等难度
	void hardlevel();	//困难难度
	void show_sudo();	//根据成员变量ways设置成员变量how_to_show

	//成员变量
	const int level;	//难度，可选择1-3
	vint ways;	//一维数组，设置每行显示出几个数
	vvbool how_to_show;	//9x9的显示方式

public:
	const std::vector<bool>& operator[](int a)const 
	{ 
		return how_to_show[a]; 
	}

	explicit GameLevel(int alevel);
};
#endif
