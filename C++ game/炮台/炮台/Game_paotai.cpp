//time		：	2016年3月31日
//author	：	 @`13
//func		：	小游戏-炮台，第三次实验

#include<iostream>
#include<Windows.h>
#include<vector>
#include<time.h>
#include<string>

using namespace std;

#define TOP_boundary 30
#define RIGHT_boundary 80
class Game_paotai
{
private:

	//坐标
	int x;
	int y;

	//计时器
	int t;

	//控制时间
	int t_bul;
	int t_move;
	int t_targ;

	//计数变量
	int p_forw;
	int tar_count;
	
	//子弹计时器
	clock_t t_p, t_b, t_b_u, t_b_d, t_b_l, t_b_r;

	//目标时间计时器
	clock_t t_tar_c,t_tar_s, t_tar_alive;
	
	//各种方向子弹容器
	vector <COORD> bul;
	vector <COORD> bul_U;
	vector <COORD> bul_D;
	vector <COORD> bul_L;
	vector <COORD> bul_R;

	//随机目标容器
	vector <COORD> targ;

	//flag
	bool flag;

public:

	//构造函数
	Game_paotai()
	{
		x = 13; y = 13;
		t_bul = 10;
		t_move = 20;
		t_targ = 20;

		flag = true;
		p_forw = 1;
		t = 0;
		tar_count = 0;
		t_p = clock();
		t_b = clock();
		t_b_u = clock();
		t_b_d = clock();
		t_b_l = clock();
		t_b_r = clock();
		t_tar_c = clock();
		t_tar_s = clock();
		t_tar_alive = clock();
	}

	//构造函数，带参数重载
	Game_paotai(int input_x, int input_y, int input_t_bul, int input_t_move, int input_t_targ)
	{
		x = input_x;
		y = input_y;
		t_bul = input_t_bul;
		t_move = input_t_move;
		t_targ = input_t_targ;

		flag = true;
		tar_count = 0;
		p_forw = 1;
		t = 0;
		t_p = clock();
		t_b = clock();
		t_b_u = clock();
		t_b_d = clock();
		t_b_l = clock();
		t_b_r = clock();
		t_tar_c = clock();
		t_tar_s = clock();
		t_tar_alive = clock();
	}

	void gotoxy(int x, int y)
	{
		//光标移动到指定坐标处
		HANDLE h;//句柄,对象的索引
		COORD c;//结构体,坐标值
		c.X = x;
		c.Y = y;
		h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(h, c);
	}
	//清除函数
	void erase()
	{
		gotoxy(x, y);
		cout << "  ";
	}

	//绘制炮台本体函数
	int get_forward()
	{
		return p_forw;
	}
	void draw()
	{
		switch (get_forward())
		{
		case 1:
		{
				  draw_U();
				  break;
		}
		case 2:
		{
				  draw_D();
				  break;
		}
		case 3:
		{
				  draw_L();
				  break;
		}
		case 4:
		{
				  draw_R();
				  break;
		}

		}
	}
	void draw_L()
	{
		gotoxy(x, y);
		cout << "┫";
	}
	void draw_R()
	{
		gotoxy(x, y);
		cout << "┣";
	}
	void draw_U()
	{
		gotoxy(x, y);
		cout << "┻";
	}
	void draw_D()
	{
		gotoxy(x, y);
		cout << "┳";
	}

	//炮台移动函数
	void move()
	{
		if (flag == true)
		{
			draw();
			flag = false;
		}
		if (clock() - t_p > t_move)
		{

			if (GetAsyncKeyState(VK_NUMPAD4))
			{
				p_forw = 3;
			}
			if (GetAsyncKeyState(VK_NUMPAD6))
			{
				p_forw = 4;
			}
			if (GetAsyncKeyState(VK_NUMPAD8))
			{
				p_forw = 1;
			}
			if (GetAsyncKeyState(VK_NUMPAD2))
			{
				p_forw = 2;
			}

			if (GetAsyncKeyState(VK_SPACE))
			{
				switch (get_forward())
				{
				case 1:
				{
						  COORD temp;
						  temp.X = x; temp.Y = y - 1;
						  bul_U.push_back(temp);
						  break;
				}
				case 2:
				{
						  COORD temp;
						  temp.X = x; temp.Y = y + 1;
						  bul_D.push_back(temp);
						  break;
				}
				case 3:
				{
						  COORD temp;
						  temp.X = x - 1; temp.Y = y;
						  bul_L.push_back(temp);
						  break;
				}
				case 4:
				{
						  COORD temp;
						  temp.X = x + 1; temp.Y = y;
						  bul_R.push_back(temp);
						  break;
				}
				}

			}

			if (GetAsyncKeyState(VK_LEFT))
			{
				erase();
				--x;
				if (x < 0) x = 0;
				draw();
			}
			if (GetAsyncKeyState(VK_RIGHT))
			{
				erase();
				++x;
				if (x>RIGHT_boundary) x = RIGHT_boundary;
				draw();
			}
			if (GetAsyncKeyState(VK_UP))
			{
				erase();
				--y;
				if (y < 0) y = 0;
				draw();
			}
			if (GetAsyncKeyState(VK_DOWN))
			{
				erase();
				++y;
				if (y>TOP_boundary) y = TOP_boundary;
				draw();
			}

			flag = true;
			t_p = clock();
		}
	}

	//炮台移动函数 右上方
	void move_ur()
	{
		if (flag == true)
		{
			draw();
			flag = false;
		}
		if (clock() - t_p > t_move)
		{
			if (GetAsyncKeyState(VK_ESCAPE)) exit(0);


			if (GetAsyncKeyState(VK_NUMPAD4))
			{
				p_forw = 3;
			}
			if (GetAsyncKeyState(VK_NUMPAD6))
			{
				p_forw = 4;
			}
			if (GetAsyncKeyState(VK_NUMPAD8))
			{
				p_forw = 1;
			}
			if (GetAsyncKeyState(VK_NUMPAD2))
			{
				p_forw = 2;
			}

			if (GetAsyncKeyState(VK_SPACE))
			{

				COORD temp,temp2;
				temp.X = x; temp.Y = y - 1;
				temp.X = x+3; temp.Y = y+2 ;
				bul.push_back(temp);
				bul.push_back(temp2);

			}

			if (GetAsyncKeyState(VK_LEFT))
			{
				erase();
				--x;
				if (x < 0) x = 0;
				draw();
			}
			if (GetAsyncKeyState(VK_RIGHT))
			{
				erase();
				++x;
				if (x>RIGHT_boundary) x = RIGHT_boundary;
				draw();
			}
			if (GetAsyncKeyState(VK_UP))
			{
				erase();
				--y;
				if (y < 0) y = 0;
				draw();
			}
			if (GetAsyncKeyState(VK_DOWN))
			{
				erase();
				++y;
				if (y>TOP_boundary) y = TOP_boundary;
				draw();
			}

			flag = true;
			t_p = clock();
		}
	}

	//计时，绘制计时器函数
	void draw_time_clock()
	{
		if (clock() - t_b > 1000)
		{
			++t;
			t_b = clock();
		}

		gotoxy(x, y);
		cout << t;
	}

	//计时器移动函数
	void move_time_clock()
	{
		if (flag == true)
		{
			draw_time_clock();
			flag = false;
		}
		if (clock() - t_p > t_move)
		{
			if (GetAsyncKeyState(VK_ESCAPE)) exit(0);


			if (GetAsyncKeyState(VK_NUMPAD4))
			{
				p_forw = 3;
			}
			if (GetAsyncKeyState(VK_NUMPAD6))
			{
				p_forw = 4;
			}
			if (GetAsyncKeyState(VK_NUMPAD8))
			{
				p_forw = 1;
			}
			if (GetAsyncKeyState(VK_NUMPAD2))
			{
				p_forw = 2;
			}

			if (GetAsyncKeyState(VK_SPACE))
			{
				switch (get_forward())
				{
				case 1:
				{
						  COORD temp;
						  temp.X = x; temp.Y = y - 1;
						  bul_U.push_back(temp);
						  break;
				}
				case 2:
				{
						  COORD temp;
						  temp.X = x; temp.Y = y + 1;
						  bul_D.push_back(temp);
						  break;
				}
				case 3:
				{
						  COORD temp;
						  temp.X = x - 1; temp.Y = y;
						  bul_L.push_back(temp);
						  break;
				}
				case 4:
				{
						  COORD temp;
						  temp.X = x + 1; temp.Y = y;
						  bul_R.push_back(temp);
						  break;
				}
				}

			}

			if (GetAsyncKeyState(VK_LEFT))
			{
				erase();
				--x;
				if (x < 0) x = 0;
				draw_time_clock();
			}
			if (GetAsyncKeyState(VK_RIGHT))
			{
				erase();
				++x;
				if (x>RIGHT_boundary) x = RIGHT_boundary;
				draw_time_clock();
			}
			if (GetAsyncKeyState(VK_UP))
			{
				erase();
				--y;
				if (y < 0) y = 0;
				draw_time_clock();
			}
			if (GetAsyncKeyState(VK_DOWN))
			{
				erase();
				++y;
				if (y>TOP_boundary) y = TOP_boundary;
				draw_time_clock();
			}

			flag = true;
			t_p = clock();
		}
	}

	//射击子弹函数(右上)
	void butl()
	{		
		if (clock() - t_b > t_bul)
		{
			for (int i = 0; i<bul.size(); ++i)
			{
				gotoxy(bul[i].X, bul[i].Y);
				cout << "  ";
				if (bul[i].Y>0 && bul[i].X < RIGHT_boundary)
				{
					--bul[i].Y;
					++bul[i].X;

					gotoxy(bul[i].X, bul[i].Y);
					cout << "*";
				}
				else
				{
					bul.erase(bul.begin() + i);
				}
			}
			t_b = clock();
		}
	}

	//射击子弹函数
	void butl_U()
	{
		if (clock() - t_b_u > t_bul)
		{
			for (int i = 0; i<bul_U.size(); ++i)
			{
				gotoxy(bul_U[i].X, bul_U[i].Y);
				cout << "  ";
				if (bul_U[i].Y>0)
				{
					--bul_U[i].Y;
					gotoxy(bul_U[i].X, bul_U[i].Y);
					cout << "|";
				}
				else
				{
					bul_U.erase(bul_U.begin() + i);
				}
			}
			t_b_u = clock();
		}
	}
	void butl_D()
	{
		if (clock() - t_b_d > t_bul)
		{
			for (int i = 0; i < bul_D.size(); ++i)
			{
				gotoxy(bul_D[i].X, bul_D[i].Y);
				cout << "  ";
				if (bul_D[i].Y < TOP_boundary)
				{
					++bul_D[i].Y;
					gotoxy(bul_D[i].X, bul_D[i].Y);
					cout << "|";
				}
				else
				{
					bul_D.erase(bul_D.begin() + i);
				}
			}
			t_b_d = clock();
		}
	}
	void butl_L()
	{
		if (clock() - t_b_l > t_bul)
		{
			for (int i = 0; i < bul_L.size(); ++i)
			{
				gotoxy(bul_L[i].X, bul_L[i].Y);
				cout << "  ";
				if (bul_L[i].X>0)
				{
					--bul_L[i].X;
					gotoxy(bul_L[i].X, bul_L[i].Y);
					cout << "-";
				}
				else
				{
					bul_L.erase(bul_L.begin() + i);
				}
			}
			t_b_l = clock();
		}
	}
	void butl_R()
	{
		if (clock() - t_b_r > t_bul)
		{
			for (int i = 0; i < bul_R.size(); ++i)
			{
				gotoxy(bul_R[i].X, bul_R[i].Y);
				cout << "  ";
				if (bul_R[i].X < RIGHT_boundary)
				{
					++bul_R[i].X;
					gotoxy(bul_R[i].X, bul_R[i].Y);
					cout << "-";
				}
				else
				{
					bul_R.erase(bul_R.begin() + i);
				}
			}
			t_b_r = clock();
		}
	}

	//产生射击目标函数
	void create_target()
	{

		if (clock() - t_tar_c > t_bul * 100)
		{
			srand(time(NULL));
			COORD temp;
			temp.X = rand() % RIGHT_boundary; temp.Y = rand() % TOP_boundary;
			targ.push_back(temp);

			t_tar_c = clock();
		}
	}

	//产生精确射击目标函数
	void create_exact_target(int input_x,int input_y)
	{
		COORD temp;
		temp.X = input_x; temp.Y = input_y;
		targ.push_back(temp);
	}

	//显示射击目标函数
	void show_targe()
	{	 

		int i;
		if (clock() - t_tar_s > t_bul)
		{
			gotoxy(1, 29);
			cout << "Targer num:" << targ.size() << endl;
			gotoxy(1, 30);
			cout << "HIT    num:" << tar_count << endl;
			for (i = 0; i<targ.size(); ++i)
			{
				gotoxy(targ[i].X, targ[i].Y);
				cout << "@";
			}
			t_tar_s = clock();
		}
	}

	//检查是否击中目标
	void check_target_alive()
	{
		int i, j,l,m,n;
		if (clock() - t_tar_alive > t_bul)
		{
			srand(time(NULL));
			for ( i = 0; i < targ.size(); ++i)
			{
				for (j = 0; j < bul_U.size(); ++j)
				{
					if (bul_U[j].X == targ[i].X && bul_U[j].Y == targ[i].Y)
					{
						gotoxy(targ[i].X, targ[i].Y);
						cout << "  ";
						targ.erase(targ.begin() + i);
						++tar_count;
						break;
					}
				}
				for (l = 0; l < bul_D.size(); ++l)
				{
					if (bul_D[l].X == targ[i].X && bul_D[l].Y == targ[i].Y)
					{
						gotoxy(targ[i].X, targ[i].Y);
						cout << "  ";
						targ.erase(targ.begin() + i);
						++tar_count;
						break;
					}
				}
				for (m = 0; m < bul_L.size(); ++m)
				{
					if (bul_L[m].X == targ[i].X && bul_L[m].Y == targ[i].Y)
					{
						gotoxy(targ[i].X, targ[i].Y);
						cout << "  ";
						targ.erase(targ.begin() + i);
						++tar_count;
						break;
					}
				}
				for (n = 0; n < bul_R.size(); ++n)
				{
					if (bul_R[n].X == targ[i].X && bul_R[n].Y == targ[i].Y)
					{
						gotoxy(targ[i].X, targ[i].Y);
						cout << "  ";
						targ.erase(targ.begin() + i);
						++tar_count;
						break;
					}
				}
			}
			t_tar_alive = clock();
		}
	}

	//检查游戏是否结束
	void check_game_over(int input_count,string input)
	{
		if (input_count <= tar_count)
		{
			gotoxy(5, 25);
			cout << input << endl;
			exit(input_count);
		}
	}

};



int main(void)
{
	//初始化
	Game_paotai g(13,13,40,50,10);
	string sent;
	sent = "Congratulations!,Misson Completed！\n";

	//产生一个坐标为30 5 的射击目标
	g.create_exact_target(30, 5);
	while (true)
	{
		g.show_targe();
		g.move();
		g.butl_U();
		g.butl_D();
	    g.butl_L();
		g.butl_R();
		g.check_target_alive();
		//参数说明，（需要击中的目标数,结束后输出的字符串)
		g.check_game_over(1, sent);
	}
}

