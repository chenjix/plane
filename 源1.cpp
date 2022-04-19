#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include<time.h>
#include<Windows.h>
#include <mmsystem.h>
#define bullet_num 3000
#define enemy_num 20
#define supply_num 20
int height = 600, width = 470;
int score = 0;
int shoot_mode = 0;
int shoot_mode1_time = 0;
int shoot_mode2_time = 0;
int level = 1;
int level_flag1 = 0, level_flag2 = 0;
int win = 0;
double bk_h1 = 700 - height, bk_h2 = 1026 - height, bk_h3 = 717 - height;
struct plane {
	double x;
	double y;
	int islive;
	int enemy_width;
	int enemy_height;
	int blood;//Ѫ��
	int type;//�л�����
	int enemy_mark;
	double vx, vy;
}my_player, bull[bullet_num], enemy[enemy_num], supply[supply_num], boss;


IMAGE bk, bk1, bk2;
IMAGE img_player[2];
IMAGE img_bull[2];
IMAGE img_enemy[5][2];
IMAGE img_enemy_down[4][2];
IMAGE img_supply[3][2];
//����ͼƬ
void loadImg() {
	//���ر���ͼƬ
	loadimage(&bk, "./images/background.png");
	loadimage(&bk1, "./images/bk4.jpg");
	loadimage(&bk2, "./images/bk5.jpg");
	loadimage(&img_player[0], "./images/me02.png");
	loadimage(&img_player[1], "./images/me01.png");
	loadimage(&img_bull[0], "./images/BULLET.1.png");
	loadimage(&img_bull[1], "./images/bullet1.png");
	loadimage(&img_enemy[0][0], "./images/en1.2.png");
	loadimage(&img_enemy[0][1], "./images/en1.1.png");
	loadimage(&img_enemy[2][0], "./images/en2.2.png");
	loadimage(&img_enemy[2][1], "./images/en2.1.png");
	loadimage(&img_enemy[1][0], "./images/bomb002.png");
	loadimage(&img_enemy[1][1], "./images/bomb001.png");
	loadimage(&img_enemy[3][0], "./images/boss.1.png");
	loadimage(&img_enemy[3][1], "./images/boss.2.png");
	loadimage(&img_supply[0][0], "./images/supp2.png");
	loadimage(&img_supply[0][1], "./images/supp1.png");
	loadimage(&img_supply[1][0], "./images/supply2.png");
	loadimage(&img_supply[1][1], "./images/supply1.png");
	loadimage(&img_supply[2][0], "./images/sup2.png");
	loadimage(&img_supply[2][1], "./images/sup1.png");
	loadimage(&img_enemy_down[0][0], "./images/endown.1.png");
	loadimage(&img_enemy_down[0][1], "./images/endown.2.png");
}
//��Ϸ��ʼ��
void plane_init() {
	settextcolor(RED);
	settextstyle(30, 0, "Berlin Sans FB");
	setbkmode(TRANSPARENT);
	my_player.x = width / 2 - 49;
	my_player.y = height - 123;
	my_player.enemy_width = 102;
	my_player.enemy_height = 126;
	my_player.islive = 1;
	my_player.blood = 20;
	loadImg();
	//��ʼ���ӵ�
	for (int i = 0; i < bullet_num; i++) {
		bull[i].islive = 0;
		bull[i].x = 0;
		bull[i].y = 0;
		bull[i].enemy_mark = 0;
		bull[i].vx = 0;
		bull[i].vy = 0;
	}
	//��ʼ���л�
	for (int i = 0; i < enemy_num; i++) {
		enemy[i].islive = 0;
		if (i == 0) {
			enemy[i].type = 2;
			enemy[i].blood = 5;
			enemy[i].enemy_width = 69;
			enemy[i].enemy_height = 88;
		}
		else if (rand() % 10 == 1 || rand() % 10 == 2 || rand() % 10 == 3) {
			enemy[i].type = 1;
			enemy[i].blood = 3;
			enemy[i].enemy_width = 62;
			enemy[i].enemy_height = 53;
		}
		else {
			enemy[i].type = 0;
			enemy[i].blood = 1;
			enemy[i].enemy_width = 49;
			enemy[i].enemy_height = 35;
		}
	}
	//��ʼ������
	for (int i = 0; i < supply_num; i++) {
		supply[i].islive = 0;
		supply[i].x = 0;
		supply[i].y = 0;
	}
	//��ʼ��boss
	boss.islive = 0;
	boss.blood = 30;
	boss.enemy_width = 165;
	boss.enemy_height = 254;
	boss.x = width / 2 - boss.enemy_width / 2;
	boss.y = 0;
}
void createBullet() {
	for (int i = 0; i < bullet_num; i++) {
		if (!bull[i].islive) {
			bull[i].islive = 1;
			bull[i].x = my_player.x + 49;
			bull[i].y = my_player.y;
			break;
		}
	}
}
void createEnemyBullet(double x, double y) {
	for (int i = 0; i < bullet_num; i++) {
		if (!bull[i].islive) {
			bull[i].islive = 1;
			bull[i].x = x;
			bull[i].y = y;
			bull[i].enemy_mark = 1;
			break;
		}
	}
}
void createBossBullet(double x, double y) {
	for (int i = 0; i < bullet_num; i++) {
		if (!bull[i].islive) {
			bull[i].islive = 1;
			bull[i].x = x;
			bull[i].y = y;
			bull[i].enemy_mark = 2;
			break;
		}
	}
}
void createBossBullet2(double x, double y) {
	for (int j = 1; j <= 12; j++) {
		for (int i = 0; i < bullet_num; i++) {
			if (!bull[i].islive) {
				bull[i].islive = 1;
				bull[i].x = x;
				bull[i].y = y;
				switch (j) {
				case 1:
					bull[i].vx = -0.2;
					bull[i].vy = 0;
					break;
				case 2:
					bull[i].vx = -0.173;
					bull[i].vy = -0.1;
					break;
				case 3:
					bull[i].vx = -0.1;
					bull[i].vy = -0.173;
					break;
				case 4:
					bull[i].vx = 0;
					bull[i].vy = -0.2;
					break;
				case 5:
					bull[i].vx = 0.1;
					bull[i].vy = -0.173;
					break;
				case 6:
					bull[i].vx = 0.173;
					bull[i].vy = -0.1;
					break;
				case 7:
					bull[i].vx = 0.2;
					bull[i].vy = 0;
					break;
				case 8:
					bull[i].vx = 0.173;
					bull[i].vy = 0.1;
					break;
				case 9:
					bull[i].vx = 0.1;
					bull[i].vy = 0.173;
					break;
				case 10:
					bull[i].vx = 0;
					bull[i].vy = 0.2;
					break;
				case 11:
					bull[i].vx = -0.1;
					bull[i].vy = 0.173;
					break;
				case 12:
					bull[i].vx = -0.173;
					bull[i].vy = 0.1;
					break;
				}
				bull[i].enemy_mark = 3;
				break;
			}
		}
	}
}
//�����л�
void create_enemy() {
	for (int i = 0; i < enemy_num; i++) {
		if (!enemy[i].islive) {
			enemy[i].islive = 1;
			if (enemy[i].type == 0)
				enemy[i].blood = 1;
			if (enemy[i].type == 1)
				enemy[i].blood = 3;
			if (enemy[i].type == 2)
				enemy[i].blood = 5;
			enemy[i].x = rand() % (width - 60);
			enemy[i].y = 0;
			break;
		}
	}
}
//��������
void createSupply(double x, double y) {
	for (int i = 0; i < supply_num; i++) {
		if (!supply[i].islive) {
			supply[i].islive = 1;
			supply[i].x = x;
			supply[i].y = y;
			if (rand() % 5 == 0) {
				supply[i].type = 1;
				supply[i].enemy_width = 58;
				supply[i].enemy_height = 103;
			}
			else if (rand() % 5 == 3) {
				supply[i].type = 2;
				supply[i].enemy_width = 56;
				supply[i].enemy_height = 50;
			}
			else {
				supply[i].type = 0;
				supply[i].enemy_width = 57;
				supply[i].enemy_height = 85;
			}
			break;
		}
	}
}
void write_num(int x, int y, int num) {
	char n[20];
	sprintf_s(n, "%d", num);
	outtextxy(x, y, n);
}
//���ƽ���
void draw() {
	if (level == 1)
		putimage(0, bk_h1, &bk);
	if (level == 2)
		putimage(0, bk_h2, &bk1);
	if (level == 3)
		putimage(0, bk_h3, &bk2);
	putimage(my_player.x, my_player.y, &img_player[0], NOTSRCERASE);
	putimage(my_player.x, my_player.y, &img_player[1], SRCINVERT);
	//����boss
	if (boss.islive == 1) {
		putimage(boss.x, boss.y, &img_enemy[3][0], NOTSRCERASE);
		putimage(boss.x, boss.y, &img_enemy[3][1], SRCINVERT);
	}
	//���Ƶл�
	for (int i = 0; i < enemy_num; i++) {
		if (enemy[i].islive) {
			if (enemy[i].type == 0) {
				putimage(enemy[i].x, enemy[i].y, &img_enemy[enemy[i].type][0], NOTSRCERASE);
				putimage(enemy[i].x, enemy[i].y, &img_enemy[enemy[i].type][1], SRCINVERT);
			}
			else if (enemy[i].type == 1) {
				putimage(enemy[i].x, enemy[i].y, &img_enemy[enemy[i].type][0], NOTSRCERASE);
				putimage(enemy[i].x, enemy[i].y, &img_enemy[enemy[i].type][1], SRCINVERT);
			}
			else {
				putimage(enemy[i].x, enemy[i].y, &img_enemy[2][0], NOTSRCERASE);
				putimage(enemy[i].x, enemy[i].y, &img_enemy[2][1], SRCINVERT);
			}
		}
	}
	//���Ƶ���
	for (int i = 0; i < supply_num; i++) {
		if (supply[i].islive) {
			if (supply[i].type == 0) {
				putimage(supply[i].x, supply[i].y, &img_supply[0][0], NOTSRCERASE);
				putimage(supply[i].x, supply[i].y, &img_supply[0][1], SRCINVERT);
			}
			else if (supply[i].type == 1) {
				putimage(supply[i].x, supply[i].y, &img_supply[1][0], NOTSRCERASE);
				putimage(supply[i].x, supply[i].y, &img_supply[1][1], SRCINVERT);
			}
			else if (supply[i].type == 2) {
				putimage(supply[i].x, supply[i].y, &img_supply[2][0], NOTSRCERASE);
				putimage(supply[i].x, supply[i].y, &img_supply[2][1], SRCINVERT);
			}
		}
	}
	//�����ӵ�
	for (int i = 0; i < bullet_num; i++) {
		if (bull[i].islive) {
			putimage(bull[i].x, bull[i].y, &img_bull[0], NOTSRCERASE);
			putimage(bull[i].x, bull[i].y, &img_bull[1], SRCINVERT);
		}
	}
	outtextxy(width - 120, 20, "score:");
	write_num(width - 50, 20, score);
	outtextxy(width - 120, 60, "blood:");
	write_num(width - 50, 60, my_player.blood);
	outtextxy(width - 120, 100, "level:");
	write_num(width - 50, 100, level);
}

//��ʱ��
bool timer(int ms, int id) {
	static DWORD t[10];
	if (clock() - t[id] > ms) {
		t[id] = clock();
		return true;
	}
	return false;
}
void plane_move(double speed) {
#if 0
	//����Ƿ��м�������
	if (_kbhit()) {
		char key = _getch();
		switch (key)
		{
		case 'w':
			my_player.y -= speed;
			break;
		case 'W':
			my_player.y -= speed;
			break;
		case 'a':
			my_player.x -= speed;
			break;
		case 'A':
			my_player.x -= speed;
			break;
		case 's':case 'S':
			my_player.y += speed;
			break;
		case 'd':case 'D':
			my_player.x += speed;
			break;
		default:
			break;
		}
	}
#elif 1
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
		if (my_player.y >= speed)
			my_player.y -= speed;
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
		if (my_player.x >= speed - 40)
			my_player.x -= speed;
	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
		if (my_player.y <= height - 123)
			my_player.y += speed;
	if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
		if (my_player.x <= width - 55)
			my_player.x += speed;
#endif
	if (shoot_mode == 0) {
		if (GetAsyncKeyState(VK_SPACE) && timer(200, 1)) {
			createBullet();
		}
	}
	else if (shoot_mode == 1) {
		if (GetAsyncKeyState(VK_SPACE) && timer(50, 2)) {
			createBullet();
			shoot_mode1_time++;
			if (shoot_mode1_time > 75) {
				shoot_mode = 0;
				shoot_mode1_time = 0;
			}
		}
	}
	else {
		if (timer(8, 3)) {
			createBullet();
			shoot_mode2_time++;
			if (shoot_mode2_time > 300) {
				shoot_mode = 0;
				shoot_mode2_time = 0;
			}
		}
	}
	//�����ƶ�
	if (level == 1) {
		bk_h1 += 0.02;
		if (bk_h1 >= 0)
			bk_h1 = height - 700;
	}
	if (level == 2) {
		bk_h2 += 0.04;
		if (bk_h2 >= 0)
			bk_h2 = height - 1026;
	}
	if (level == 3) {
		bk_h3 += 0.02;
		if (bk_h3 >= 0)
			bk_h3 = height - 717;
	}

}
void bullet_move() {
	for (int i = 0; i < bullet_num; i++) {
		if (bull[i].islive) {
			if (bull[i].enemy_mark == 0) {
				bull[i].y -= 0.5;
				if (shoot_mode == 1) {
					if (i % 3 == 0)
						bull[i].x -= 0.2;
					if (i % 3 == 2)
						bull[i].x += 0.2;
				}
			}
			else if (bull[i].enemy_mark == 1)
				bull[i].y += 0.3;
			else if (bull[i].enemy_mark == 2) {
				bull[i].y += 0.2;
				if (i % 3 == 0)
					bull[i].x -= 0.1;
				if (i % 3 == 2)
					bull[i].x += 0.1;
			}
			else if (bull[i].enemy_mark == 3) {
				bull[i].y += bull[i].vy;
				bull[i].x += bull[i].vx;
			}
			if ((bull[i].enemy_mark == 0 && bull[i].y < 0) || (bull[i].enemy_mark == 1 && bull[i].y > height) ||
				((bull[i].enemy_mark == 2 || bull[i].enemy_mark == 3) &&
					(bull[i].y<0 || bull[i].y>height || bull[i].x<0 || bull[i].x>width))) {
				bull[i].islive = 0;
				bull[i].enemy_mark = 0;
			}
		}
	}
}
void enemy_move() {
	for (int i = 0; i < enemy_num; i++) {
		if (enemy[i].islive) {
			if (enemy[i].type == 0)
				enemy[i].y += 0.08;
			if (enemy[i].type == 1)
				enemy[i].y += 0.05;
			if (enemy[i].type == 2)
				enemy[i].y += 0.03;
			if (enemy[i].y > height) {
				enemy[i].islive = 0;
				my_player.blood -= enemy[i].type + 5;
			}
		}
	}
	if (boss.islive) {
		boss.y += 0.01;
	}
}
void supply_move() {
	for (int i = 0; i < supply_num; i++) {
		if (supply[i].islive) {
			supply[i].y += 0.02;
			if (supply[i].y > height) {
				supply[i].islive = 0;
			}
		}
	}
}
void hit_enemy() {
	for (int i = 0; i < enemy_num; i++) {
		if (!enemy[i].islive)
			continue;
		for (int j = 0; j < bullet_num; j++) {
			if (!bull[j].islive)
				continue;
			if (enemy[i].type == 0) {
				if (bull[j].x > enemy[i].x && bull[j].x<enemy[i].x + 49 &&
					bull[j].y>enemy[i].y && bull[j].y < enemy[i].y + 35) {
					enemy[i].blood--;
					bull[j].islive = 0;
				}
			}
			else if (enemy[i].type == 1) {
				if (bull[j].x > enemy[i].x && bull[j].x<enemy[i].x + 61 &&
					bull[j].y>enemy[i].y && bull[j].y < enemy[i].y + 51) {
					enemy[i].blood--;
					bull[j].islive = 0;
				}
			}
			else {
				if (bull[j].x > enemy[i].x && bull[j].x<enemy[i].x + 69 &&
					bull[j].y>enemy[i].y && bull[j].y < enemy[i].y + 88) {
					enemy[i].blood--;
					bull[j].islive = 0;
				}
			}
		}
		if (enemy[i].blood <= 0) {
			enemy[i].islive = 0;
			if (rand() % 4 == 0) {
				createSupply(enemy[i].x, enemy[i].y);
			}
			score += enemy[i].type + 1;
		}

	}
}
//����boss
void hit_boss() {
	if (boss.islive) {
		for (int j = 0; j < bullet_num; j++) {
			if (!bull[j].islive)
				continue;
			if (bull[j].x > boss.x && bull[j].x<boss.x + boss.enemy_width &&
				bull[j].y>boss.y && bull[j].y < boss.y + boss.enemy_height) {
				boss.blood--;
				bull[j].islive = 0;
			}
		}
		if (boss.blood <= 0) {
			boss.islive = 0;
			win = 1;
		}
	}
}
//���л�����
void get_hurt() {
	for (int j = 0; j < bullet_num; j++) {
		if (!bull[j].islive)
			continue;
		if (bull[j].enemy_mark == 1 || bull[j].enemy_mark == 2) {
			if (bull[j].x > my_player.x && bull[j].x<my_player.x + my_player.enemy_width &&
				bull[j].y>my_player.y && bull[j].y < my_player.y + my_player.enemy_height) {
				if (bull[j].enemy_mark)
					my_player.blood -= 3;
				if (bull[j].enemy_mark == 2)
					my_player.blood -= 1;
				bull[j].islive = 0;
				bull[j].enemy_mark = 0;
			}
		}
	}
}
//��õ���
void get_supply() {
	for (int i = 0; i < supply_num; i++) {
		if (supply[i].islive) {
			if (my_player.x + my_player.enemy_width > supply[i].x && my_player.x<supply[i].x + supply[i].enemy_width &&
				my_player.y + my_player.enemy_height > supply[i].y && my_player.y < supply[i].y + supply[i].enemy_height) {
				if (supply[i].type == 0)
					my_player.blood += 4;
				if (supply[i].type == 1) {
					shoot_mode = 1;
				}
				if (supply[i].type == 2) {
					shoot_mode = 2;
				}
				supply[i].islive = 0;
			}
		}
	}
}
//��л���ײ
void crash() {
	for (int i = 0; i < enemy_num; i++) {
		if (enemy[i].islive) {
			if (my_player.x + my_player.enemy_width > enemy[i].x && my_player.x<enemy[i].x + enemy[i].enemy_width &&
				my_player.y + my_player.enemy_height > enemy[i].y && my_player.y < enemy[i].y + enemy[i].enemy_height) {
				if (enemy[i].type == 0)
					my_player.blood -= 5;
				if (enemy[i].type == 1)
					my_player.blood -= 10;
				if (enemy[i].type == 2)
					my_player.blood = 0;
				enemy[i].islive = 0;
			}
		}
	}
	if (boss.islive) {
		if (my_player.x + my_player.enemy_width > boss.x && my_player.x<boss.x + boss.enemy_width &&
			my_player.y + my_player.enemy_height > boss.y && my_player.y < boss.y + boss.enemy_height) {
			my_player.blood = 0;
			boss.islive = 0;
		}
	}
}
void level2() {
	level = 2;
	/*settextcolor(RED);
	settextstyle(40, 0, "��������");
	setbkmode(TRANSPARENT);
	cleardevice();
	outtextxy(width / 2 - 150, height / 2, "LEVEL 2");
	Sleep(2000);
	/*while (1) {
		if (timer(1000, 4))
			break;
	}*/
	settextcolor(WHITE);
	settextstyle(20, 0, "ARLRDBD");
	setbkmode(TRANSPARENT);
	for (int i = 0; i < enemy_num; i++) {
		if (enemy[i].islive && enemy[i].type == 2) {
			if (timer(800, 3)) {
				createEnemyBullet(enemy[i].x + enemy[i].enemy_width / 2, enemy[i].y + enemy[i].enemy_height);
			}
		}
	}
}
void level3() {
	settextcolor(BLUE);
	settextstyle(20, 0, "����");
	setbkmode(TRANSPARENT);
	//level2();
	level = 3;
	if (score > 100) {
		boss.islive = 1;
		if (timer(800, 4))
			createBossBullet(boss.x + boss.enemy_width / 2, boss.y + boss.enemy_height);
		if (score > 130) {
			if (timer(1000, 5))
				createBossBullet2(boss.x + boss.enemy_width / 2, boss.y + boss.enemy_height);
		}
	}
}
int main()
{
	initgraph(width, height, SHOWCONSOLE);
	settextcolor(RED);
	settextstyle(40, 0, "��������");
	setbkmode(TRANSPARENT);
	BeginBatchDraw();
	putimage(0, 0, &bk);
	EndBatchDraw();
	outtextxy(width / 2 - 150, height / 2, "the plane war");
	Sleep(2000);
	plane_init();
	//˫�����ͼ
	BeginBatchDraw();
	while (1) {
		draw();
		FlushBatchDraw();
		plane_move(0.3);
		bullet_move();
		supply_move();
		if (timer(800, 0))
			create_enemy();
		enemy_move();
		hit_enemy();
		hit_boss();
		get_supply();
		crash();
		get_hurt();
		/*if (win == 1)
			break;
		if (my_player.blood <= 0)
			break;*/
		if (score >= 50 && score < 110) {
			level2();
		}
		if (score >= 110)
			level3();
	}
	EndBatchDraw();
	cleardevice();
	putimage(0, 0, &bk);
	settextcolor(RED);
	settextstyle(40, 0, "��������");
	setbkmode(TRANSPARENT);
	if (win == 1)
		outtextxy(width / 2 - 110, height / 2, "YOU WIN!");
	else
		outtextxy(width / 2 - 110, height / 2, "GAME OVER");
	Sleep(2000);
	return 0;
}

