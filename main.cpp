#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<random>
#include<vector>
#include<deque>
#include<string>
#include"TRANS.h"
using namespace std;
class Block {
public:
	int x;//横坐标
	int y;//纵坐标
	int state;//状态
	int type;//类型
};
class game {
public:
	const int width = 30;
	const int height = 30;
	int origin_x = 270;
	int origin_y = 20;
	int ex_origin_x = 590;
	int ex_end_x = 710;
	int end_x = 570;
	int end_y = 620;
	int end_end_y = 640;
	int width_x = (end_x - origin_x) / width;
	int width_y = (end_y - origin_y) / width;
	const int bkcolor = 0x008F7A;
	//const int linecolor = RGB(255, 192, 203);
	const int linecolor = RGB(255, 192, 203);
	bool is_end = false;
	int score = 0;
	int pre_lo[2] = { 13,3 };
	//以三维数组存储地块状态和颜色
	int LandedBlock[10][20]{ 0 };
	//俄罗斯方块类型
	int Blocktype[7][4][4][2] =
	{
		{/*Type 0*/
			{{0, 0}, {-1, 0}, {1, 0}, {0, -1}},//坐标
			{{0, 0}, {1, 0}, {0, 1}, {0, -1}},
			{{0, 0}, {-1, 0}, {1, 0}, {0, 1}},
			{{0, 0}, {-1, 0}, {0, 1}, {0, -1}}
		},
		{/*Type 1*/
			{{0, 0},{0,-1},{1,-1},{-1,0}},
			{{0, 0},{0,-1},{1,0},{1,1}},
			{{0, 0},{-1,0},{0,-1},{1,-1}},
			{{0, 0},{0,-1},{1,0},{1,1}}
		},
		{/*Type 2*/
			{{0, 0},{-1,-1},{0,-1},{1,0}},
			{{0, 0},{1,0},{0,1},{1,-1}},
			{{0, 0},{-1,-1},{0,-1},{1,0}},
			{{0, 0},{1,-1},{1,0},{0,1}}
		},
		{/*Type 3*/
			{{0, 0},{-2,0},{-1,0},{1,0}},
			{{0, 0},{0,-2},{0,-1},{0,1}},
			{{0, 0},{-2,0},{-1,0},{1,0}},
			{{0, 0},{0,-2},{0,-1},{0,1}}
		},
		{/*Type 4*/
			{{0,0},{-1,-1},{0,-1},{-1,0}},
			{{0,0},{-1,-1},{0,-1},{-1,0}},
			{{0,0},{-1,-1},{0,-1},{-1,0}},
			{{0,0},{-1,-1},{0,-1},{-1,0}}
		},
		{/*Type 5*/
			{{0,0},{1,-1},{-1,0},{1,0}},
			{{1,1},{0,0},{0,-1},{0,1}},
			{{-1,1},{0,0},{-1,0},{1,0}},
			{{-1,-1},{0,0},{0,1},{0,-1}}
		},
		{/*Type 6*/
			{{0,0},{-1,0},{1,0},{1,1}},
			{{0,0},{0,1},{0,-1},{-1,1}},
			{{0,0},{-1,0},{1,0},{-1,-1}},
			{{0,0},{0,1},{0,-1},{1,-1}}
		}
	};
	wstring color[8] = { L"blue.jpg", L"green.jpg", L"yellow.jpg", L"red.jpg", L"cyan.jpg", L"lightblue.jpg", L"lightgreen.jpg",L"black.png" };
	deque<Block> b;//用于存储出现的方块
	wstring mizuki[2] = { L"水月.png",L"水月die.png" };
public:
	game() {
		return;
	}
	game(int origin_y,int end_y,int ex_origin_x,int ex_end_x,int origin_x,int end_x){
		this->origin_x = origin_x;
		this->origin_y = origin_y;
		this->ex_origin_x = ex_origin_x;
		this->ex_end_x = ex_end_x;
		this->end_y = end_y;
		this->end_x = end_x;
	}
	void drawbk() {
		//画边界
		setcolor(linecolor);
		rectangle(origin_x, origin_y, end_x, end_y);
		//画背景
		for (int i = 0; i < 10; i++) {
			line(origin_x + width * i, origin_y, origin_x + width * i, end_y);
		}
		for (int i = 0; i < 20; i++) {
			line(origin_x, origin_y + i * width, end_x, origin_y + i * width);
		}
		return;
	}
	void drawbkground() {
		initgraph(ex_end_x, 640);
		setbkcolor(bkcolor);
		cleardevice();
		//画边界
		setcolor(RGB(55, 88, 66));
		rectangle(origin_x, origin_y, end_x, end_y);
		//画背景
		for (int i = 0; i < end_x / width; i++) {
			line(origin_x + width * i, 0, origin_x + width * i, end_y);
		}
		for (int i = 0; i < end_y / width; i++) {
			line(origin_x, origin_y + i * width, end_x, origin_y + i * width);
		}
		//得分
		settextstyle(30, 0, _T("宋体"));
		settextcolor(linecolor);
		outtextxy(ex_origin_x + 10, 350, _T("得分："));
		outtextxy(ex_origin_x + 10, 400, _T("0"));
		settextstyle(20, 0, _T("宋体"));
		outtextxy(ex_origin_x + 10, 450, _T("q 退出游戏"));
		outtextxy(ex_origin_x + 10, 500, _T("c 重新开始"));
	}
	// 单个背景块
	void DrawbkUnitBlock(int block[2], int lo[2], int color) {
		int x = lo[0] + block[0];
		int y = (lo[1] + block[1]);
		if (x < 0) {
			setcolor(bkcolor);
		}
		else {
			setcolor(linecolor);
		}
		setfillcolor(bkcolor);
		fillrectangle(origin_x + (lo[0] + block[0]) * width, origin_y + (lo[1] + block[1]) * width, origin_x + (lo[0] + block[0] + 1) * width, origin_y + (lo[1] + block[1] + 1) * width);
		return;
	}
	// 单个方块对应的背景块
	void DrawbkBlock(Block b) {
		//画背景
		int lo[2] = { b.x,b.y };
		for (int i = 0; i < 4; i++) {
			DrawbkUnitBlock(Blocktype[b.type][b.state][i], lo, bkcolor);
		}
		return;
	}
	// 画一种类型的方块的单个方块
	void DrawUnitBlock(int block[2], int lo[2], wstring color) {
		int x = lo[0] + block[0];
		int y = (lo[1] + block[1]);
		IMAGE bk;
		loadimage(&bk, color.c_str(), 30, 30);
		IMAGE mask;
		loadimage(&mask, _T("掩码.jpg"), 30, 30);
		// 使用 SRCAND+SRCPAINT 的方法实现透明绘制
		putimage(origin_x + x * width, origin_y + y * width, &mask, NOTSRCERASE); // 第二次：绘制剩下部分
		putimage(origin_x + x * width, origin_y + y * width, &bk, SRCINVERT);
		// fillrectangle(origin_x + x * width, origin_y + y * width, origin_x + (x + 1) * width, origin_y + (y + 1) * width);
		return;
	}
	void DrawSingleBlock(int x, int y, wstring color) {
		IMAGE bk;
		loadimage(&bk, color.c_str(), 30, 30);
		IMAGE mask;
		loadimage(&mask, _T("掩码.jpg"), 30, 30);
		// 使用 SRCAND+SRCPAINT 的方法实现透明绘制
		setbkmode(TRANSPARENT);
		putimage(origin_x + x * width, origin_y + y * width, &mask, NOTSRCERASE); // 第二次：绘制剩下部分
		putimage(origin_x + x * width, origin_y + y * width, &bk, SRCINVERT);
		// fillrectangle(origin_x + x * width, origin_y + y * width, origin_x + (x + 1) * width, origin_y + (y + 1) * width);
		return;
	}
	// 一种类型的方块
	void Draw_block(Block b, wstring color) {
		int lo[2] = { b.x,b.y };
		for (int i = 0; i < 4; i++) {
			DrawUnitBlock(Blocktype[b.type][b.state][i], lo, color);
		}
		return;
	}
	virtual void update(int mode=0) {
		BeginBatchDraw();  // 开启批量绘图（双缓冲）
		// 导图
		IMAGE bk;
		loadimage(&bk, _T("背景.png"), 960, 640);
		putimage(0, 0, &bk);
		drawbk();
		//画地图
		for (int i = 0; i < width_x; i++) {
			for (int j = 0; j < width_y; j++) {
				// DrawUnitBlock()
				if (LandedBlock[i][j] != 0) {
					DrawSingleBlock(i, j, color[LandedBlock[i][j]-1]);
				}
			}
		}
		wstring leng = to_wstring(score);
		setbkmode(TRANSPARENT);// 设置文字背景为透明
		settextstyle(40, 0, _T("楷体"));
		settextcolor(linecolor);
		outtextxy(ex_origin_x + 90, 350, leng.c_str());
		settextstyle(30, 0, _T("楷体"));
		outtextxy(ex_origin_x + 10, 355, _T("得分："));

		if (b.size() < 2) {
			genBlock();
			if (is_end) {
				return;
			}
		}
		// 更新下落的方块
		Draw_block(b[0], color[b[0].type]);
		//画预先的方块
		for (int i = 0; i < 4; i++) {
			DrawUnitBlock(Blocktype[b[1].type][b[1].state][i], pre_lo, color[b[1].type]);
		}
		//画小人
		IMAGE character;
		loadimage(&character,mizuki[mode].c_str(), 200, 200);
		drawAlpha(&character,600, 400);

		FlushBatchDraw();  // 显示这一帧的内容
		return;
	}
	// 消除行
	void clear() {
		for (int i = 0; i < width_x; i++) {
			for (int j = 0; j < width_y; j++) {
				LandedBlock[i][j] = 0;
			}
		}
		while (!b.empty()) {
			b.pop_back();
		}
		return;
	}
	//判断是否到边界
	bool canGoLeft(Block b) {
		for (int i = 0; i < 4; i++) {
			if (b.x + Blocktype[b.type][b.state][i][0] <= 0 || LandedBlock[b.x - 1 + Blocktype[b.type][b.state][i][0]][b.y + Blocktype[b.type][b.state][i][1]] != 0) {
				return false;
			}
		}
		return true;
	}
	bool canGoRight(Block b) {
		for (int i = 0; i < 4; i++) {
			if (b.x + Blocktype[b.type][b.state][i][0] >= width_x - 1 || LandedBlock[b.x + Blocktype[b.type][b.state][i][0]][b.y + Blocktype[b.type][b.state][i][1]] != 0) {
				return false;
			}
		}
		return true;
	}
	bool canGoFall(Block b) {
		for (int i = 0; i < 4; i++) {
			if (b.y + Blocktype[b.type][b.state][i][1] >= width_y - 1 || LandedBlock[b.x + Blocktype[b.type][b.state][i][0]][b.y + Blocktype[b.type][b.state][i][1]] != 0) {
				return false;
			}
		}
		return true;
	}
	bool canRotate(Block b) {
		int state = (b.state + 1) % 4;
		//找到旋转之后最左边的
		int leftest = 0;
		for (int i = 0; i < 4; i++) {
			if (Blocktype[b.type][state][i][0] < leftest) {
				leftest = Blocktype[b.type][state][i][0];
			}
		}
		if (b.x + leftest < 0 || LandedBlock[b.x + leftest][b.y] != 0) {			return false;
		}
		//找到旋转之后最右边的
		int rightest = 0;
		for (int i = 0; i < 4; i++) {
			if (Blocktype[b.type][state][i][0] > rightest) {
				rightest = Blocktype[b.type][state][i][0];
			}
		}
		if (b.x + rightest > width_y-1 || LandedBlock[b.x + rightest][b.y] != 0) {
			return false;
		}
		//找到旋转之后最下边的
		int lowest = 0;
		for (int i = 0; i < 4; i++) {
			if (Blocktype[b.type][state][i][1] > lowest) {
				lowest = Blocktype[b.type][state][i][1];
			}
		}
		if (b.y + lowest > width_y - 1  || LandedBlock[b.x][b.y + lowest] != 0) {
			return false;
		}
		//找到旋转之后最上边的
		int highest = 0;
		for (int i = 0; i < 4; i++) {
			if (Blocktype[b.type][state][i][1] < highest) {
				highest = Blocktype[b.type][state][i][1];
			}
		}
		if (b.y + highest < 0 || LandedBlock[b.x][b.y + highest] != 0) {
			return false;
		}
		return true;
	}
	//检查是否落到底，用数组存储
	//用数组存储地图
	bool LandBlock() {
		//检查是否落地
		bool l = false;
		for (int j = 0; j < 4; j++) {
			if (b[0].y + Blocktype[b[0].type][b[0].state][j][1] + 1 < 0) {
				continue;
			}
			if (b[0].y + Blocktype[b[0].type][b[0].state][j][1] >= width_y - 1 || LandedBlock[b[0].x + Blocktype[b[0].type][b[0].state][j][0]][b[0].y + Blocktype[b[0].type][b[0].state][j][1] + 1] != 0) {
				cout << b[0].y << ' ' << b[0].x + Blocktype[b[0].type][b[0].state][j][0] << ' ' << b[0].y + Blocktype[b[0].type][b[0].state][j][1] + 1 << ' ' << LandedBlock[b[0].x + Blocktype[b[0].type][b[0].state][j][0]][b[0].y + Blocktype[b[0].type][b[0].state][j][1] + 1] << endl;
				l = true;
				break;
			}
		}
		if (l) {//如果落地则更新map,并且更新数组
			for (int j = 0; j < 4; j++) {
				if (b[0].y + Blocktype[b[0].type][b[0].state][j][1] < 0) {
					is_end = true;
					return true;
				}
				LandedBlock[b[0].x + Blocktype[b[0].type][b[0].state][j][0]][b[0].y + Blocktype[b[0].type][b[0].state][j][1]] = b[0].type + 1;
			}
			b.pop_front();
		}
		return l;
	}
	//实现块的移动
	void moveBlock() {
		//数组的第一个为最下面的一个
		if (GetAsyncKeyState('A') & 0x8000) {
			//首先重画背景
			if (canGoLeft(b[0])) {
				// DrawbkBlock(b[0]);
				b[0].x -= 1;
				Draw_block(b[0], color[b[0].type]);
			}
		}
		else if (GetAsyncKeyState('D') & 0x8000) {
			//首先重画背景
			if (canGoRight(b[0])) {
				// DrawbkBlock(b[0]);
				b[0].x += 1;
				Draw_block(b[0], color[b[0].type]);
			}
		}
		else if (GetAsyncKeyState('S') & 0x8000) {
			//首先重画背景
			if (canGoFall(b[0]) && !LandBlock()) {
				// DrawbkBlock(b[0]);
				b[0].y += 1;
				Draw_block(b[0], color[b[0].type]);
			}
		}
		else if (GetAsyncKeyState('W') & 0x8000) {
			// 首先重画背景
			if (canRotate(b[0])) {
				b[0].state++;
				b[0].state %= 4;
				Draw_block(b[0], color[b[0].type]);
			}
		}
		return;
	}
	//实现块的移动
	void moveBlock2() {
		//数组的第一个为最下面的一个
		if (GetAsyncKeyState(VK_LEFT)) {
			if (canGoLeft(b[0])) {
				b[0].x -= 1;
				Draw_block(b[0], color[b[0].type]);
			}
		}
		else if (GetAsyncKeyState(VK_RIGHT)) {
			if (canGoRight(b[0])) {
				b[0].x += 1;
				Draw_block(b[0], color[b[0].type]);
			}
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			if (canGoFall(b[0]) && !LandBlock()) {
				b[0].y += 1;
				Draw_block(b[0], color[b[0].type]);
			}
		}
		else if (GetAsyncKeyState(VK_UP)) {
			// 首先重画背景
			if (canRotate(b[0])) {
				b[0].state++;
				b[0].state %= 4;
				Draw_block(b[0], color[b[0].type]);
			}
		}
		
		return;
	}
	void Move_auto() {
		//从头开始更新位置
		// DrawbkBlock(b[0]);
		b[0].y += 1;
		return;
	}
	//块随机出现
	void genBlock() {
		mt19937 rng(random_device{}());
		uniform_int_distribution<int> dist_x(3, 7);
		uniform_int_distribution<int> dist_type(0, 6);
		uniform_int_distribution<int> dist_state(0, 3);
		Block ne;
		ne.x = dist_x(rng);
		ne.y = 0;
		ne.state = dist_state(rng);
		ne.type = dist_type(rng);
		b.push_back(ne);
		// 判断是否结束
		if (!is_end&&LandBlock()) {
			cout << "落地结束" << endl;
			is_end = true;
		}
		return;
	}
	bool end() {//结束模块
		int result = 0;
		result = MessageBox(
			GetHWnd(),           // 窗口句柄（EasyX 通过 GetHWnd() 获取）
			L"游戏结束\n重新开始？",     // 对话框内容
			L"游戏结束",              // 对话框标题
			MB_YESNO | MB_ICONQUESTION // 按钮和图标类型
		);
		if (result == IDYES) {
			
			return true;
		}
		else {
			return false;
		}
	}
	//消除行
	bool clean_row() {
		//如果有块落地则判断是否可以消除行
		//从下到上开始检查是否可以消除行
		vector<int> cleanrow;
		setcolor(WHITE);
		for (int i = width_y - 1; i >= 0; i--) {
			bool f = true;
			//找到应该消除的行
			for (int j = 0; j < width_x; j++) {
				if (LandedBlock[j][i] == 0||LandedBlock[j][i]==8) {
					f = false;
					break;
				}
			}
			if (f) {
				//记录需要消除的行
				cleanrow.push_back(i);
			}
		}
		//更新界面和数组
		for (int i = cleanrow.size() - 1; i >= 0; i--) {
			for (int m = cleanrow[i]; m >= 0; m--) {
				for (int n = 0; n < width_x; n++) {
					if (m != 0) {
						LandedBlock[n][m] = LandedBlock[n][m - 1];
					}
					else {
						LandedBlock[n][m] = 0;
					}
				}
			}
		}
		if (cleanrow.size() != 0) {
			score += cleanrow.size();
			return true;
		}
		else {
			return false;
		}
	}
	//控制模块
	//控制下落的块
	//简单模式（正常模式）
	void controler_easy() {
	start:
		BeginBatchDraw();  // 开启批量绘图（双缓冲）
		drawbk();
		wstring leng = to_wstring(score);
		setbkmode(TRANSPARENT);// 设置文字背景为透明
		settextstyle(40, 0, _T("楷体"));
		settextcolor(linecolor);
		outtextxy(ex_origin_x + 90, 350, leng.c_str());
		settextstyle(30, 0, _T("楷体"));
		outtextxy(ex_origin_x + 10, 355, _T("得分："));
		FlushBatchDraw();  // 显示这一帧的内容
		score = 0;
		is_end = false;
		int fall_r = -1;
		genBlock();//先产生一个作为开始
		while (!is_end) {
			fall_r++;
			update();
			if (fall_r % 2 == 0) {
				Move_auto();//块自动下落
				update();
				fall_r %= 2;
				if (LandBlock()) {
					if (is_end) {
						break;
					}
					if (clean_row()) {
						update();
					}
				}
			}
			//q为退出程序
			if (GetAsyncKeyState('Q') & 0x8000) {//退出游戏
				break;
			}
			else if (GetAsyncKeyState('C') & 0x8000) {//重新开始
				clear();
				goto start;
			}
			else {
				moveBlock();
			}
			//判断块是否落地
			if (LandBlock()) {
				if (is_end) {
					break;
				}
				if (clean_row()) {
					update();
				}
			}
			update();
			Sleep(10);
		}
		update(1);
		if (end()) {
			clear();
			goto start;
		}
		return;
	}
};
class game_double: public game{
private:
	int origin_y = 20;
	int end_y = 620;
	int ex_origin_x_l = 0;// 左边（玩家1
	int ex_end_x_l = 180;// 左边
	int origin_x_l = 180;
	int end_x_l = 480;
	int origin_x_r = 500;
	int end_x_r = 800;
	int ex_origin_x_r = 800;
	int ex_end_x_r = 980;//结尾
	int count1 = 0;
	int count2 = 0;
	int m1 = 0;
	int m2 = 0;
	wstring mizuki[6] = {L"水月.png",L"水月skill1.png",L"水月skill2.png",L"水月skill3.png",L"水月win.png",L"水月die.png"};
	wstring golden[6] = { L"澄闪.png",L"澄闪skill1.png",L"澄闪skill2.png",L"澄闪skill3.png",L"澄闪win.png",L"澄闪die.png" };
	// 右边
	game* player1;
	game* player2;
public:
	game_double() {
		player1 = new game(origin_y,end_y,ex_origin_x_l,ex_end_x_l,origin_x_l,end_x_l);//两个玩家
		player2 = new game(origin_y, end_y, ex_origin_x_r, ex_end_x_r, origin_x_r, end_x_r);//两个玩家
		player1->pre_lo[0] = -3;
	}
	void drawbk() {
		player1->drawbk();
		// (void)_getch();
		player2->drawbk();
		// (void)_getch();
		return;
	}
	int skill(game* p1,game*p2) {
		mt19937 rng(random_device{}());
		uniform_int_distribution<int> dist_p(0, 100);
		int p = dist_p(rng);
		//有40%概率不发动技能
		//20%概率清除最下面的一行
		//20%概率增加自己的得分
		//20%从底下增加对方的一行
		if (p > 80) {
			//更新界面和数组
			cout << "技能1" << endl;
			for (int m = width_y - 1; m >= 0; m--) {
				for (int n = 0; n < width_x; n++) {
					if (m != 0) {
						p1->LandedBlock[n][m] = p1->LandedBlock[n][m - 1];
					}
					else {
						p1->LandedBlock[n][m] = 0;
					}
				}
			}
			return 1;
		}
		else if (p > 60) {
			cout << "技能2" << endl;
			p1->score++;
			return 2;
		}
		else if (p > 40) {
			//更新界面和数组
			cout << "技能3" << endl;
			for (int m = 0; m < width_y; m++) {
				for (int n = 0; n < width_x; n++) {
					if (m != width_y-1) {
						p2->LandedBlock[n][m] = p2->LandedBlock[n][m +1];
					}
					else {
						p2->LandedBlock[n][m] = 8;//另一种颜色
					}
				}
			}
			return 3;
		}
		return 0;
	}
	void update(int mode1=0,int mode2=0) {
		BeginBatchDraw();  // 开启批量绘图（双缓冲）
		// 导图
		IMAGE bk;
		loadimage(&bk, _T("背景.png"), 980, 640);
		putimage(0, 0, &bk);
		drawbk();
		//画地图
		for (int i = 0; i < width_x; i++) {
			for (int j = 0; j < width_y; j++) {
				// DrawUnitBlock()
				if (player1->LandedBlock[i][j] != 0) {
					player1->DrawSingleBlock(i, j, player1->color[player1->LandedBlock[i][j] - 1]);
				}
				if (player2->LandedBlock[i][j] != 0) {
					player2->DrawSingleBlock(i, j, player2->color[player2->LandedBlock[i][j] - 1]);
				}
			}
		}
		wstring leng = to_wstring(player1->score);
		wstring leng2 = to_wstring(player2->score);
		setbkmode(TRANSPARENT);// 设置文字背景为透明
		settextstyle(40, 0, _T("行楷"));
		settextcolor(linecolor);
		outtextxy(ex_origin_x_l + 90, 350, leng.c_str());
		outtextxy(ex_origin_x_r + 100, 350, leng2.c_str());
		settextstyle(30, 0, _T("行楷"));
		outtextxy(ex_origin_x_l + 10, 355, _T("得分："));
		outtextxy(ex_origin_x_r + 20, 355, _T("得分："));

		if (player1->b.size() < 2) {
			player1->genBlock();
			if (player1->is_end || player2->is_end) {
				goto draw;
				//return;
			}
		}
		if (player2->b.size() < 2) {
			player2->genBlock();
			if (player1->is_end || player2->is_end) {
				goto draw;
				//return;
			}
		}
		if (player1->b.size() == 2) {
			// 更新下落的方块
			player1->Draw_block(player1->b[0], color[player1->b[0].type]);
			//画预先的方块
			for (int i = 0; i < 4; i++) {
				player1->DrawUnitBlock(Blocktype[player1->b[1].type][player1->b[1].state][i], player1->pre_lo, color[player1->b[1].type]);
			}
		}
		if (player2->b.size() == 2) {
			player2->Draw_block(player2->b[0], color[player2->b[0].type]);
			for (int i = 0; i < 4; i++) {
				player2->DrawUnitBlock(Blocktype[player2->b[1].type][player2->b[1].state][i], player2->pre_lo, color[player2->b[1].type]);
			}
		}

		draw:
		//画小人
		if (mode1 == 0&&count1<10) {
			mode1 = m1;
			count1++;
		}
		else {
			m1 = mode1;
			count1 = 0;
		}
		IMAGE character;
		loadimage(&character, mizuki[mode1].c_str(), 200, 200);
		drawAlpha(&character, 10, 400);

		if (mode2 == 0&&count2<10) {
			mode2 = m2;
			count2++;
		}
		else {
			m2 = mode2;
			count2 = 0;
		}
		// cout << mode1 << mode2;
		loadimage(&character, golden[mode2].c_str(),180,180);
		drawAlpha(&character, ex_origin_x_r - 30, 410);
		FlushBatchDraw();  // 显示这一帧的内容
		return;
	}
	void controler_easy() {
	start:
		BeginBatchDraw();  // 开启批量绘图（双缓冲）
		drawbk();
		setbkmode(TRANSPARENT);// 设置文字背景为透明
		settextstyle(30, 0, _T("宋体"));
		settextcolor(linecolor);
		outtextxy(ex_origin_x_l + 10, 400, _T("0"));
		outtextxy(ex_origin_x_r + 10, 400, _T("0"));
		FlushBatchDraw();  // 显示这一帧的内容
		player1->is_end = false;
		player2->is_end = false;
		player1->score = 0;
		player2->score = 0;
		int fall_r = -1;
		player1->genBlock();//先产生一个作为开始
		player2->genBlock();
		while (!player1->is_end&&!player2->is_end) {
			fall_r++;
			update();
			if (player1->is_end || player2->is_end) {
				break;
			}
			if (fall_r % 2 == 0) {
				player1->Move_auto();//块自动下落
				player2->Move_auto();
				update();
				fall_r %= 2;
				// 自动下落
				if (player1->LandBlock()) {
					if (player1->is_end || player2->is_end) {
						break;
					}
				}
				if (player2->LandBlock()) {
					if (player1->is_end || player2->is_end) {
						break;
					}
				}
				bool c1 = player1->clean_row();
				bool c2 = player2->clean_row();
				if (c1 || c2) {
					if (c1) {
						m1=skill(player1, player2);
					}
					if (c2) {
						m2=skill(player2, player1);
					}
					update(m1,m2);
				}
			}
			//q 为退出程序
			if (GetAsyncKeyState('Q') & 0x8000) {//退出游戏
				player1->is_end = true;
				player2->is_end = true;
				break;
			}
			else if (GetAsyncKeyState('C') & 0x8000) {//重新开始
				player1->clear();
				player2->clear();
				goto start;
			}
			else {
				player1->moveBlock();
				player2->moveBlock2();
			}
			//判断块是否落地
			if (player1->LandBlock()) {
				if (player1->is_end || player2->is_end) {
					break;
				}
			}
			if (player2->LandBlock()) {
				if (player1->is_end || player2->is_end) {
					break;
				}
			}
			Sleep(30);
		}
		if (player1->is_end&&!player2->is_end) {
			update(5, 4);
			cout << "执行结束" << endl;
		}
		else if (player2->is_end && !player1->is_end) {
			cout << "执行结束" << endl;
			update(4, 5);
		}
		else {
			update(5, 5);
		}
		if (end()) {
			player1->clear();
			player2->clear();
			goto start;
		}
		return;
	}
};
// 总控类
class play {
public:
	bool is_mode;// true为单人模式，false为双人模式
	bool is_end = false;
	int x = 960;
	int y = 640;
	int button1_x=120;
	int button1_y=385;
	int button2_x=370;
	int button2_y=385;
	int button3_x = 620;
	int button3_y = 385;
	play() {}
	// 创建开始界面
	// 读入用户的点击
	// 选择模式
	// 根据选择的模式进行下一步的页面替换（单人模式的页面大小
	void start() {
		initgraph(x,y);
		// 导图
		IMAGE bk;
		loadimage(&bk, _T("制作动漫风格俄罗斯方块开始界面.png"), x, y);
		putimage(0, 0, &bk);
		// setlinecolor(BLACK);
		/*rectangle(button1_x, button1_y, button1_x + 220, button1_y + 100);
		rectangle(button2_x, button2_y, button2_x + 220, button2_y + 100);
		rectangle(button3_x, button3_y, button3_x + 220, button3_y + 100);*/
		// 检测点击
		ExMessage msg;
		while (true) {
			msg = getmessage();
			if (msg.message == WM_LBUTTONDOWN) {
				if (msg.x >= button1_x && msg.x <= button1_x + 220 && msg.y >= button1_y && msg.y <= button1_y + 100) {
					is_mode = true;//开始
					return;
				}
				else if (msg.x >= button2_x && msg.x <= button2_x + 220 && msg.y >= button2_y && msg.y <= button2_y + 100) {
					is_mode = false;//退出
					return;
				}
				else if (msg.x >= button3_x && msg.x <= button3_x + 220 && msg.y >= button3_y && msg.y <= button3_y + 100) {
					is_end = true;
					return;
				}
			}
		}
	}
	void mode() {
		// 导图
		IMAGE bk;
		loadimage(&bk, _T("背景.png"), x, y);
		putimage(0, 0, &bk);
		return;
	}
	void controler() {
		start();
		if (is_end) {//结束了
			return;// 退出游戏
		}
		mode();
		if (is_mode) {// 单人模式
			game* p = new game();
			p->controler_easy();
			return;
		}
		else {// 双人模式
			game_double* p = new game_double();
			p->controler_easy();// 运行
		}
	}
};
int main() {
	play* a = new play();
	a->controler();
	//(void)_getch();
	closegraph();
	return 0;
}