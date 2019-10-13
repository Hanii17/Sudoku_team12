#include"sudo3.h"
#include<random>
#include<ctime>
//#include<set>
#include<iostream>
//#include<vector>
//#include<cstdlib>
//typedef std::vector<int>  vint;
//typedef std::vector<vint> vvint;
using namespace std;
/*class SudoKu
{
private:
    //const int hardclass;
    int checktemp;//
    vvint vvnum;
    vvint result;
    void creat_sudo();
    //
    void change_value(int lhs,int rhs);
    void swap_col(int lhs,int rhs);
    void swap_row(int lhs,int rhs);
    void swap_threecol(int lhs,int rhs);
    void swap_threerow(int lhs,int rhs);

    int onlyone(int a,int b);
public:
    SudoKu();
    void change_Number();//鍒濆鍖�9脳9鏍煎瓙
    //~SudoKu(){}
    explicit SudoKu(int a);

    const vint & operator[](int a)const{return vvnum[a];}

    vint & operator[](int a){return vvnum[a];}
    vvint copy();
    void set(const vvint& vec);


    const vvint& getresult(){return result;}
    std::pair<int,int> help();

    //same num check
    void check1(int a, int b, spairii &vecpr);

    //only number check
    void check2(int a, int b, spairii &vecpr);

    bool haswrong(int a, int b);
    bool haswrong2(int a, int b);
    bool checkwin();
    void show();
};*/
static std::default_random_engine e(time(0));

void SudoKu::change_value(int lhs,int rhs) //交换数独中两个数的位置
{
    for(vint  & vec:vvnum)  //限制范围
        for(int &a : vec)
        {
            if(a==lhs)a=rhs;
            else a= a==rhs?lhs:a;
        }
}
void SudoKu::swap_row(int lhs,int rhs) //交换行数据
{
    using std::swap;
    swap(vvnum[lhs],vvnum[rhs]);  //使用系统自带的函数
}
void SudoKu::swap_threerow(int lhs,int rhs) //交换三行数据
{
    for(int i=0;i<3;++i)   //连续三次交换行数据
        swap_row(lhs+i,rhs+i);
}
void SudoKu::swap_threecol(int lhs,int rhs) //交换三列数据
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
void SudoKu::change_Number() //随机生成9*9数独
{
    std::uniform_int_distribution<int> u(1,9); //随机生成2个数字进行交换
    //交换两个数的位置
    for(int a=0;a<15;++a) //a为交换的次数
    {
        int i=u(e),j=u(e); //得到随机数
        if(i!=j)
            change_value(u(e),u(e));
        else --a;
    }
    std::uniform_int_distribution<int>ul(0,2); //生成交换的行和列的随机数
    //交换行列时，只有当1~3 4~6 7~9三行（列）进行交换时才不会破坏数独的合理性
    //swap row and line 
    for(int a=0;a<10;++a) //开始进行随机转换
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
    creat_sudo(); //生成数独游戏盘
    
}
void SudoKu::show()
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
}
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
            
}
void SudoKu::creat_sudo()
{
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
    cout << endl;

}
int main()
{
    SudoKu one;
    //one.show();
    cout << endl;
    one.change_Number();
    one.show();
    return 0;
}