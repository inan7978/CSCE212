#include "gba_2.h"
#include <stdbool.h>

void sync()
{
	while(REG_DISPLAY_VCOUNT >= 160);
	while(REG_DISPLAY_VCOUNT < 160);
}

uint16 makeColor(uint8 r, uint8 g, uint8 b)
{
	return (r & 0x1f) | ((g & 0x1f) << 5) | ((b & 0x1f) << 10);
}

uint32 clamp(int value, int min, int max)
{
	return (value < min ? min : (value > max ? max : value));
}

void drawRect(struct Rect rect, uint16 color)
{
	for(int y = 0; y < rect.h; y++)
	{
		for(int x = 0; x < rect.w; x++)
		{
			SCREENBUFFER[(rect.y + y) * SCREEN_WIDTH + rect.x + x] = color;
		}
	}
}

void init7seg(){
	a.w = 16;
	a.h = 4;
	f.w = 4;
	f.h = 16;
	
	b = c = e = f;
	d = g = a;
	
	a.x = d.x = e.x = f.x = g.x = SCREEN_WIDTH/4;
	b.x = c.x = a.x + a.w;
	
	a.y = b.y = f.y = 0;
	c.y = e.y = g.y = b.y + b.h - a.h;
	d.y = g.y + b.h - a.h;
}
void init7seg2(){
	a1.w = 16;
	a1.h = 4;
	f1.w = 4;
	f1.h = 16;
	
	b1 = c1 = e1 = f1;
	d1 = g1 = a1;
	
	a1.x = d1.x = e1.x = f1.x = g1.x = (2*SCREEN_WIDTH/3);
	b1.x = c1.x = a1.x + a1.w;
	
	a1.y = b1.y = f1.y = 0;
	c1.y = e1.y = g1.y = b1.y + b1.h - a1.h;
	d1.y = g1.y + b1.h - a1.h;
}

void clear7seg(){
	drawRect(a, makeColor(0,0,0));
	drawRect(b, makeColor(0,0,0));
	drawRect(c, makeColor(0,0,0));
	drawRect(d, makeColor(0,0,0));
	drawRect(e, makeColor(0,0,0));
	drawRect(f, makeColor(0,0,0));
	drawRect(g, makeColor(0,0,0));
}
void clear7seg2(){
	drawRect(a1, makeColor(0,0,0));
	drawRect(b1, makeColor(0,0,0));
	drawRect(c1, makeColor(0,0,0));
	drawRect(d1, makeColor(0,0,0));
	drawRect(e1, makeColor(0,0,0));
	drawRect(f1, makeColor(0,0,0));
	drawRect(g1, makeColor(0,0,0));
}

void draw7seg(uint8 num){
	clear7seg();
	bool w, x, y, z;
	
	w = (num >= 8 ? ((num-=8 ) ? 1 : 1) : 0);
	x = (num >= 4 ? ((num-=4 ) ? 1 : 1) : 0);
	y = (num >= 2 ? ((num-=2 ) ? 1 : 1) : 0);
	z = (num >= 1 ? ((num-=1 ) ? 1 : 1) : 0);
	
	if (w || y || (!x && !z) || (x && z))
		drawRect(a, makeColor(0x1f, 0x1f, 0x1f));
	if((y && z) || (!y && !z) || !x)
		drawRect(b, makeColor(0x1f, 0x1f, 0x1f));
	if (x || !y || z)
		drawRect(c, makeColor(0x1f, 0x1f, 0x1f));
	if (w || (y &&!z) || (!x && !z) || (!x && y) || (x && !y &&z))
		drawRect(d, makeColor(0x1f, 0x1f, 0x1f));
	if((y && !z) || (!x && !z))
		drawRect(e, makeColor(0x1f, 0x1f, 0x1f));
	if(w || (x && !y) || (x && !z) || (!y && !z))
		drawRect(f, makeColor(0x1f, 0x1f, 0x1f));
	if(w || (!y && x) || (y && !z) || (y && !x))
		drawRect(g, makeColor(0x1f, 0x1f, 0x1f));
	
}

void draw7seg2(uint8 num){
	clear7seg2();
	bool w, x, y, z;
	
	w = (num >= 8 ? ((num-=8 ) ? 1 : 1) : 0);
	x = (num >= 4 ? ((num-=4 ) ? 1 : 1) : 0);
	y = (num >= 2 ? ((num-=2 ) ? 1 : 1) : 0);
	z = (num >= 1 ? ((num-=1 ) ? 1 : 1) : 0);
	
	if (w || y || (!x && !z) || (x && z))
		drawRect(a1, makeColor(0x1f, 0x1f, 0x1f));
	if((y && z) || (!y && !z) || !x)
		drawRect(b1, makeColor(0x1f, 0x1f, 0x1f));
	if (x || !y || z)
		drawRect(c1, makeColor(0x1f, 0x1f, 0x1f));
	if (w || (y &&!z) || (!x && !z) || (!x && y) || (x && !y &&z))
		drawRect(d1, makeColor(0x1f, 0x1f, 0x1f));
	if((y && !z) || (!x && !z))
		drawRect(e1, makeColor(0x1f, 0x1f, 0x1f));
	if(w || (x && !y) || (x && !z) || (!y && !z))
		drawRect(f1, makeColor(0x1f, 0x1f, 0x1f));
	if(w || (!y && x) || (y && !z) || (y && !x))
		drawRect(g1, makeColor(0x1f, 0x1f, 0x1f));
	
}




int main()
{
	REG_DISPLAY = VIDEOMODE | BGMODE;
	
	int left = 0;
	int right = 240;
	int top2 = 0;
	int top = 0;
	int ballLeft = 130;
	int ballTop = 80;
	int speedLeft = 1;
	int speedUp = 1;
	int score = 0;
	int score2 = 0;
	player.x = left;
	player.y = top;
	player2.x = right - 8;
	player2.y = top2;
	player.w = 8;
	player.h = 32;
	player2.w = 8;
	player2.h = 32;
	
	prevPlayer = player;
	prevPlayer2 = player2;
	
	ball.x = ballLeft;
	ball.y = ballTop;
	ball.w = 8;
	ball.h = 8;
	
	prevBall = ball;
	init7seg();
	draw7seg(score);
	init7seg2();
	draw7seg2(score2);
	while(1)
	{
		sync();
		
		//erase prev ball and player
		drawRect(prevPlayer, makeColor(0,0,0));
		drawRect(prevBall, makeColor(0,0,0));
		drawRect(prevPlayer2, makeColor(0,0,0));
		
		
		if ((ball.y >= player.y) && (ball.y <= player.y+32) && (ball.x == 8)){
			speedLeft = -speedLeft;
		}
		if ((ball.y < player.y) && (ball.y+8 > player.y) && (ball.x == 8)){
			speedLeft = -speedLeft;
		}
		
		if ((ball.y >= player2.y) && (ball.y <= player2.y+32) && (ball.x == 224)){
			speedLeft = -speedLeft;
		}
		if ((ball.y < player2.y) && (ball.y+8 > player2.y) && (ball.x == 224)){
			speedLeft = -speedLeft;
		}
		
		
		ballTop += speedUp;
		ballLeft += speedLeft;
		
		if(!((REG_KEY_INPUT) & A)){
		top++;}
		if(!((REG_KEY_INPUT) & B)){
		top--;}
		
		if(!((REG_KEY_INPUT) & DOWN)){
		top2++;}
		if(!((REG_KEY_INPUT) & UP)){
		top2--;}
		
		top = clamp(top, 0, SCREEN_HEIGHT - player.h);
		top2 = clamp(top2, 0, SCREEN_HEIGHT - player2.h);
		
		ballTop = clamp(ballTop, 0, SCREEN_HEIGHT - ball.h);
		ballLeft = clamp(ballLeft, 0, SCREEN_WIDTH - ball.w);
		
		if(ballTop == 0 || ballTop == SCREEN_HEIGHT - ball.h)
			speedUp = -speedUp;
		if(ballLeft == 0 || ballLeft == SCREEN_WIDTH - ball.w)
			speedLeft = -speedLeft;
		
		
		
		
		player.y = top;
		prevPlayer = player;
		player2.y = top2;
		prevPlayer2 = player2;
		
		
		ball.x = ballLeft;
		ball.y = ballTop;
		prevBall = ball;
		
		if (ball.x == 0){
			ballLeft = 130;
			ballTop = 80;
			if (score2 == 9){
				score2 = 0;
			} else {
			score2 = score2 + 1;
			}
		}
		if (ball.x == 232){
			ballLeft = 130;
			ballTop = 80;
			if (score == 9){
				score = 0;
			} else {
			score = score + 1;
			}
		}
		
	
		
		drawRect(player, makeColor(0,0,0x1f));
		drawRect(player2, makeColor(0,0,0x1f));
		drawRect(ball, makeColor(0x1f,0,0));
		draw7seg(score);
		draw7seg2(score2);
		
	}
}
