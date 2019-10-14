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
/*void SudoKu::show()
{
    int i, j;
    for (i = 0; i < 9;i++)
    {
        for (j = 0; j < 9;j++)
            cout << vvnum[i][j] << ' ';
        cout << endl;
    }
    cout << endl;
    for (i = 0; i < 9;i++)
    {
        for (j = 0; j < 9;j++)
            cout << result[i][j] << ' ';
        cout << endl;
    }
}*/
SudoKu::SudoKu()
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
    change_Number();
            
}
void SudoKu::creat_sudo() //挖空法得到数独
{   change_Number();
    srand(time(0));
    int i;
    for (i = 0; i < 40;i++)
    {
		int x,y;
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