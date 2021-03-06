#ifndef _SUDOKU_H
#define _SUDOKU_H
#include<vector>
#include<set>
#include<cstdlib>
#include <QApplication>
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
     int idea_sudo();//提示功能
    int* change_color();	//变换格子颜色

int c_color[36];
  int level;
    vvint vvnum; //生成的游戏数独
    vvint result; //游戏数独的答案

};


#endif
