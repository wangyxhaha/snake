#include <iostream>
#include <queue>
#include <graphics.h>
#include <windows.h>
using namespace std;

struct node{
    int x,y,d;
};

int dx[]={0,-1,0,1},
    dy[]={-1,0,1,0};

int start_menu(){
    setbkcolor(BLACK);
    setcolor(WHITE);
    setfont(10,10,"Fixedsys");
    int cho=0;
    while (1){
        cleardevice();
        if (cho==0) xyprintf(0,0,"> start");
        else xyprintf(0,0,"  start");
        if (cho==1) xyprintf(0,15,"> setting");
        else xyprintf(0,15,"  setting");
        if (cho==2) xyprintf(0,30,"> exit");
        else xyprintf(0,30,"  exit");
        delay_ms(0);
        cout << '^' << endl;
        Sleep(200);
        while (1){
            if (keystate(VK_UP)){
                cho=(cho-1+3)%3;
                break;
            }
            if (keystate(VK_DOWN)){
                cho=(cho+1)%3;
                break;
            }
            if (keystate(VK_RETURN)){
                cleardevice();
                return cho;
            }
            if (!is_run()){
                return -1;
            }
        }
        cout << cho << endl;
    }
    return -1;
}

void loading(){
    setbkcolor(BLACK);
    setcolor(WHITE);
    setfont(10,10,"Fixedsys");
    for (int i=0;i<10;i++){
        xyprintf(i*5,0,".");
        Sleep(20);
    }
    xyprintf(50,0,"done");
    for (int i=0,j=0;i<4;i++,j=!j){
        if (j) setfillcolor(WHITE);
        else setfillcolor(BLACK);
        bar(83,2,90,12);
        Sleep(500);
    }
    return;
}

void dea(){
    setbkcolor(BLACK);
    setcolor(WHITE);
    setfont(10,10,"Fixedsys");
    xyprintf(0,0,"defeat");
    getch();
    return;
}

void win(){
    setbkcolor(BLACK);
    setcolor(WHITE);
    setfont(10,10,"Fixedsys");
    xyprintf(0,0,"you win");
    getch();
    return;
}

int game_loop(){
    loading();
    cleardevice();
    setbkcolor(BLACK);
    setfillcolor(WHITE);
    setcolor(WHITE);
    setfont(10,10,"Fixedsys");
    node s[400],food;
    int head=0,dir,len=2,eat=0;
    s[0].x=9,s[0].y=9,s[0].d=0;
    food.x=11,food.y=11;
    xyprintf(0,0,"ready");
    bar(216,216,240,240);
    delay_ms(0);
    char c=getch();
    if (c=='w'){
        head=1,dir=0;
        s[1].x=9,s[1].y=8,s[1].d=0;
    }
    if (c=='a'){
        head=1,dir=1;
        s[1].x=8,s[1].y=9,s[1].d=0;
    }
    if (c=='s'){
        head=1,dir=2;
        s[1].x=9,s[1].y=10,s[1].d=0;
    }
    if (c=='d'){
        head=1,dir=3;
        s[1].x=10,s[1].y=9,s[1].d=0;
    }
    bool gmap[20][20];
    int de=0;
    while (1){
        if (!is_run()){
            return -1;
        }
        cout << de << endl;
        if (de==5){
            cout << "d" << endl;
            cleardevice();
            if (s[head].x>19 && s[head].x<0 && s[head].y>19 && s[head].y<0){
                cout << "out" << endl;
                dea();
                break;
            }
            bool lose=0;
            memset(gmap,0,sizeof(gmap));
            for (int i=0,j=s[head].d;i<len-1;i++){
                bar(s[j].x*24,s[j].y*24,s[j].x*24+24,s[j].y*24+24);
                gmap[s[j].x][s[j].y]=1;
                if (s[j].x==s[head].x && s[j].y==s[head].y){
                    lose=1;
                    cout << head << ' ' << s[head].x << ' ' << s[head].y << endl;
                    cout << j << ' ' << s[j].x << ' ' << s[j].y << endl;
                }
                j=s[j].d;
            }
            gmap[s[head].x][s[head].y]=1;
            bar(s[head].x*24,s[head].y*24,s[head].x*24+24,s[head].y*24+24);
            if (s[head].x==food.x && s[head].y==food.y){
                eat=2;
                int x,y;
                while (1){
                    x=random(20),y=random(20);
                    if (!gmap[x][y]) break;
                }
                food.x=x,food.y=y;
            }
            bar(food.x*24,food.y*24,food.x*24+24,food.y*24+24);
            if (lose){
                cout << "b" << endl; 
                dea();
                break;
            }
            if (len==400){
                win();
                break;
            }
            int next=(head+1)%400;
            s[next].x=(s[head].x+dx[dir]+20)%20,s[next].y=(s[head].y+dy[dir]+20)%20,s[next].d=head;
            head=next;
            if (eat>0){
                eat--,len++;
            }
            de=0;
        }
        if (keystate('W')) dir=0;
        if (keystate('A')) dir=1;
        if (keystate('S')) dir=2;
        if (keystate('D')) dir=3;
        de++;
        cout << '+' << endl;
        delay_fps(60);
    }
    return 0;
}

void setting(){
    setbkcolor(BLACK);
    setfont(10,10,"Fixedsys");
    xyprintf(0,0,"no settings!!!");
    Sleep(2000);
    return;
}

void main_loop(){
    while (1){
        int cho=start_menu();
        if (cho==-1){
            break;
        }
        if (cho==0){
            if (game_loop()==-1) break;
        }
        if (cho==1){
            setting();
        }
        if (cho==2){
            break;
        }
    }
    return;
}

int main(){
    randomize();
    setinitmode(!INIT_WITHLOGO);
    initgraph(480,480);
    main_loop();
	closegraph();
    return 0;
}

