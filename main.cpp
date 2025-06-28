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
	int x;//������
	int y;//������
	int state;//״̬
	int type;//����
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
	//����ά����洢�ؿ�״̬����ɫ
	int LandedBlock[10][20]{ 0 };
	//����˹��������
	int Blocktype[7][4][4][2] =
	{
		{/*Type 0*/
			{{0, 0}, {-1, 0}, {1, 0}, {0, -1}},//����
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
	deque<Block> b;//���ڴ洢���ֵķ���
	wstring mizuki[2] = { L"ˮ��.png",L"ˮ��die.png" };
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
		//���߽�
		setcolor(linecolor);
		rectangle(origin_x, origin_y, end_x, end_y);
		//������
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
		//���߽�
		setcolor(RGB(55, 88, 66));
		rectangle(origin_x, origin_y, end_x, end_y);
		//������
		for (int i = 0; i < end_x / width; i++) {
			line(origin_x + width * i, 0, origin_x + width * i, end_y);
		}
		for (int i = 0; i < end_y / width; i++) {
			line(origin_x, origin_y + i * width, end_x, origin_y + i * width);
		}
		//�÷�
		settextstyle(30, 0, _T("����"));
		settextcolor(linecolor);
		outtextxy(ex_origin_x + 10, 350, _T("�÷֣�"));
		outtextxy(ex_origin_x + 10, 400, _T("0"));
		settextstyle(20, 0, _T("����"));
		outtextxy(ex_origin_x + 10, 450, _T("q �˳���Ϸ"));
		outtextxy(ex_origin_x + 10, 500, _T("c ���¿�ʼ"));
	}
	// ����������
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
	// ���������Ӧ�ı�����
	void DrawbkBlock(Block b) {
		//������
		int lo[2] = { b.x,b.y };
		for (int i = 0; i < 4; i++) {
			DrawbkUnitBlock(Blocktype[b.type][b.state][i], lo, bkcolor);
		}
		return;
	}
	// ��һ�����͵ķ���ĵ�������
	void DrawUnitBlock(int block[2], int lo[2], wstring color) {
		int x = lo[0] + block[0];
		int y = (lo[1] + block[1]);
		IMAGE bk;
		loadimage(&bk, color.c_str(), 30, 30);
		IMAGE mask;
		loadimage(&mask, _T("����.jpg"), 30, 30);
		// ʹ�� SRCAND+SRCPAINT �ķ���ʵ��͸������
		putimage(origin_x + x * width, origin_y + y * width, &mask, NOTSRCERASE); // �ڶ��Σ�����ʣ�²���
		putimage(origin_x + x * width, origin_y + y * width, &bk, SRCINVERT);
		// fillrectangle(origin_x + x * width, origin_y + y * width, origin_x + (x + 1) * width, origin_y + (y + 1) * width);
		return;
	}
	void DrawSingleBlock(int x, int y, wstring color) {
		IMAGE bk;
		loadimage(&bk, color.c_str(), 30, 30);
		IMAGE mask;
		loadimage(&mask, _T("����.jpg"), 30, 30);
		// ʹ�� SRCAND+SRCPAINT �ķ���ʵ��͸������
		setbkmode(TRANSPARENT);
		putimage(origin_x + x * width, origin_y + y * width, &mask, NOTSRCERASE); // �ڶ��Σ�����ʣ�²���
		putimage(origin_x + x * width, origin_y + y * width, &bk, SRCINVERT);
		// fillrectangle(origin_x + x * width, origin_y + y * width, origin_x + (x + 1) * width, origin_y + (y + 1) * width);
		return;
	}
	// һ�����͵ķ���
	void Draw_block(Block b, wstring color) {
		int lo[2] = { b.x,b.y };
		for (int i = 0; i < 4; i++) {
			DrawUnitBlock(Blocktype[b.type][b.state][i], lo, color);
		}
		return;
	}
	virtual void update(int mode=0) {
		BeginBatchDraw();  // ����������ͼ��˫���壩
		// ��ͼ
		IMAGE bk;
		loadimage(&bk, _T("����.png"), 960, 640);
		putimage(0, 0, &bk);
		drawbk();
		//����ͼ
		for (int i = 0; i < width_x; i++) {
			for (int j = 0; j < width_y; j++) {
				// DrawUnitBlock()
				if (LandedBlock[i][j] != 0) {
					DrawSingleBlock(i, j, color[LandedBlock[i][j]-1]);
				}
			}
		}
		wstring leng = to_wstring(score);
		setbkmode(TRANSPARENT);// �������ֱ���Ϊ͸��
		settextstyle(40, 0, _T("����"));
		settextcolor(linecolor);
		outtextxy(ex_origin_x + 90, 350, leng.c_str());
		settextstyle(30, 0, _T("����"));
		outtextxy(ex_origin_x + 10, 355, _T("�÷֣�"));

		if (b.size() < 2) {
			genBlock();
			if (is_end) {
				return;
			}
		}
		// ��������ķ���
		Draw_block(b[0], color[b[0].type]);
		//��Ԥ�ȵķ���
		for (int i = 0; i < 4; i++) {
			DrawUnitBlock(Blocktype[b[1].type][b[1].state][i], pre_lo, color[b[1].type]);
		}
		//��С��
		IMAGE character;
		loadimage(&character,mizuki[mode].c_str(), 200, 200);
		drawAlpha(&character,600, 400);

		FlushBatchDraw();  // ��ʾ��һ֡������
		return;
	}
	// ������
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
	//�ж��Ƿ񵽱߽�
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
		//�ҵ���ת֮������ߵ�
		int leftest = 0;
		for (int i = 0; i < 4; i++) {
			if (Blocktype[b.type][state][i][0] < leftest) {
				leftest = Blocktype[b.type][state][i][0];
			}
		}
		if (b.x + leftest < 0 || LandedBlock[b.x + leftest][b.y] != 0) {			return false;
		}
		//�ҵ���ת֮�����ұߵ�
		int rightest = 0;
		for (int i = 0; i < 4; i++) {
			if (Blocktype[b.type][state][i][0] > rightest) {
				rightest = Blocktype[b.type][state][i][0];
			}
		}
		if (b.x + rightest > width_y-1 || LandedBlock[b.x + rightest][b.y] != 0) {
			return false;
		}
		//�ҵ���ת֮�����±ߵ�
		int lowest = 0;
		for (int i = 0; i < 4; i++) {
			if (Blocktype[b.type][state][i][1] > lowest) {
				lowest = Blocktype[b.type][state][i][1];
			}
		}
		if (b.y + lowest > width_y - 1  || LandedBlock[b.x][b.y + lowest] != 0) {
			return false;
		}
		//�ҵ���ת֮�����ϱߵ�
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
	//����Ƿ��䵽�ף�������洢
	//������洢��ͼ
	bool LandBlock() {
		//����Ƿ����
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
		if (l) {//�����������map,���Ҹ�������
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
	//ʵ�ֿ���ƶ�
	void moveBlock() {
		//����ĵ�һ��Ϊ�������һ��
		if (GetAsyncKeyState('A') & 0x8000) {
			//�����ػ�����
			if (canGoLeft(b[0])) {
				// DrawbkBlock(b[0]);
				b[0].x -= 1;
				Draw_block(b[0], color[b[0].type]);
			}
		}
		else if (GetAsyncKeyState('D') & 0x8000) {
			//�����ػ�����
			if (canGoRight(b[0])) {
				// DrawbkBlock(b[0]);
				b[0].x += 1;
				Draw_block(b[0], color[b[0].type]);
			}
		}
		else if (GetAsyncKeyState('S') & 0x8000) {
			//�����ػ�����
			if (canGoFall(b[0]) && !LandBlock()) {
				// DrawbkBlock(b[0]);
				b[0].y += 1;
				Draw_block(b[0], color[b[0].type]);
			}
		}
		else if (GetAsyncKeyState('W') & 0x8000) {
			// �����ػ�����
			if (canRotate(b[0])) {
				b[0].state++;
				b[0].state %= 4;
				Draw_block(b[0], color[b[0].type]);
			}
		}
		return;
	}
	//ʵ�ֿ���ƶ�
	void moveBlock2() {
		//����ĵ�һ��Ϊ�������һ��
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
			// �����ػ�����
			if (canRotate(b[0])) {
				b[0].state++;
				b[0].state %= 4;
				Draw_block(b[0], color[b[0].type]);
			}
		}
		
		return;
	}
	void Move_auto() {
		//��ͷ��ʼ����λ��
		// DrawbkBlock(b[0]);
		b[0].y += 1;
		return;
	}
	//���������
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
		// �ж��Ƿ����
		if (!is_end&&LandBlock()) {
			cout << "��ؽ���" << endl;
			is_end = true;
		}
		return;
	}
	bool end() {//����ģ��
		int result = 0;
		result = MessageBox(
			GetHWnd(),           // ���ھ����EasyX ͨ�� GetHWnd() ��ȡ��
			L"��Ϸ����\n���¿�ʼ��",     // �Ի�������
			L"��Ϸ����",              // �Ի������
			MB_YESNO | MB_ICONQUESTION // ��ť��ͼ������
		);
		if (result == IDYES) {
			
			return true;
		}
		else {
			return false;
		}
	}
	//������
	bool clean_row() {
		//����п�������ж��Ƿ����������
		//���µ��Ͽ�ʼ����Ƿ����������
		vector<int> cleanrow;
		setcolor(WHITE);
		for (int i = width_y - 1; i >= 0; i--) {
			bool f = true;
			//�ҵ�Ӧ����������
			for (int j = 0; j < width_x; j++) {
				if (LandedBlock[j][i] == 0||LandedBlock[j][i]==8) {
					f = false;
					break;
				}
			}
			if (f) {
				//��¼��Ҫ��������
				cleanrow.push_back(i);
			}
		}
		//���½��������
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
	//����ģ��
	//��������Ŀ�
	//��ģʽ������ģʽ��
	void controler_easy() {
	start:
		BeginBatchDraw();  // ����������ͼ��˫���壩
		drawbk();
		wstring leng = to_wstring(score);
		setbkmode(TRANSPARENT);// �������ֱ���Ϊ͸��
		settextstyle(40, 0, _T("����"));
		settextcolor(linecolor);
		outtextxy(ex_origin_x + 90, 350, leng.c_str());
		settextstyle(30, 0, _T("����"));
		outtextxy(ex_origin_x + 10, 355, _T("�÷֣�"));
		FlushBatchDraw();  // ��ʾ��һ֡������
		score = 0;
		is_end = false;
		int fall_r = -1;
		genBlock();//�Ȳ���һ����Ϊ��ʼ
		while (!is_end) {
			fall_r++;
			update();
			if (fall_r % 2 == 0) {
				Move_auto();//���Զ�����
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
			//qΪ�˳�����
			if (GetAsyncKeyState('Q') & 0x8000) {//�˳���Ϸ
				break;
			}
			else if (GetAsyncKeyState('C') & 0x8000) {//���¿�ʼ
				clear();
				goto start;
			}
			else {
				moveBlock();
			}
			//�жϿ��Ƿ����
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
	int ex_origin_x_l = 0;// ��ߣ����1
	int ex_end_x_l = 180;// ���
	int origin_x_l = 180;
	int end_x_l = 480;
	int origin_x_r = 500;
	int end_x_r = 800;
	int ex_origin_x_r = 800;
	int ex_end_x_r = 980;//��β
	int count1 = 0;
	int count2 = 0;
	int m1 = 0;
	int m2 = 0;
	wstring mizuki[6] = {L"ˮ��.png",L"ˮ��skill1.png",L"ˮ��skill2.png",L"ˮ��skill3.png",L"ˮ��win.png",L"ˮ��die.png"};
	wstring golden[6] = { L"����.png",L"����skill1.png",L"����skill2.png",L"����skill3.png",L"����win.png",L"����die.png" };
	// �ұ�
	game* player1;
	game* player2;
public:
	game_double() {
		player1 = new game(origin_y,end_y,ex_origin_x_l,ex_end_x_l,origin_x_l,end_x_l);//�������
		player2 = new game(origin_y, end_y, ex_origin_x_r, ex_end_x_r, origin_x_r, end_x_r);//�������
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
		//��40%���ʲ���������
		//20%��������������һ��
		//20%���������Լ��ĵ÷�
		//20%�ӵ������ӶԷ���һ��
		if (p > 80) {
			//���½��������
			cout << "����1" << endl;
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
			cout << "����2" << endl;
			p1->score++;
			return 2;
		}
		else if (p > 40) {
			//���½��������
			cout << "����3" << endl;
			for (int m = 0; m < width_y; m++) {
				for (int n = 0; n < width_x; n++) {
					if (m != width_y-1) {
						p2->LandedBlock[n][m] = p2->LandedBlock[n][m +1];
					}
					else {
						p2->LandedBlock[n][m] = 8;//��һ����ɫ
					}
				}
			}
			return 3;
		}
		return 0;
	}
	void update(int mode1=0,int mode2=0) {
		BeginBatchDraw();  // ����������ͼ��˫���壩
		// ��ͼ
		IMAGE bk;
		loadimage(&bk, _T("����.png"), 980, 640);
		putimage(0, 0, &bk);
		drawbk();
		//����ͼ
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
		setbkmode(TRANSPARENT);// �������ֱ���Ϊ͸��
		settextstyle(40, 0, _T("�п�"));
		settextcolor(linecolor);
		outtextxy(ex_origin_x_l + 90, 350, leng.c_str());
		outtextxy(ex_origin_x_r + 100, 350, leng2.c_str());
		settextstyle(30, 0, _T("�п�"));
		outtextxy(ex_origin_x_l + 10, 355, _T("�÷֣�"));
		outtextxy(ex_origin_x_r + 20, 355, _T("�÷֣�"));

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
			// ��������ķ���
			player1->Draw_block(player1->b[0], color[player1->b[0].type]);
			//��Ԥ�ȵķ���
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
		//��С��
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
		FlushBatchDraw();  // ��ʾ��һ֡������
		return;
	}
	void controler_easy() {
	start:
		BeginBatchDraw();  // ����������ͼ��˫���壩
		drawbk();
		setbkmode(TRANSPARENT);// �������ֱ���Ϊ͸��
		settextstyle(30, 0, _T("����"));
		settextcolor(linecolor);
		outtextxy(ex_origin_x_l + 10, 400, _T("0"));
		outtextxy(ex_origin_x_r + 10, 400, _T("0"));
		FlushBatchDraw();  // ��ʾ��һ֡������
		player1->is_end = false;
		player2->is_end = false;
		player1->score = 0;
		player2->score = 0;
		int fall_r = -1;
		player1->genBlock();//�Ȳ���һ����Ϊ��ʼ
		player2->genBlock();
		while (!player1->is_end&&!player2->is_end) {
			fall_r++;
			update();
			if (player1->is_end || player2->is_end) {
				break;
			}
			if (fall_r % 2 == 0) {
				player1->Move_auto();//���Զ�����
				player2->Move_auto();
				update();
				fall_r %= 2;
				// �Զ�����
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
			//q Ϊ�˳�����
			if (GetAsyncKeyState('Q') & 0x8000) {//�˳���Ϸ
				player1->is_end = true;
				player2->is_end = true;
				break;
			}
			else if (GetAsyncKeyState('C') & 0x8000) {//���¿�ʼ
				player1->clear();
				player2->clear();
				goto start;
			}
			else {
				player1->moveBlock();
				player2->moveBlock2();
			}
			//�жϿ��Ƿ����
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
			cout << "ִ�н���" << endl;
		}
		else if (player2->is_end && !player1->is_end) {
			cout << "ִ�н���" << endl;
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
// �ܿ���
class play {
public:
	bool is_mode;// trueΪ����ģʽ��falseΪ˫��ģʽ
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
	// ������ʼ����
	// �����û��ĵ��
	// ѡ��ģʽ
	// ����ѡ���ģʽ������һ����ҳ���滻������ģʽ��ҳ���С
	void start() {
		initgraph(x,y);
		// ��ͼ
		IMAGE bk;
		loadimage(&bk, _T("��������������˹���鿪ʼ����.png"), x, y);
		putimage(0, 0, &bk);
		// setlinecolor(BLACK);
		/*rectangle(button1_x, button1_y, button1_x + 220, button1_y + 100);
		rectangle(button2_x, button2_y, button2_x + 220, button2_y + 100);
		rectangle(button3_x, button3_y, button3_x + 220, button3_y + 100);*/
		// �����
		ExMessage msg;
		while (true) {
			msg = getmessage();
			if (msg.message == WM_LBUTTONDOWN) {
				if (msg.x >= button1_x && msg.x <= button1_x + 220 && msg.y >= button1_y && msg.y <= button1_y + 100) {
					is_mode = true;//��ʼ
					return;
				}
				else if (msg.x >= button2_x && msg.x <= button2_x + 220 && msg.y >= button2_y && msg.y <= button2_y + 100) {
					is_mode = false;//�˳�
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
		// ��ͼ
		IMAGE bk;
		loadimage(&bk, _T("����.png"), x, y);
		putimage(0, 0, &bk);
		return;
	}
	void controler() {
		start();
		if (is_end) {//������
			return;// �˳���Ϸ
		}
		mode();
		if (is_mode) {// ����ģʽ
			game* p = new game();
			p->controler_easy();
			return;
		}
		else {// ˫��ģʽ
			game_double* p = new game_double();
			p->controler_easy();// ����
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