#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#pragma comment(lib,"Winmm.lib")
#include<time.h>
#include<Windows.h>
#include <mmsystem.h>
#define bullet_num 3000
#define enemy_num 20
#define supply_num 20
int height = 600, width = 470;
int score=0;
int shoot_mode = 0;
int shoot_mode1_time = 0;
int shoot_mode2_time = 0;
int level = 1;
int level_flag1 = 0, level_flag2 = 0;
int win = 0;
double bk_h1 = 700-height, bk_h2 = 1026-height, bk_h3 = 717-height;
int sound_upgrade2 = 0, sound_upgrade3 = 0;
int down1, down2;
struct plane {
	double x;
	double y;
	int islive;
	int enemy_width;
	int enemy_height;
	double blood;//血量
	int type;//敌机类型
	int enemy_mark;
	double vx, vy;
}my_player,bull[bullet_num],enemy[enemy_num],supply[supply_num],boss;


IMAGE bk,bk1,bk2,bk3;
IMAGE img_player[2];
IMAGE img_bull[2];
IMAGE img_enemy[5][2];
IMAGE img_enemy_down[4][2];
IMAGE img_supply[3][2];
IMAGE img_blood[3][2];
//加载图片
void loadImg() {
	//加载背景图片
	loadimage(&bk, "./images/background.png");
	loadimage(&bk1, "./images/bk4.jpg");
	loadimage(&bk2, "./images/bk.jpg");
	loadimage(&bk3, "./images/bk5.jpg");
	loadimage(&img_player[0], "./images/me02.png");
	loadimage(&img_player[1], "./images/me01.png");
	loadimage(&img_bull[0], "./images/BULLET.1.png");
	loadimage(&img_bull[1], "./images/bullet1.png");
	loadimage(&img_blood[0][0], "./images/blood002.png");
	loadimage(&img_blood[0][1], "./images/blood001.png");
	loadimage(&img_blood[1][0], "./images/blood003.png");
	loadimage(&img_blood[1][1], "./images/blood004.png");
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
	loadimage(&img_enemy_down[0][0], "./images/endown.2.png");
	loadimage(&img_enemy_down[0][1], "./images/endown.1.png");
}
//游戏初始化
void plane_init() {
	settextcolor(RED);
	settextstyle(15, 0, "华文琥珀");
	setbkmode(TRANSPARENT);
	my_player.x = width / 2 - 49;
	my_player.y = height - 123;
	my_player.enemy_width = 102;
	my_player.enemy_height = 126;
	my_player.islive = 1;
	my_player.blood = 20;
	loadImg();
	//初始化子弹
	for (int i = 0; i < bullet_num; i++) {
		bull[i].islive = 0;
		bull[i].x = 0;
		bull[i].y = 0;
		bull[i].enemy_mark = 0;
		bull[i].vx = 0;
		bull[i].vy = 0;
	}
	//初始化敌机
	for (int i = 0; i < enemy_num; i++) {
		enemy[i].islive = 0;
		if (i==0) {
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
	//初始化道具
	for (int i = 0; i < supply_num; i++) {
		supply[i].islive = 0;
		supply[i].x = 0;
		supply[i].y = 0;		
	}
	//初始化boss
	boss.islive = 0;
	boss.blood = 300;
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
			if (shoot_mode == 0) {
				mciSendString("open ./sound/bullet.wav alias BGM3", NULL, 0, NULL);
				mciSendString("play BGM3", NULL, 0, NULL);
				mciSendString("close BGM3", NULL, 0, NULL);
			}
			break;
		}
	}
}
void createEnemyBullet(double x,double y) {
	for (int i = 0; i < bullet_num; i++) {
		if (!bull[i].islive) {
			bull[i].islive = 1;
			bull[i].x = x;
			bull[i].y = y;
			mciSendString("open ./sound/bullet.wav alias BGM3", NULL, 0, NULL);
			mciSendString("play BGM3", NULL, 0, NULL);
			mciSendString("close BGM3", NULL, 0, NULL);
			bull[i].enemy_mark = 1;
			break;
		}
	}
}
void createBossBullet(double x,double y) {
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
//产生敌机
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
//产生道具
void createSupply(double x,double y) {
	for (int i = 0; i < supply_num; i++) {
		if (!supply[i].islive) {
			supply[i].islive = 1;
			supply[i].x = x;
			supply[i].y = y;
			if (rand()%5 == 0) {
				supply[i].type = 1;
				supply[i].enemy_width = 58;
				supply[i].enemy_height = 103;
			}
			else if (rand()%5 == 3) {
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
	outtextxy(x,y, n);
}
//绘制界面
void draw() {
	if (level == 1)
	putimage(0, bk_h1, &bk1);
	if (level == 2)
		putimage(0,bk_h2, &bk2);
	if (level == 3)
		putimage(0, bk_h3, &bk3);
	putimage(my_player.x, my_player.y, &img_player[0], NOTSRCERASE);
	putimage(my_player.x, my_player.y, &img_player[1], SRCINVERT);
	//绘制boss
	if (boss.islive == 1) {
		putimage(boss.x, boss.y, &img_enemy[3][0], NOTSRCERASE);
		putimage(boss.x, boss.y, &img_enemy[3][1], SRCINVERT);
		putimage(boss.x, boss.y-10, 215 * 0.6 *boss.blood / 30, 10, &img_blood[1][0], 0, 0, NOTSRCERASE);
		putimage(boss.x, boss.y-10, 215 * 0.6 * boss.blood / 30, 10, &img_blood[1][1], 0, 0, SRCINVERT);
	}
	//绘制敌机
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
	//绘制道具
	for (int i = 0; i < supply_num; i++) {
		if (supply[i].islive) {
			if (supply[i].type == 0) {
				putimage(supply[i].x, supply[i].y, &img_supply[0][0], NOTSRCERASE);
				putimage(supply[i].x, supply[i].y, &img_supply[0][1], SRCINVERT);
			}
			else if(supply[i].type==1) {
				putimage(supply[i].x, supply[i].y, &img_supply[1][0], NOTSRCERASE);
				putimage(supply[i].x, supply[i].y, &img_supply[1][1], SRCINVERT);
			}
			else if (supply[i].type == 2) {
				putimage(supply[i].x, supply[i].y, &img_supply[2][0], NOTSRCERASE);
				putimage(supply[i].x, supply[i].y, &img_supply[2][1], SRCINVERT);
			}
		}
	}
	//绘制子弹
	for (int i = 0; i < bullet_num; i++) {
		if (bull[i].islive) {
			putimage(bull[i].x, bull[i].y, &img_bull[0], NOTSRCERASE);
			putimage(bull[i].x, bull[i].y, &img_bull[1], SRCINVERT);
		}
	}
	//实时血条
	putimage(width-100, 20, 215*0.6*my_player.blood/20,10,&img_blood[0][0], 0, 0, NOTSRCERASE);
	putimage(width - 100, 20, 215 * 0.6 * my_player.blood / 20, 10, &img_blood[0][1], 0, 0, SRCINVERT);
	if(level==1)
		settextcolor(BLUE);
	else
		settextcolor(RED);
	settextstyle(20, 0, "Berlin Sans FB Demi");
	setbkmode(TRANSPARENT);
	outtextxy(width - 100, 40, "score:");
	write_num(width - 50, 40, score);
	outtextxy(width - 180, 20, "blood:");
	write_num(width - 130, 20, my_player.blood);
	if(level==2||level==3)
	settextcolor(WHITE);
	else
	settextcolor(BLUE);
	settextstyle(20, 0, "ALGERIAN");
	setbkmode(TRANSPARENT);
	outtextxy(40, 20, "level:");
	write_num(110, 20, level);
}

//定时器
bool timer(int ms,int id) {
	static DWORD t[10];
	if (clock() - t[id] > ms) {
		t[id] = clock();
		return true;
	}
	return false;
}
void plane_move(double speed) {
#if 0
	//检测是否有键盘输入
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
	if(GetAsyncKeyState(VK_UP)||GetAsyncKeyState('W'))
		if(my_player.y>=speed)
		my_player.y -= speed;
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
		if(my_player.x>=speed-40)
		my_player.x -= speed;
	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
		if(my_player.y<=height-123)
		my_player.y += speed;
	if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
		if(my_player.x<=width-55)
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
	else{
			if (timer(8, 3)) {
				createBullet();
				shoot_mode2_time++;
				if (shoot_mode2_time > 300) {
					shoot_mode = 0;
					shoot_mode2_time = 0;
				}
			}
	}
	//背景移动
	if (level == 1) {
		bk_h1+=0.04;
		if (bk_h1 >=0)
			bk_h1 = height-1026;
	}
	if (level == 2) {
		bk_h2+=0.02;
		if (bk_h2 >=0)
			bk_h2 = height-717;
	}
	if (level == 3) {
		bk_h3+=0.02;
		if (bk_h3 >=0)
			bk_h3 =height-717;
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
			else if(bull[i].enemy_mark==1)
				bull[i].y+=0.3;
			else if(bull[i].enemy_mark==2) {
				bull[i].y += 0.2;
				if (i%3== 0)
					bull[i].x -= 0.1;
				if (i%3 == 2)
					bull[i].x += 0.1;
			}
			else if(bull[i].enemy_mark==3) {
				bull[i].y += bull[i].vy;
				bull[i].x += bull[i].vx;
			}
			if ((bull[i].enemy_mark == 0&&bull[i].y < 0)|| (bull[i].enemy_mark == 1 && bull[i].y >height)||
				((bull[i].enemy_mark==2||bull[i].enemy_mark==3)&&
					(bull[i].y<0||bull[i].y>height||bull[i].x<0||bull[i].x>width))) {
				bull[i].islive = 0;
				bull[i].enemy_mark = 0;
			}
		}
	}
}
void enemy_move() {
	for (int i = 0; i < enemy_num; i++) {
		if (enemy[i].islive) {
			if(enemy[i].type==0)
			enemy[i].y+=0.08;
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
					bull[j].islive=0;
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
			putimage(enemy[i].x, enemy[i].y, &img_enemy_down[0][0], NOTSRCERASE);
			putimage(enemy[i].x, enemy[i].y, &img_enemy_down[0][1], SRCINVERT);
			mciSendString("close BGM2", NULL, 0, NULL);
			mciSendString("open enemy1_down.wav alias BGM2", NULL, 0, NULL);
			mciSendString("play BGM2", NULL, 0, NULL);
			if (rand() % 4 == 0) {
				createSupply(enemy[i].x,enemy[i].y);
			}
			score += enemy[i].type + 1;
		}

	}
}
//击中boss
void hit_boss() {
	if (boss.islive) {
		for (int j = 0; j < bullet_num; j++) {
			if (!bull[j].islive)
				continue;
				if (bull[j].x > boss.x && bull[j].x<boss.x + boss.enemy_width &&
					bull[j].y>boss.y && bull[j].y < boss.y +boss.enemy_height) {
					boss.blood--;
					bull[j].islive = 0;
				}			
		}
		if (boss.blood <= 0) {
			mciSendString("open ./sound/enemy3_down.wav alias BGM4", NULL, 0, NULL);
			mciSendString("play BGM4", NULL, 0, NULL);
			mciSendString("close BGM4a", NULL, 0, NULL);
			boss.islive = 0;
			win = 1;
		}
	}
}
//被敌机击中
void get_hurt() {
	for (int j = 0; j < bullet_num; j++) {
		if (!bull[j].islive)
			continue;
		if (bull[j].enemy_mark==1|| bull[j].enemy_mark == 2||bull[j].enemy_mark==3) {
			if (bull[j].x > my_player.x && bull[j].x<my_player.x +my_player.enemy_width &&
				bull[j].y>my_player.y && bull[j].y < my_player.y + my_player.enemy_height) {
				//if(bull[j].enemy_mark)
				my_player.blood-=1;
				//if (bull[j].enemy_mark == 2)
					//my_player.blood -= 1;
				bull[j].islive = 0;
				bull[j].enemy_mark = 0;
			}
		}
	}
}
//获得道具
void get_supply() {
	for (int i = 0; i < supply_num; i++) {
		if (supply[i].islive) {
			if (my_player.x + my_player.enemy_width > supply[i].x && my_player.x<supply[i].x + supply[i].enemy_width &&
				my_player.y + my_player.enemy_height > supply[i].y && my_player.y < supply[i].y + supply[i].enemy_height){
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
//与敌机相撞
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
					my_player.blood =0;
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
	settextstyle(40, 0, "华文琥珀");
	setbkmode(TRANSPARENT);
	cleardevice();
	outtextxy(width / 2 - 150, height / 2, "LEVEL 2");
	Sleep(2000);
	/*while (1) {
		if (timer(1000, 4))
			break;
	}*/
	settextcolor(WHITE);
	settextstyle(30, 0, "Berlin Sans FB");
	setbkmode(TRANSPARENT);
	for (int i = 0; i < enemy_num; i++) {
		if (enemy[i].islive&&enemy[i].type==2) {
			if (timer(800, 3)) {
				createEnemyBullet(enemy[i].x+enemy[i].enemy_width/2,enemy[i].y+enemy[i].enemy_height);
			}
		}
	}
}
void level3() {
	settextcolor(BLUE);
	settextstyle(30, 0, "Berlin Sans FB");
	setbkmode(TRANSPARENT);
	//level2();
	level = 3;
	if (score > 100) {
		boss.islive = 1;
		if (timer(800, 4))
			createBossBullet(boss.x + boss.enemy_width / 2, boss.y + boss.enemy_height);
		if (score > 130) {
			if(timer(1000,5))
			createBossBullet2(boss.x + boss.enemy_width / 2, boss.y + boss.enemy_height);
		}
	}
}
int main()
{
	initgraph(width, height,SHOWCONSOLE);
	//mciSendString("close BGM1", NULL, 0, NULL);
	mciSendString("open background.mp3 alias BGM1", NULL, 0, NULL);
	mciSendString("play background.mp3 repeat", NULL , 0,NULL);
	mciSendString("close BGM1", NULL, 0, NULL);
	mciSendString("open enemy1_down.wav alias BGM2", NULL, 0, NULL);
	mciSendString("play BGM2", NULL, 0, NULL);

	cleardevice();
	loadImg();
	putimage(0, 0, &bk);
	settextcolor(BLUE);
	settextstyle(40, 0, "ALGERIAN");
	setbkmode(TRANSPARENT);
	outtextxy(width/2-150, height/2, "the plane war");
	settextstyle(20, 0, "ALGERIAN");
	outtextxy(width / 2 - 80, height / 2+50, "M.I.  2.3.0");
	Sleep(2000);
	plane_init();
	//双缓冲绘图
	BeginBatchDraw();
	while (1) {
	draw();
 	FlushBatchDraw();
	plane_move(0.3);
	bullet_move();
	supply_move();
	if(timer(800,0))
		create_enemy();
	enemy_move();
	hit_enemy();
	hit_boss();
	get_supply();
	crash();
	get_hurt();
	if (win == 1)
		break;
	if (my_player.blood <= 0)		
		break;
	if (score >= 50&&score<110) {
		if (sound_upgrade2 == 0) {
			int t = 3;
			while (t--) {
				mciSendString("open ./sound/upgrade.wav alias upgrade", NULL, 0, NULL);
				mciSendString("play upgrade", NULL, 0, NULL);
				mciSendString("close upgrade", NULL, 0, NULL);
			}
			sound_upgrade2 = 1;
		}
		level2();
	}
	if (score >= 110) {
		if (sound_upgrade3 == 0) {
			int t = 3;
			while (t--) {
				mciSendString("open ./sound/upgrade.wav alias upgrade", NULL, 0, NULL);
				mciSendString("play upgrade", NULL, 0, NULL);
				mciSendString("close upgrade", NULL, 0, NULL);
			}
			sound_upgrade3 = 1;
		}
		level3();
	}
	}
	EndBatchDraw();
	cleardevice();
	putimage(0, 0, &bk);
		settextcolor(BLUE);
		settextstyle(40, 0, "ALGERIAN");
		setbkmode(TRANSPARENT);
		if(win==1)
		outtextxy(width / 2 - 110, height / 2, "YOU WIN!");
		else
		outtextxy(width / 2 - 110, height / 2, "GAME OVER");
		Sleep(2000);
	return 0;
}

