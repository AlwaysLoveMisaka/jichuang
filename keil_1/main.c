#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "code_def.h"
//uint16_t x=0,y=0;
//uint8_t dx=20,dy=20;

uint16_t i_time,count=0;
uint16_t score,falltime;
uint8_t mode,level;
uint8_t State[25][13]=
{
	{1,0,0,0,0,0,0,0,0,0,0,0,1},//1
	{1,0,0,0,0,0,0,0,0,0,0,0,1},//2
	{1,0,0,0,0,0,0,0,0,0,0,0,1},//3
	{1,0,0,0,0,0,0,0,0,0,0,0,1},//4
	{1,0,0,0,0,0,0,0,0,0,0,0,1},//5
	{1,0,0,0,0,0,0,0,0,0,0,0,1},//6
	{1,0,0,0,0,0,0,0,0,0,0,0,1},//7
	{1,0,0,0,0,0,0,0,0,0,0,0,1},//8
	{1,0,0,0,0,0,0,0,0,0,0,0,1},//9
	{1,0,0,0,0,0,0,0,0,0,0,0,1},//10
	{1,0,0,0,0,0,0,0,0,0,0,0,1},//11
	{1,0,0,0,0,0,0,0,0,0,0,0,1},//12
	{1,0,0,0,0,0,0,0,0,0,0,0,1},//13
	{1,0,0,0,0,0,0,0,0,0,0,0,1},//14
	{1,0,0,0,0,0,0,0,0,0,0,0,1},//15
	{1,0,0,0,0,0,0,0,0,0,0,0,1},//16
	{1,0,0,0,0,0,0,0,0,0,0,0,1},//17
	{1,0,0,0,0,0,0,0,0,0,0,0,1},//18
	{1,0,0,0,0,0,0,0,0,0,0,0,1},//19
	{1,0,0,0,0,0,0,0,0,0,0,0,1},//20
	{1,0,0,0,0,0,0,0,0,0,0,0,1},//21
	{1,0,0,0,0,0,0,0,0,0,0,0,1},//22
	{1,0,0,0,0,0,0,0,0,0,0,0,1},//23
	{1,0,0,0,0,0,0,0,0,0,0,0,1},//24
	{1,1,1,1,1,1,1,1,1,1,1,1,1},//25
};  //设定屏幕方格的状态

uint8_t Color[24][11]=
{
	{0,0,0,0,0,0,0,0,0,0,0},//1
	{0,0,0,0,0,0,0,0,0,0,0},//2
	{0,0,0,0,0,0,0,0,0,0,0},//3
	{0,0,0,0,0,0,0,0,0,0,0},//4
	{0,0,0,0,0,0,0,0,0,0,0},//5
	{0,0,0,0,0,0,0,0,0,0,0},//6
	{0,0,0,0,0,0,0,0,0,0,0},//7
	{0,0,0,0,0,0,0,0,0,0,0},//8
	{0,0,0,0,0,0,0,0,0,0,0},//9
	{0,0,0,0,0,0,0,0,0,0,0},//10
	{0,0,0,0,0,0,0,0,0,0,0},//11
	{0,0,0,0,0,0,0,0,0,0,0},//12
	{0,0,0,0,0,0,0,0,0,0,0},//13
	{0,0,0,0,0,0,0,0,0,0,0},//14
	{0,0,0,0,0,0,0,0,0,0,0},//15
	{0,0,0,0,0,0,0,0,0,0,0},//16
	{0,0,0,0,0,0,0,0,0,0,0},//17
	{0,0,0,0,0,0,0,0,0,0,0},//18
	{0,0,0,0,0,0,0,0,0,0,0},//19
	{0,0,0,0,0,0,0,0,0,0,0},//20
	{0,0,0,0,0,0,0,0,0,0,0},//21
	{0,0,0,0,0,0,0,0,0,0,0},//22
	{0,0,0,0,0,0,0,0,0,0,0},//23
	{0,0,0,0,0,0,0,0,0,0,0},//24
};  //设定屏幕方格的色彩

uint16_t SelectColor(uint8_t what){
	uint16_t color;
	switch(what){
		case 1: color=YELLOW; break; //正方形
		case 2: case 3: color=BROWN; break; //长条
		case 4: case 5: case 6: case 7: color=BRED; break; //1+3
		case 8: case 9: case 10: case 11: color=BLUE; break; //倒L
		case 12: case 13: case 14: case 15: color=CYAN; break; //L
		case 16: case 17: color=GREEN; break; //梯形
		case 18: case 19: color=BRRED; break; //倒梯形
		case 20: case 21: case 22: color=RED; break; //炸弹
	}
	return color;
}  //颜色选择

void StateInit()
{
	uint8_t i,j;
	if(mode==1||mode==3||mode==4){
		for(i=0;i<24;i++){
			for(j=1;j<12;j++){
				State[i][j]=0;
			}
		}
		for(i=0;i<25;i++){
			State[i][0]=1;
			State[i][12]=1;
		}
		for(j=0;j<13;j++){
			State[24][j]=1;
		}
	}
	else if(mode==2){	
		for(i=0;i<19;i++){
			for(j=1;j<12;j++){
	      State[i][j]=0;
			}
		}
		for(i=19;i<24;i++){
			for(j=1;j<12;j++){
	      if(rand()%100>=50){
					State[i][j]=0;
				}
				else{
					State[i][j]=1;
				}
			}
		}
		for(i=0;i<25;i++){
			State[i][0]=1;
			State[i][12]=1;
		}
		for(j=0;j<13;j++){
			State[24][j]=1;
		}
	}
}  //模式设定

void DrawBox(uint16_t x,uint16_t y, uint8_t what)
{
	//480x320   24x11   480x220     20	
	POINT_COLOR=BLACK;
	
	if(mode==4 && x>19 && what<100){
		Color[x-1][y-1]=what;
		LCD_Fill(13*y-12, 13*x-12, 13*y-1, 13*x-1, GRAY);
	}
	else if(mode==4 && x>19 && what>=100){
		if(what>100){
			Color[x-1][y-1]=what-100;
			LCD_Fill(13*y-12, 13*x-12, 13*y-1, 13*x-1, SelectColor(what-100));
		}
		else if(what==100){
			Color[x-1][y-1]=0;
			LCD_Fill(13*y-13, 13*x-13, 13*y, 13*x, WHITE);
		}
	}
	else if(what==0){
		Color[x-1][y-1]=rand()%19+1;
		LCD_Fill(13*y-12, 13*x-12, 13*y-1, 13*x-1, SelectColor(Color[x-1][y-1]));
	}
	else{
		Color[x-1][y-1]=what;
		LCD_Fill(13*y-12, 13*x-12, 13*y-1, 13*x-1, SelectColor(what));
	}
  LCD_DrawRectangle(13*y-12, 13*x-12, 13*y-1, 13*x-1);
}  //填色函数


void DeleteBox(uint16_t x,uint16_t y)
{
	//480x320   24x11   480x220     20	
	if(mode==4 && x>19){
		DrawBox(x,y,Color[x-1][y-1]);
		Color[x-1][y-1]=0;
	}
	else{
	  LCD_Fill(13*y-12, 13*x-12, 13*y-1, 13*x-1, WHITE);
	  Color[x-1][y-1]=0;
	}
}  //删除函数


void DrawPic(uint16_t x,uint16_t y,uint8_t what)
{
	//左上角为原点
	switch (what)
	{
		case 1:   //正方形
		{
		DrawBox(x,y,what);
		DrawBox(x+1,y,what);
		DrawBox(x,y+1,what);
		DrawBox(x+1,y+1,what);
		}
		break;
		
		case 2:   //长条 竖
		{
		DrawBox(x,y,what);
		DrawBox(x+1,y,what);
	  DrawBox(x+2,y,what);
		DrawBox(x+3,y,what);
		}
		break;
		
		case 3:   //长条 横
		{
		DrawBox(x,y,what);
		DrawBox(x,y+1,what);
		DrawBox(x,y+2,what);
		DrawBox(x,y+3,what);
		}
		break;
		
		case 4:   //1+3 向左
		{
		DrawBox(x+1,y,what);
		DrawBox(x,y+1,what);
		DrawBox(x+1,y+1,what);
		DrawBox(x+2,y+1,what);
		}
		break;
		
		case 5:   //1+3 向下 逆时针
		{
		DrawBox(x+1,y+1,what);
		DrawBox(x,y,what);
		DrawBox(x,y+1,what);
		DrawBox(x,y+2,what);
		}
		break;

		case 6:   //1+3 向上
		{
		DrawBox(x,y+1,what);
		DrawBox(x+1,y,what);
		DrawBox(x+1,y+1,what);
		DrawBox(x+1,y+2,what);
		}
		break;
		
		case 7:   //1+3 向右
		{
		DrawBox(x+1,y+1,what);
		DrawBox(x,y,what);
		DrawBox(x+1,y,what);
		DrawBox(x+2,y,what);
		}
		break;
	
		case 8:   // 倒L形态1
		{
		DrawBox(x,y,what);
		DrawBox(x,y+1,what);
		DrawBox(x,y+2,what);
		DrawBox(x+1,y+2,what);
		}
		break;
		
		case 9:   // 倒L形态2 逆时针
		{
		DrawBox(x,y,what);
		DrawBox(x,y+1,what);
		DrawBox(x+1,y,what);
		DrawBox(x+2,y,what);
		}
		break;
		
		case 10:   // 倒L形态3
		{
		DrawBox(x,y,what);
		DrawBox(x+1,y,what);
		DrawBox(x+1,y+1,what);
		DrawBox(x+1,y+2,what);
		}
		break;
		
		case 11:   // 倒L形态4
		{
		DrawBox(x,y+1,what);
		DrawBox(x+1,y+1,what);
		DrawBox(x+2,y+1,what);
		DrawBox(x+2,y,what);
		}
		break;
		
		case 12:   // L形态1
		{
		DrawBox(x+1,y,what);
		DrawBox(x+1,y+1,what);
		DrawBox(x+1,y+2,what);
		DrawBox(x,y+2,what);
		}
		break;
		
		case 13:   // L形态2
		{
		DrawBox(x,y,what);
		DrawBox(x+1,y,what);
		DrawBox(x+2,y,what);
		DrawBox(x+2,y+1,what);
		}
		break;
		
		case 14:   // L形态3
		{
		DrawBox(x,y,what);
		DrawBox(x+1,y,what);
		DrawBox(x,y+1,what);
		DrawBox(x,y+2,what);
		}
		break;
		
		case 15:   // L形态4
		{
		DrawBox(x,y,what);
		DrawBox(x,y+1,what);
		DrawBox(x+1,y+1,what);
		DrawBox(x+2,y+1,what);
		}
		break;
		
		
		case 16:   //梯形 横
		{
		DrawBox(x+1,y,what);
		DrawBox(x+1,y+1,what);
		DrawBox(x,y+1,what);
		DrawBox(x,y+2,what);
		}
		break;
		
		case 17:   //梯形 竖
		{
		DrawBox(x,y,what);
		DrawBox(x+1,y,what);
		DrawBox(x+1,y+1,what);
		DrawBox(x+2,y+1,what);
		}
		break;
		
		case 18:   //反梯形 横
		{
		DrawBox(x,y,what);
		DrawBox(x,y+1,what);
		DrawBox(x+1,y+1,what);
		DrawBox(x+1,y+2,what);
		}
		break;
		
		case 19:   //反梯形 竖
		{
		DrawBox(x,y+1,what);
		DrawBox(x+1,y+1,what);
		DrawBox(x+1,y,what);
		DrawBox(x+2,y,what);
		}
		break;
		
		case 20: case 21: case 22:   //炸弹
		{
		DrawBox(x,y,what);
		}
		break;
	}
}  //画方块组合

void DeletePic(uint16_t x,uint16_t y,uint8_t what)
{
	//左上角为原点
	switch (what)
	{
		case 1:   //正方形
		{
		DeleteBox(x,y);
		DeleteBox(x+1,y);
		DeleteBox(x,y+1);
		DeleteBox(x+1,y+1);
		}
		break;
		
		case 2:   //长条 竖
		{
		DeleteBox(x,y);
		DeleteBox(x+1,y);
		DeleteBox(x+2,y);
		DeleteBox(x+3,y);
		}
		break;
		
		case 3:   //长条 横
		{
		DeleteBox(x,y);
		DeleteBox(x,y+1);
		DeleteBox(x,y+2);
		DeleteBox(x,y+3);
		}
		break;
		
		case 4:   //1+3 向左
		{
		DeleteBox(x+1,y);
		DeleteBox(x,y+1);
		DeleteBox(x+1,y+1);
		DeleteBox(x+2,y+1);
		}
		break;
		
		case 5:   //1+3 向下 逆时针
		{
		DeleteBox(x+1,y+1);
		DeleteBox(x,y);
		DeleteBox(x,y+1);
		DeleteBox(x,y+2);
		}
		break;

		case 6:   //1+3 向上
		{
		DeleteBox(x,y+1);
		DeleteBox(x+1,y);
		DeleteBox(x+1,y+1);
		DeleteBox(x+1,y+2);
		}
		break;
		
		case 7:   //1+3 向右
		{
		DeleteBox(x+1,y+1);
		DeleteBox(x,y);
		DeleteBox(x+1,y);
		DeleteBox(x+2,y);
		}
		break;
	
		case 8:   // 倒L形态1
		{
		DeleteBox(x,y);
		DeleteBox(x,y+1);
		DeleteBox(x,y+2);
		DeleteBox(x+1,y+2);
		}
		break;
		
		case 9:   // 倒L形态2 逆时针
		{
		DeleteBox(x,y);
		DeleteBox(x,y+1);
		DeleteBox(x+1,y);
		DeleteBox(x+2,y);
		}
		break;
		
		case 10:   // 倒L形态3
		{
		DeleteBox(x,y);
		DeleteBox(x+1,y);
		DeleteBox(x+1,y+1);
		DeleteBox(x+1,y+2);
		}
		break;
		
		case 11:   // 倒L形态4
		{
		DeleteBox(x,y+1);
		DeleteBox(x+1,y+1);
		DeleteBox(x+2,y+1);
		DeleteBox(x+2,y);
		}
		break;
		
		case 12:   // L形态1
		{
		DeleteBox(x+1,y);
		DeleteBox(x+1,y+1);
		DeleteBox(x+1,y+2);
		DeleteBox(x,y+2);
		}
		break;
		
		case 13:   // L形态2
		{
		DeleteBox(x,y);
		DeleteBox(x+1,y);
		DeleteBox(x+2,y);
		DeleteBox(x+2,y+1);
		}
		break;
		
		case 14:   // L形态3
		{
		DeleteBox(x,y);
		DeleteBox(x+1,y);
		DeleteBox(x,y+1);
		DeleteBox(x,y+2);
		}
		break;
		
		case 15:   // L形态4
		{
		DeleteBox(x,y);
		DeleteBox(x,y+1);
		DeleteBox(x+1,y+1);
		DeleteBox(x+2,y+1);
		}
		break;
		
		
		case 16:   //梯形 横
		{
		DeleteBox(x+1,y);
		DeleteBox(x+1,y+1);
		DeleteBox(x,y+1);
		DeleteBox(x,y+2);
		}
		break;
		
		case 17:   //梯形 竖
		{
		DeleteBox(x,y);
		DeleteBox(x+1,y);
		DeleteBox(x+1,y+1);
		DeleteBox(x+2,y+1);
		}
		break;
		
		case 18:   //反梯形 横
		{
		DeleteBox(x,y);
		DeleteBox(x,y+1);
		DeleteBox(x+1,y+1);
		DeleteBox(x+1,y+2);
		}
		break;
		
		case 19:   //反梯形 竖
		{
		DeleteBox(x,y+1);
		DeleteBox(x+1,y+1);
		DeleteBox(x+1,y);
		DeleteBox(x+2,y);
		}
		break;
		
		case 20: case 21: case 22:    //炸弹
		{
		DeleteBox(x,y);
		}
		break;
	}
}  //删方块组合

void MoveDown(uint16_t x,uint16_t y,uint8_t what)
{
	DeletePic(x,y,what);
	DrawPic(x+1,y,what);
}
void MoveLeft(uint16_t x,uint16_t y,uint8_t what)
{
	DeletePic(x,y,what);
	DrawPic(x,y-1,what);
}
void MoveRight(uint16_t x,uint16_t y,uint8_t what)
{
	DeletePic(x,y,what);
	DrawPic(x,y+1,what);
} //左移，右移，下移

void Change(uint16_t x,uint16_t y,uint8_t what)
{
	switch(what)
	{
		case 1:break;
		
		case 2:DeletePic(x,y,2);DrawPic(x,y,3);break;
		case 3:DeletePic(x,y,3);DrawPic(x,y,2);break;
		
		case 4:DeletePic(x,y,4);DrawPic(x,y,5);break;
		case 5:DeletePic(x,y,5);DrawPic(x,y,7);break;
		case 6:DeletePic(x,y,6);DrawPic(x,y,4);break;
		case 7:DeletePic(x,y,7);DrawPic(x,y,6);break;
		
		case 8:DeletePic(x,y,8);DrawPic(x,y,9);break;
		case 9:DeletePic(x,y,9);DrawPic(x,y,10);break;
		case 10:DeletePic(x,y,10);DrawPic(x,y,11);break;
		case 11:DeletePic(x,y,11);DrawPic(x,y,8);break;
			
		case 12:DeletePic(x,y,12);DrawPic(x,y,15);break;
		case 13:DeletePic(x,y,13);DrawPic(x,y,12);break;
		case 14:DeletePic(x,y,14);DrawPic(x,y,13);break;
		case 15:DeletePic(x,y,15);DrawPic(x,y,14);break;
		
		case 16:DeletePic(x,y,16);DrawPic(x,y,17);break;
		case 17:DeletePic(x,y,17);DrawPic(x,y,16);break;
		
		case 18:DeletePic(x,y,18);DrawPic(x,y,19);break;
		case 19:DeletePic(x,y,19);DrawPic(x,y,18);break;
		
		case 20:case 21:case 22:break;
	}
}  //对缓慢下落的模拟


uint8_t Change_w(uint8_t what)
{
	uint8_t w;
	switch(what)
	{
		case 1:break;
		
		case 2:w=3;break;
		case 3:w=2;break;
		
		case 4:w=5;break;
		case 5:w=7;break;
		case 6:w=4;break;
		case 7:w=6;break;
		
		case 8:w=9;break;
		case 9:w=10;break;
		case 10:w=11;break;
		case 11:w=8;break;
			
		case 12:w=15;break;
		case 13:w=12;break;
		case 14:w=13;break;
		case 15:w=14;break;
		
		case 16:w=17;break;
		case 17:w=16;break;
		
		case 18:w=19;break;
		case 19:w=18;break;
	}
	return w;
}  //对缓慢下落的模拟


void DrawBox_s(uint16_t x,uint16_t y)
{
	//480x320   24x11   480x220     20	
	State[x-1][y]=1;
}

void DeleteBox_s(uint16_t x,uint16_t y)
{
	//480x320   24x11   480x220     20	
	State[x-1][y]=0;
}  //这俩函数暂时不知道啥意思

void DrawPic_s(uint16_t x,uint16_t y,uint8_t what)
{
	//左上角为原点
	switch (what)
	{
		case 1:   //正方形
		{
		DrawBox_s(x,y);
		DrawBox_s(x+1,y);
		DrawBox_s(x,y+1);
		DrawBox_s(x+1,y+1);
		}
		break;
		
		case 2:   //长条 竖
		{
		DrawBox_s(x,y);
		DrawBox_s(x+1,y);
		DrawBox_s(x+2,y);
		DrawBox_s(x+3,y);
		}
		break;
		
		case 3:   //长条 横
		{
		DrawBox_s(x,y);
		DrawBox_s(x,y+1);
		DrawBox_s(x,y+2);
		DrawBox_s(x,y+3);
		}
		break;
		
		case 4:   //1+3 向左
		{
		DrawBox_s(x+1,y);
		DrawBox_s(x,y+1);
		DrawBox_s(x+1,y+1);
		DrawBox_s(x+2,y+1);
		}
		break;
		
		case 5:   //1+3 向下 逆时针
		{
		DrawBox_s(x+1,y+1);
		DrawBox_s(x,y);
		DrawBox_s(x,y+1);
		DrawBox_s(x,y+2);
		}
		break;

		case 6:   //1+3 向上
		{
		DrawBox_s(x,y+1);
		DrawBox_s(x+1,y);
		DrawBox_s(x+1,y+1);
		DrawBox_s(x+1,y+2);
		}
		break;
		
		case 7:   //1+3 向右
		{
		DrawBox_s(x+1,y+1);
		DrawBox_s(x,y);
		DrawBox_s(x+1,y);
		DrawBox_s(x+2,y);
		}
		break;
	
		case 8:   // 倒L形态1
		{
		DrawBox_s(x,y);
		DrawBox_s(x,y+1);
		DrawBox_s(x,y+2);
		DrawBox_s(x+1,y+2);
		}
		break;
		
		case 9:   // 倒L形态2 逆时针
		{
		DrawBox_s(x,y);
		DrawBox_s(x,y+1);
		DrawBox_s(x+1,y);
		DrawBox_s(x+2,y);
		}
		break;
		
		case 10:   // 倒L形态3
		{
		DrawBox_s(x,y);
		DrawBox_s(x+1,y);
		DrawBox_s(x+1,y+1);
		DrawBox_s(x+1,y+2);
		}
		break;
		
		case 11:   // 倒L形态4
		{
		DrawBox_s(x,y+1);
		DrawBox_s(x+1,y+1);
		DrawBox_s(x+2,y+1);
		DrawBox_s(x+2,y);
		}
		break;
		
		case 12:   // L形态1
		{
		DrawBox_s(x+1,y);
		DrawBox_s(x+1,y+1);
		DrawBox_s(x+1,y+2);
		DrawBox_s(x,y+2);
		}
		break;
		
		case 13:   // L形态2
		{
		DrawBox_s(x,y);
		DrawBox_s(x+1,y);
		DrawBox_s(x+2,y);
		DrawBox_s(x+2,y+1);
		}
		break;
		
		case 14:   // L形态3
		{
		DrawBox_s(x,y);
		DrawBox_s(x+1,y);
		DrawBox_s(x,y+1);
		DrawBox_s(x,y+2);
		}
		break;
		
		case 15:   // L形态4
		{
		DrawBox_s(x,y);
		DrawBox_s(x,y+1);
		DrawBox_s(x+1,y+1);
		DrawBox_s(x+2,y+1);
		}
		break;
		
		
		case 16:   //梯形 横
		{
		DrawBox_s(x+1,y);
		DrawBox_s(x+1,y+1);
		DrawBox_s(x,y+1);
		DrawBox_s(x,y+2);
		}
		break;
		
		case 17:   //梯形 竖
		{
		DrawBox_s(x,y);
		DrawBox_s(x+1,y);
		DrawBox_s(x+1,y+1);
		DrawBox_s(x+2,y+1);
		}
		break;
		
		case 18:   //反梯形 横
		{
		DrawBox_s(x,y);
		DrawBox_s(x,y+1);
		DrawBox_s(x+1,y+1);
		DrawBox_s(x+1,y+2);
		}
		break;
		
		case 19:   //反梯形 竖
		{
		DrawBox_s(x,y+1);
		DrawBox_s(x+1,y+1);
		DrawBox_s(x+1,y);
		DrawBox_s(x+2,y);
		}
		break;
		
		case 20: case 21: case 22:    //炸弹
		{
		DrawBox_s(x,y);
		}
		break;
	}
}

void DeletePic_s(uint16_t x,uint16_t y,uint8_t what)
{
	//左上角为原点
	switch (what)
	{
		case 1:   //正方形
		{
		DeleteBox_s(x,y);
		DeleteBox_s(x+1,y);
		DeleteBox_s(x,y+1);
		DeleteBox_s(x+1,y+1);
		}
		break;
		
		case 2:   //长条 竖
		{
		DeleteBox_s(x,y);
		DeleteBox_s(x+1,y);
		DeleteBox_s(x+2,y);
		DeleteBox_s(x+3,y);
		}
		break;
		
		case 3:   //长条 横
		{
		DeleteBox_s(x,y);
		DeleteBox_s(x,y+1);
		DeleteBox_s(x,y+2);
		DeleteBox_s(x,y+3);
		}
		break;
		
		case 4:   //1+3 向左
		{
		DeleteBox_s(x+1,y);
		DeleteBox_s(x,y+1);
		DeleteBox_s(x+1,y+1);
		DeleteBox_s(x+2,y+1);
		}
		break;
		
		case 5:   //1+3 向下 逆时针
		{
		DeleteBox_s(x+1,y+1);
		DeleteBox_s(x,y);
		DeleteBox_s(x,y+1);
		DeleteBox_s(x,y+2);
		}
		break;

		case 6:   //1+3 向上
		{
		DeleteBox_s(x,y+1);
		DeleteBox_s(x+1,y);
		DeleteBox_s(x+1,y+1);
		DeleteBox_s(x+1,y+2);
		}
		break;
		
		case 7:   //1+3 向右
		{
		DeleteBox_s(x+1,y+1);
		DeleteBox_s(x,y);
		DeleteBox_s(x+1,y);
		DeleteBox_s(x+2,y);
		}
		break;
	
		case 8:   // 倒L形态1
		{
		DeleteBox_s(x,y);
		DeleteBox_s(x,y+1);
		DeleteBox_s(x,y+2);
		DeleteBox_s(x+1,y+2);
		}
		break;
		
		case 9:   // 倒L形态2 逆时针
		{
		DeleteBox_s(x,y);
		DeleteBox_s(x,y+1);
		DeleteBox_s(x+1,y);
		DeleteBox_s(x+2,y);
		}
		break;
		
		case 10:   // 倒L形态3
		{
		DeleteBox_s(x,y);
		DeleteBox_s(x+1,y);
		DeleteBox_s(x+1,y+1);
		DeleteBox_s(x+1,y+2);
		}
		break;
		
		case 11:   // 倒L形态4
		{
		DeleteBox_s(x,y+1);
		DeleteBox_s(x+1,y+1);
		DeleteBox_s(x+2,y+1);
		DeleteBox_s(x+2,y);
		}
		break;
		
		case 12:   // L形态1
		{
		DeleteBox_s(x+1,y);
		DeleteBox_s(x+1,y+1);
		DeleteBox_s(x+1,y+2);
		DeleteBox_s(x,y+2);
		}
		break;
		
		case 13:   // L形态2
		{
		DeleteBox_s(x,y);
		DeleteBox_s(x+1,y);
		DeleteBox_s(x+2,y);
		DeleteBox_s(x+2,y+1);
		}
		break;
		
		case 14:   // L形态3
		{
		DeleteBox_s(x,y);
		DeleteBox_s(x+1,y);
		DeleteBox_s(x,y+1);
		DeleteBox_s(x,y+2);
		}
		break;
		
		case 15:   // L形态4
		{
		DeleteBox_s(x,y);
		DeleteBox_s(x,y+1);
		DeleteBox_s(x+1,y+1);
		DeleteBox_s(x+2,y+1);
		}
		break;
		
		
		case 16:   //梯形 横
		{
		DeleteBox_s(x+1,y);
		DeleteBox_s(x+1,y+1);
		DeleteBox_s(x,y+1);
		DeleteBox_s(x,y+2);
		}
		break;
		
		case 17:   //梯形 竖
		{
		DeleteBox_s(x,y);
		DeleteBox_s(x+1,y);
		DeleteBox_s(x+1,y+1);
		DeleteBox_s(x+2,y+1);
		}
		break;
		
		case 18:   //反梯形 横
		{
		DeleteBox_s(x,y);
		DeleteBox_s(x,y+1);
		DeleteBox_s(x+1,y+1);
		DeleteBox_s(x+1,y+2);
		}
		break;
		
		case 19:   //反梯形 竖
		{
		DeleteBox_s(x,y+1);
		DeleteBox_s(x+1,y+1);
		DeleteBox_s(x+1,y);
		DeleteBox_s(x+2,y);
		}
		break;
		
		case 20: case 21: case 22:    //炸弹
		{
		DeleteBox_s(x,y);
		}
		break;
	}
}

void MoveDown_s(uint16_t x,uint16_t y,uint8_t what)
{
	DeletePic_s(x,y,what);
	DrawPic_s(x+1,y,what);
}
void MoveLeft_s(uint16_t x,uint16_t y,uint8_t what)
{
	DeletePic_s(x,y,what);
	DrawPic_s(x,y-1,what);
}
void MoveRight_s(uint16_t x,uint16_t y,uint8_t what)
{
	DeletePic_s(x,y,what);
	DrawPic_s(x,y+1,what);
}
void Change_s(uint16_t x,uint16_t y,uint8_t what)
{
	switch(what)
	{
		case 1:break;
		
		case 2:DeletePic_s(x,y,2);DrawPic_s(x,y,3);break;
		case 3:DeletePic_s(x,y,3);DrawPic_s(x,y,2);break;
		
		case 4:DeletePic_s(x,y,4);DrawPic_s(x,y,5);break;
		case 5:DeletePic_s(x,y,5);DrawPic_s(x,y,7);break;
		case 6:DeletePic_s(x,y,6);DrawPic_s(x,y,4);break;
		case 7:DeletePic_s(x,y,7);DrawPic_s(x,y,6);break;
		
		case 8:DeletePic_s(x,y,8);DrawPic_s(x,y,9);break;
		case 9:DeletePic_s(x,y,9);DrawPic_s(x,y,10);break;
		case 10:DeletePic_s(x,y,10);DrawPic_s(x,y,11);break;
		case 11:DeletePic_s(x,y,11);DrawPic_s(x,y,8);break;
			
		case 12:DeletePic_s(x,y,12);DrawPic_s(x,y,15);break;
		case 13:DeletePic_s(x,y,13);DrawPic_s(x,y,12);break;
		case 14:DeletePic_s(x,y,14);DrawPic_s(x,y,13);break;
		case 15:DeletePic_s(x,y,15);DrawPic_s(x,y,14);break;
		
		case 16:DeletePic_s(x,y,16);DrawPic_s(x,y,17);break;
		case 17:DeletePic_s(x,y,17);DrawPic_s(x,y,16);break;
		
		case 18:DeletePic_s(x,y,18);DrawPic_s(x,y,19);break;
		case 19:DeletePic_s(x,y,19);DrawPic_s(x,y,18);break;
	}
}

int Crash(uint16_t x,uint16_t y,uint8_t what,uint8_t Direction)
{
	uint16_t sum1=0,sum2=0;
	uint8_t i,n;
	uint8_t sbuf[25][13];
	for(i=0;i<25;i++)
	{
		for(n=0;n<13;n++)
		{
			sbuf[i][n]=State[i][n];
			sum1=sum1+State[i][n];	
		}	  
	}
	switch(Direction)
	{
		case 1: MoveDown_s(x,y,what);break;
		case 2: MoveLeft_s(x,y,what);break;
		case 3: MoveRight_s(x,y,what);break;
		case 4: Change_s(x,y,what);break;
	}
	for(i=0;i<25;i++){		
		for(n=0;n<13;n++){
	  	sum2=sum2+State[i][n];	
	  	State[i][n]=sbuf[i][n];			
    }
	}
	return !(sum1==sum2);  //发生碰撞返回1
}

void ExchangeLine(uint16_t x)  //x取1~23 和对应下一行交换
{
	uint8_t i;
	uint8_t color_temp;
	for(i=1;i<12;i++)
	{
		if(State[x-1][i]==0 && State[x][i]==0){}
		else if(State[x-1][i]==1 && State[x][i]==1)
		{			
			color_temp=Color[x-1][i-1];
			Color[x-1][i-1]=Color[x][i-1];
			Color[x][i-1]=color_temp;
			
			DrawBox(x,i,Color[x-1][i-1]);
			DrawBox(x+1,i,Color[x][i-1]);
		}
		else if(State[x-1][i]==0 && State[x][i]==1)
		{
			DrawBox_s(x,i);
			DeleteBox_s(x+1,i);
			
			Color[x-1][i-1]=Color[x][i-1];
			
			DrawBox(x,i,Color[x-1][i-1]);
			DeleteBox(x+1,i);
		}
		else if(State[x-1][i]==1 && State[x][i]==0)
		{
			DeleteBox_s(x,i);
			DrawBox_s(x+1,i);
			
			Color[x][i-1]=Color[x-1][i-1];
			
			DeleteBox(x,i);
			DrawBox(x+1,i,Color[x][i-1]);
		}
	}
}  //将给定行x及其下一行的方块颜色进行交换


void DeleteLine(uint16_t x)
{
	uint8_t i;
	for(i=1;i<12;i++)
	{
		DeleteBox_s(x,i);
		DeleteBox(x,i);
	}
}  

int ClearLine()
{
	uint8_t ret=0;
	uint8_t n,i;
	uint8_t State_sum[25];
	State_sum[0]=0;
	for(n=0;n<24;n++){
		State_sum[n+1]=0;
		for(i=1;i<12;i++){
			State_sum[n+1] += State[n][i];
		}
	}
	for(n=24;n>0;n--)
	{
		if(State_sum[n]==11){
			DeleteLine(n);
			score+=11;
			ret=1;
			for(i=n-1;i>0;i--){
				ExchangeLine(i);
			}
			ClearLine();
			break;
		}
	}
	return ret;
}  //清除满行并更新分数

void PicInit()
{
	uint8_t i,j;
	for(i=0;i<24;i++){
		for(j=1;j<12;j++){
			Color[i][j-1]=0;
			if(State[i][j]==1){
				DrawBox(i+1,j,0);
			}
		}
	}
  if(mode==4){
		POINT_COLOR=BLACK;
		for(i=20;i<25;i++){
			for(j=1;j<12;j++){
				LCD_Fill(13*j-12, 13*i-12, 13*j-1, 13*i-1, GRAY);
				LCD_DrawRectangle(13*j-12, 13*i-12, 13*j-1, 13*i-1);
			}
		}
	}
}  //初始化

void Explode(uint16_t x,uint16_t y)
{
	DeleteBox(x,y); DeleteBox_s(x,y);
	if(x>1 && State[x-2][y]==1){   //消除上方
		DeleteBox(x-1,y); DeleteBox_s(x-1,y); score++;
	}
	if(x<24 && State[x][y]==1){    //消除下方
		DeleteBox(x+1,y); DeleteBox_s(x+1,y); score++;
	}
	if(y>1 && State[x-1][y-1]==1){   //消除左方
		DeleteBox(x,y-1); DeleteBox_s(x,y-1); score++;
	}
	if(y<11 && State[x-1][y+1]==1){    //消除右方
		DeleteBox(x,y+1); DeleteBox_s(x,y+1); score++;
	}
	if(x>1 && y>1 && State[x-2][y-1]==1){   //消除左上
		DeleteBox(x-1,y-1); DeleteBox_s(x-1,y-1); score++;
	}
  if(x>1 && y<11 && State[x-2][y+1]==1){    //消除右上
		DeleteBox(x-1,y+1); DeleteBox_s(x-1,y+1); score++;
	}
	if(x<24 && y>1 && State[x][y-1]==1){     //消除左下
		DeleteBox(x+1,y-1); DeleteBox_s(x+1,y-1); score++;
	}	
	if(x<24 && y<11 && State[x][y+1]==1){      //消除右下
		DeleteBox(x+1,y+1); DeleteBox_s(x+1,y+1); score++;
	}
}  //消除周围的方块并更新分数

void LightOn(uint16_t x,uint16_t y){
	uint8_t i,j;
	for(i=0;i<=4;i++){
		for(j=0;j<=4;j++){
			if(x+i-2>=20 && x+i-2<=24 && y+j-2>=1 && y+j-2<=11){
				DrawBox(x+i-2,y+j-2,Color[x+i-3][y+j-3]+100);
			}
		}
	}	
}  //将指定位置周围的方格变成明亮的颜色

void LightOff(uint16_t x,uint16_t y){
	uint8_t i,j;
	for(i=0;i<=4;i++){
		for(j=0;j<=4;j++){
			if(x+i-2>=20 && x+i-2<=24 && y+j-2>=1 && y+j-2<=11){
				DrawBox(x+i-2,y+j-2,Color[x+i-3][y+j-3]);
			}
		}
	}	
}

int main(void)
{	uint16_t key=0;
 	uint8_t x,y,what,next_what;
  uint8_t lose_flag=0;
	uint8_t clear_flag=0;
	uint8_t light;

	SYSInit();
	LCD->LCD_RST = 0;
	delay(5000000);
	LCD->LCD_RST = 1;
	LCD_Init();
	*GPIO_OEN=0x00;
	//一些初始化设定
	
	while(1)	 
{	LCD_Clear(WHITE);
	POINT_COLOR=RED;
	LCD_ShowString(30,10,200,24,24,"Press Button To");
	LCD_ShowString(50,40,200,24,24,"Select Mode");
	POINT_COLOR=BLACK;
	LCD_ShowString(20,90,200,24,24,"   1       2");
	LCD_ShowString(20,120,200,24,24,"   3       4");
	POINT_COLOR=BLUE;
	LCD_ShowString(23,160,200,24,24,"Normal   Block");
	LCD_ShowString(23,200,200,24,24,"Explode  Hiding");
	//初始界面
	
	
	while(1){
		if(*GPIO_IDR==0xff){
			key=*GPIO_IDR;
		}
	  else if(*GPIO_IDR!=0xff){
			key=*GPIO_IDR;
			if(key==0xfe)      //1->普通模式 
			{
				mode=1;
				break;
			}
			else if(key==0xfd)  //2->残局模式
			{
				mode=2;
				break;
			}
			else if(key==0xfb)  //3->炸弹模式
			{
				mode=3;
				break;
			}
			else if(key==0xf7)  //4->迷雾模式
			{
				mode=4;
				break;
			}
		}
	}
	
	LCD_Clear(WHITE);
	POINT_COLOR=RED;
	LCD_ShowString(30,10,200,24,24,"Press Button To");
	LCD_ShowString(50,40,200,24,24,"Select Level");
	POINT_COLOR=BLACK;
	LCD_ShowString(20,70,200,24,24,"   1       2");
	LCD_ShowString(20,100,200,24,24,"       3      ");
	POINT_COLOR=BLUE;
	LCD_ShowString(23,140,200,24,24,"  Easy   Middle");
	LCD_ShowString(80,180,200,24,24,"Hard");
	
	
	while(1){
		if(*GPIO_IDR==0xff){
			key=*GPIO_IDR;
		}
	  else if(*GPIO_IDR!=0xff){
			key=*GPIO_IDR;
			if(key==0xfe)     //1->简单
			{
				level=1;
				falltime=15;
				break;
			}
			else if(key==0xfd)   //2->中级
			{
				level=2;
				falltime=10;
				break;
			}
			else if(key==0xfb)  //3->困难
			{
				level=3;
				falltime=5;
				break;
			}
		}
	}
		
	LCD_Clear(WHITE);
	POINT_COLOR=BLACK;
	score=0;	
	StateInit();
	PicInit();
	
	LCD_DrawLine(170,0,170,320);
	what=rand()%19+1;
	POINT_COLOR=BLACK;
	LCD_ShowString(30,10,200,18,18,"NEXT");
	DrawPic(5,13,what);
	LCD_ShowString(100,135,200,10,10,"SCORE");
	POINT_COLOR=BLUE;
	LCD_ShowNum(100,165,score,3,10);
	POINT_COLOR=BLACK;
	LCD_ShowString(100,210,200,10,10,"MODE");
	POINT_COLOR=BLUE;
	switch(mode){
		case 1:
			LCD_ShowString(100,240,200,10,10,"Normal");
		break;
		case 2:
			LCD_ShowString(100,240,200,10,10,"Block");
		break;
		case 3:
			LCD_ShowString(100,240,200,10,10,"Explode");
		break;
		case 4:
			LCD_ShowString(100,240,200,10,10,"Hiding");
		break;
	}
	POINT_COLOR=BLACK;
	LCD_ShowString(100,210,140,10,10,"LEVEL");
	POINT_COLOR=BLUE;
	switch(level){
		case 1:
			LCD_ShowString(100,240,200,10,10,"Easy");
		break;
		case 2:
			LCD_ShowString(100,240,200,10,10,"Middle");
		break;
		case 3:
			LCD_ShowString(100,240,200,10,10,"Hard");
		break;
	}
	POINT_COLOR=BLACK;
	DeletePic(5,13,what);
	 
  while(1){	
		x=1;y=5;
		if(mode==3||mode==4){
			next_what=rand()%22+1;
		}
		else{
			next_what=rand()%13+1;
		}
		
		DrawPic(5,13,next_what);
		DrawPic(x,y,what);
		DrawPic_s(x,y,what);
		i_time=0; 
		if(mode==4 && what>=20) {
			light=1;
		}
		else{
			light=0;
		}
    while(1){		
			if(light==1) LightOn(x,y);
			key=*GPIO_IDR;
			if(key!=0xff){				
				switch(key){    
					case 0xfe:    //DOWN->向下
					{
						if(Crash(x,y,what,1)==0){
							if(light==1) LightOff(x,y);
							MoveDown(x,y,what);
			      	MoveDown_s(x,y,what);
							x++;
							if(light==1) LightOn(x,y);
						}
						break;
					}	
		  		case 0xfd:		 //LEFT->向左 
					{
						if(Crash(x,y,what,2)==0){
							if(light==1) LightOff(x,y);
							MoveLeft(x,y,what);
			      	MoveLeft_s(x,y,what);
							y--;
							if(light==1) LightOn(x,y);
						}
						break;
					}
					case 0xfb:    //RIGHT->向右
					{
						if(Crash(x,y,what,3)==0){
							if(light==1) LightOff(x,y);
							MoveRight(x,y,what);
			      	MoveRight_s(x,y,what);
							y++;
							if(light==1) LightOn(x,y);
						}
						break;
					}
					case 0xf7:     //UP->变形
					{
						if(Crash(x,y,what,4)==0){
							Change(x,y,what);
			      	Change_s(x,y,what);
							what=Change_w(what);
						}
						break;	 
					}			
					case 0xef:     	//PLAY->开始	
					{
						//DeleteLine(24);
						break;
					}
		  	}
			}			
      if (i_time>=falltime){
		  	i_time=0;
				if(Crash(x,y,what,1)==1){
					if(light==1) LightOff(x,y);
					if(what==20&&mode==3){
						Explode(x,y);
					}
					else{
						clear_flag=ClearLine();
						if(x==1 && !clear_flag){
							lose_flag=1;
						}
						clear_flag=0;
					}
					POINT_COLOR=BLUE;
		    	LCD_ShowNum(189,165,score,3,18);
		    	POINT_COLOR=BLACK;
					break;
				}
				else if(Crash(x,y,what,1)==0){
					if(light==1) LightOff(x,y);
					MoveDown(x,y,what);
			  	MoveDown_s(x,y,what);
					x++;
					if(light==1) LightOn(x,y);
				}
  		}
	  }	
		if(lose_flag==1){
			POINT_COLOR=RED;
			LCD_ShowString(25,134,200,24,24,"You Are Lose!");
			LCD_ShowString(30,174,200,24,24,"Press \"PLAY\"");
			LCD_ShowString(30,214,200,24,24," To Restart");
			lose_flag=0;
			break;
		}
		DeletePic(5,13,next_what);
		what=next_what;
	} 
	while(1){
		key=*GPIO_IDR;
		if(key==0xef) break;
	}
 }	
/*
	//NVIC_CTRL_ADDR = 1;
	*GPIO_OEN=0X00;
	*GPIO_ODR=0X00;
	if(*GPIO_IDR==0xFF){*GPIO_OEN=0X01;
	*GPIO_ODR=0XE0;}*/
	
	/*
	if(ReadUART()==0x00){*GPIO_OEN=0X01;
	*GPIO_ODR=0XE0;}*/
	/*
	LCD->LCD_RST=1;
	if(LCD->LCD_RST==1){*GPIO_OEN=0X01;
	*GPIO_ODR=0XFE;}
	*/
	/**GPIO_OEN=0x01;
	*GPIO_ODR=0x01;
	uint16_t i=1000;
	while((i--)>0){
		if(*GPIO_ODR==0xff){
		*GPIO_ODR=0x01;
		}
		delay(20000);
		(*GPIO_ODR) =(*GPIO_ODR)+0x01;
		
	}*/
	//LCD->LCD_RST=0;
	/*
	SYSInit();
	LCD->LCD_RST = 0;
	delay(5000000);
	LCD->LCD_RST = 1;
	LCD_Init();
	LCD_Set_Window(0,0,240,320);
	while (1) {
		for (x = 20; x < 220; x += dx) {
			for (y = 20; y < 300; y += dy) {
				LCD_Fill(x, y, x + dx, y + dy, RED);
				delay(50000000);
				LCD_Clear(WHITE);
			}
		}
	}*/
}

