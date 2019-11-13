#include"SudoKu.h"
#include<random>
#include<ctime>
#include<iostream>
using namespace std;
static std::default_random_engine e(time(0));

void SudoKu::change_value(int lhs,int rhs) //交换两个数的位置
{
    for(vint  & vec:vvnum)  //声明循环范围
        for(int &a : vec)
        {
            if(a==lhs)a=rhs;
            else a= a==rhs?lhs:a;
        }
}
void SudoKu::swap_row(int lhs,int rhs) //交换行数据
{
    using std::swap;
    swap(vvnum[lhs],vvnum[rhs]);  //调用库函数
}
void SudoKu::swap_threerow(int lhs,int rhs) //交换连续三行的数据
{
    for(int i=0;i<3;++i)   //连续三次调用交换行函数即可实现
        swap_row(lhs+i,rhs+i);
}
void SudoKu::swap_threecol(int lhs,int rhs) //交换三列的数据
{
    for(int i=0;i<3;++i)
        swap_col(lhs+i,rhs+i);
}
void SudoKu::swap_col(int lhs,int rhs) //交换列数据
{
    for(int i=0;i<9;++i)
    {
        using std::swap;
        swap(vvnum[i][lhs],vvnum[i][rhs]);
    }
}
void SudoKu::change_Number() //生成9*9的数独
{
    std::uniform_int_distribution<int> u(1,9); //生成1~9的随机数
    //随机交换两个数值的位置
    for(int a=0;a<15;++a) //随机交换a次
    {
        int i=u(e),j=u(e); //得到两个交换数值
        if(i!=j)
            change_value(u(e),u(e));
        else --a;
    }
    std::uniform_int_distribution<int>ul(0,2); //生成0~2的随机数
    //在交换行列数据的时候需要3行内进行交换，这样得到的是合法的数独
    //否则在交换过程中，数独将会不合法
    //swap row and line 
    for(int a=0;a<10;++a) //随即交换10次
    {
        int bases=3*ul(e),i=bases+ul(e),j=bases+ul(e);
        if(i!=j)
            swap_row(i,j);// 0-8
        i=ul(e),j=ul(e);
        if(i!=j)
            swap_threerow(3*i,3*j);//0 3 6
        bases=3*ul(e),i=bases+ul(e),j=bases+ul(e);
        if(i!=j)
            swap_col(i,j);//0-8
        i=ul(e),j=ul(e);
        if(i!=j)
            swap_threecol(3*i,3*j);// 0 3 6
    }
    result=vvnum;
    creat_sudo(); //生成最终的数独棋盘
    
}

SudoKu::SudoKu(int level_sudoku)
{
    vvnum= {{1,4,5,3,2,7,6,9,8},
                {8,3,9,6,5,4,1,2,7},
                {6,7,2,9,1,8,5,4,3},
                {4,9,6,1,8,5,3,7,2},
                {2,1,8,4,7,3,9,5,6},
                {7,5,3,2,9,6,4,8,1},
                {3,6,7,5,4,2,8,1,9},
                {9,8,4,7,6,1,2,3,5},
                {5,2,1,8,3,9,7,6,4}};
     level=level_sudoku;
    change_Number();
            
}
void SudoKu::creat_sudo() //挖空法得到数独
{
    int conl; //挖空数量
    switch (level)
    {
    case 1: conl=40;
        break;
    case 2: conl=50;break;
    case 3: conl=56;break;
    case 4: conl=62;break;
    default:conl=40;
        break;
    }
    srand(time(0));
    int i;
    for (i = 0; i < conl;i++)
    {
        unsigned int x,y;
		x=rand()%9;
		y=rand()%9;
        while(vvnum[x][y]==0)
        {
            x=rand()%9;
            y=rand()%9;
        }
		vvnum[x][y]=0;
	}
}

bool  SudoKu::judge_sudo(int num_btni,int num_btnj,int n)//第几个按钮填入了多少
{
    /*if(this->result[num_btni][num_btnj]==n)
        return true;
    else return false;*/
    int i, j;
        for (i = 0; i < 9; i++)
        {
            for (j = 0; j < 9; j++)
            {
                if (j != num_btnj && vvnum[num_btni][j] != 0 && n == vvnum[num_btni][j])	//判断行有没有填重复
                    return false;
                if (j != num_btni && vvnum[j][num_btnj] != 0 && n == vvnum[j][num_btnj])	//判断列有没有填重复
                    return false;
                if ((i != num_btni || j != num_btnj) && vvnum[i][j] != 0 && i / 3 == num_btni / 3 && j / 3 == num_btnj / 3 && n == vvnum[i][j])	//判断3x3有没有填重复
                    return false;
            }
        }
        return true;
}

//提示功能
int SudoKu::idea_sudo()
{
    srand(time(0));
    int x;
    int raw,line;
    x=(rand()%81)+1;
    raw=(x-1)/9;
    line=(x-1)%9;
    if(vvnum[raw][line]!=0)
    while(vvnum[raw][line]!=0)
    {
        x=(rand()%81)+1;
        raw=(x-1)/9;
        line=(x-1)%9;
    }
    vvnum[raw][line]=result[raw][line];
return x;

}
//变换格子颜色
int* SudoKu:: change_color()
{
       c_color[36] = {};int i,j,matrix_i,matrix_j;
        for (i = 1, j = 0; i <= 81 && j < 36; i++)
        {
            matrix_i = (i - 1) / 9 / 3;
            matrix_j = (i - 1) % 9 / 3;
            if (matrix_i + matrix_j == 1 || matrix_i + matrix_j == 3)
            {
                c_color[j] = i;
                j++;
            }
        }
        return c_color;

}
