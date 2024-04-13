#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>
#include<string.h>
int l,b,de,kk,I,J ; //variables for initial speed,pieslice and
		    //length and breadth of one unit of snake
int arr[64][48]={0,0};  //screen array for motion of snake and pieslice
struct node{
 int x1;
 int y1;
 int x2;
 int y2;
 char cd;
 struct node *ag;
};
struct keys{
struct keys *L;
struct keys *R;
struct keys *u;
struct keys *d;
char *key;
int x;
int y;
char p;
};
struct keys *root=NULL;
struct node *head=NULL;
int highscore(int hs,char mode){
FILE *f=NULL;
f=fopen("H1S.TXT","r+") ;
if(f==NULL)
printf("unable to open file ");
if(mode=='n')
fprintf(f,"%d",hs);
else if(mode=='o')
fscanf(f,"%d",&hs);
fclose(f);
return hs;
}
void score(){  //change highscoe
int cs=kk*100,i=0,r=0,hs;char cr1[8]={'\0'},cr2[8]={'\0'};
while(cs!=0){
cr1[i]=(cs%10)+48;
cs=cs/10;
i++;
}
i=i-1;
while(i>=0){
cr2[r]=cr1[i];
i--;
r++;
}
settextstyle(1,0,3);
setcolor(8);
setfillstyle(1,14);
bar(40,430,120,470);
outtextxy(40,430,cr2);
cs=kk*100;
hs=highscore(hs,'o');
if(cs>=hs){
hs=cs;
highscore(hs,'n');
settextstyle(1,0,3);
setcolor(8);
setfillstyle(1,14);
bar(450,430,550,470);
outtextxy(450,430,cr2);
}
}
void speed(){int sp=100-de,i=0,r=0;char cr1[4]={'\0'},cr2[4]={'\0'};
if(sp<70){       //controls speed after some eating some apples
while(sp!=0){
cr1[i]=(sp%10)+48;
sp=sp/10;
i++;
}
i=i-1;
while(i>=0){
cr2[r]=cr1[i];
i--;
r++;
}
cr2[2]='%';
setcolor(8);
settextstyle(1,0,3);
setfillstyle(1,14);
bar(250,430,330,470);
outtextxy(250,430,cr2);}
else{
setcolor(8);
settextstyle(1,0,3);
setfillstyle(1,14);
bar(250,430,330,470);
outtextxy(250,430,"Max");
}
}
void applekhaya(int i,int j,struct node *ptr){   //increases length of snake
int y=0;                                       //setting new pislice
kk++;
if(kk%5==0){
if(de>40){
de=de-20;
speed(de);  }
else if(de>29){
de=de-5;
speed();       }
}
score();
sound(200);
delay(30);
nosound();
setcolor(14);
setfillstyle(1,14);
setlinestyle(0,0,0);
pieslice(i*10+5,j*10+5,0,360,5);
while(y==0){
i=random(64);
j=random(40);
if(arr[i][j]==1||arr[i][j]==4)
y=0;
else{
y=1;
arr[i][j]=3;
I=i;J=j;}
}
setcolor(14);
setfillstyle(1,5);
setlinestyle(0,0,0);
pieslice(i*10+5,j*10+5,0,360,5);
while(!ptr->ag==NULL){
ptr=ptr->ag;
}
ptr->ag=(struct node*)malloc(1*sizeof(struct node));
if(ptr->cd=='d'){
ptr->ag->x1=ptr->x2;
ptr->ag->y1=ptr->y2-b;
ptr->ag->x2=ptr->x2-l;
ptr->ag->y2=ptr->y2;
ptr->ag->cd='d';
ptr=ptr->ag;
ptr->ag=NULL;    }
else if(ptr->cd=='a'){
ptr->ag->x1=ptr->x2;
ptr->ag->y1=ptr->y2-b;
ptr->ag->x2=ptr->x2+l;
ptr->ag->y2=ptr->y2;
ptr->ag->cd='a' ;
ptr=ptr->ag;
ptr->ag=NULL;    }
else if(ptr->cd=='w'){
ptr->ag->x1=ptr->x2-b;
ptr->ag->y1=ptr->y2;
ptr->ag->x2=ptr->x2;
ptr->ag->y2=ptr->y2+l;
ptr->ag->cd='w';
ptr=ptr->ag;
ptr->ag=NULL;    }
else if(ptr->cd=='s'){
ptr->ag->x1=ptr->x2+b;
ptr->ag->y1=ptr->y2;
ptr->ag->x2=ptr->x2;
ptr->ag->y2=ptr->y2-l;
ptr->ag->cd='s';
ptr=ptr->ag;
ptr->ag=NULL;    }
}
void destroysnake(struct node *ptr){
 if(ptr->ag==NULL)
 return ;
 else{
    destroysnake(ptr->ag);
    ptr->ag=NULL;
    return;
 }
}
void snakemitao(struct node *ptr){
if(ptr==NULL)
return;
else{
setfillstyle(1,14);
bar(ptr->x2,ptr->y2,ptr->x1,ptr->y1);
if(ptr->cd=='d')
arr[((ptr->x1)-l)/l][(ptr->y1)/b]=0;
else if(ptr->cd=='s')
arr[(ptr->x2)/l][(ptr->y2)/b]=0;
else if(ptr->cd=='a'||ptr->cd=='w')
arr[(ptr->x1)/l][(ptr->y1)/b]=0;
snakemitao(ptr->ag);
return;}
}
void gameover(){
setfillstyle(2,7);
bar(250,250,470,300);
setcolor(8);
settextstyle(0,0,3);
outtextxy(250,250,"game over");
sound(493.8833);
delay(600);
sound(523.2511);
delay(600);
sound(698.4565);
delay(600);
sound(659.2551);
delay(600);
nosound();
snakemitao(head); //for setting all values of array to zero
arr[I][J]=0;   // set pieslice coordinate to zero
destroysnake(head);
head=NULL;
}
int snakebnao(int nx2,int ny2,int nx1,int ny1,struct node *ptr, char cd){
int z,i,j,r=0;
if(ptr==NULL)
r=0 ;
else{
setfillstyle(1,6);
bar(nx2,ny2,nx1,ny1);
snakebnao(ptr->x2,ptr->y2,ptr->x1,ptr->y1,ptr->ag,ptr->cd);
ptr->x1=nx1;
ptr->y1=ny1;
ptr->x2=nx2;
ptr->y2=ny2;
ptr->cd=cd;
if(cd=='d'){
z=++arr[(nx1-l)/l][ny1/b]; i=(nx1-l)/l;j=ny1/b;
}
else if(cd=='s') {
z=++arr[nx2/l][ny2/b]; i=nx2/l;j=ny2/b; }
else if(cd=='a'||cd=='w') {
z=++arr[nx1/l][ny1/b];  i=nx1/l;j=ny1/b;   }
if(z==2){
gameover();
r=1;
}
else if(z==4)
applekhaya(i,j,head);
}
return r;
}
char opcr(char ch) {   char k;
if(ch=='a')
k= 'd';
if(ch=='d')
k='a';
if(ch=='s')
k= 'w';
if(ch=='w')
k= 's';
return k;
}
void snakecontrol(){     //control of snake direction
char nd='d',cd='d',pd='d',ch;int nx1=300,ny1=300,nx2=300-l,ny2=300+b;
int over=0;
while(1){
if(nd=='d'){
if(pd=='w'){
nx1=nx1+l+b;
ny1=ny1;
nx2=nx1-l;
ny2=ny1+b;
pd=cd;
over=snakebnao(nx2,ny2,nx1,ny1,head,pd);
if(over==1)
return;//because gameover
delay(de);
snakemitao(head);
}
else if(pd=='s'){
nx2=nx1;
ny2=ny1;
nx1=nx1+l;
ny1=ny1-b;
pd=cd;
over=snakebnao(nx2,ny2,nx1,ny1,head,pd);
if(over==1)
return;
delay(de);
snakemitao(head);
}
else if(pd==cd){
if(nx1>639){
nx1=0+l;
ny1=ny1;
nx2=0;
ny2=ny2;
over=snakebnao(nx2,ny2,nx1,ny1,head,cd);
if(over==1)
return;
delay(de);
snakemitao(head);
}
else{
nx1=nx1+l;
ny1=ny1;
nx2=nx2+l;
ny2=ny2;
over=snakebnao(nx2,ny2,nx1,ny1,head,cd);
if(over==1)
return;
delay(de);
snakemitao(head);
}    }}
else if(nd=='s'){
if(pd=='d'){
nx1=nx1;
ny1=ny1+l+b;
nx2=nx1-b;
ny2=ny1-l;
if(ny1>400){
ny1=0+l;
ny2=ny1-l;  }
pd=cd;
over=snakebnao(nx2,ny2,nx1,ny1,head,pd);
if(over==1)
return;
delay(de);
snakemitao(head);
}
else if(pd=='a'){
nx1=nx1+b;
ny1=ny1+l+b;
nx2=nx1-b;
ny2=ny1-l;
if(ny1>400){
ny1=0+l;
ny2=ny1-l;  }
pd=cd;
over=snakebnao(nx2,ny2,nx1,ny1,head,pd);
if(over==1)
return;
delay(de);
snakemitao(head);
}
else if(pd==cd){
if(ny1>399){
ny1=0+l;
nx1=nx1;
nx2=nx2;
ny2=0;
over=snakebnao(nx2,ny2,nx1,ny1,head,cd);
if(over==1)
return;
delay(de);
snakemitao(head);
}
else{
nx1=nx1;
nx2=nx2;
ny1=ny1+l;
ny2=ny2+l;
over=snakebnao(nx2,ny2,nx1,ny1,head,cd);
if(over==1)
return;
delay(de);
snakemitao(head);
}
}}
else if(nd=='a'){
if(pd=='w'){
nx1=nx1-l;
ny1=ny1;
nx2=nx1+l;
ny2=ny1+b;
pd=cd;
over=snakebnao(nx2,ny2,nx1,ny1,head,pd);
if(over==1)
return;
delay(de);
snakemitao(head);
}
else if(pd=='s'){
nx1=nx1-l-b;
ny1=ny1-b;
nx2=nx1+l;
ny2=ny1+b;
pd=cd;
over=snakebnao(nx2,ny2,nx1,ny1,head,pd);
if(over==1)
return;
delay(de);
snakemitao(head);
}
else if(pd==cd){
if(nx1<1){
nx1=640-l;
ny1=ny1;
nx2=640;
ny2=ny2;
over=snakebnao(nx2,ny2,nx1,ny1,head,cd);
if(over==1)
return;
delay(de);
snakemitao(head);
}
else{
nx1=nx1-l;
ny1=ny1;
nx2=nx2-l;
ny2=ny2;
over=snakebnao(nx2,ny2,nx1,ny1,head,cd);
if(over==1)
return;
delay(de);
snakemitao(head);
}    }}
else if(nd=='w'){
if(pd=='d'){
nx1=nx1-b;
ny1=ny1-l;
nx2=nx1+b;
ny2=ny1+l;
pd=cd;
over=snakebnao(nx2,ny2,nx1,ny1,head,pd);
if(over==1)
return;
delay(de);
snakemitao(head);
}
else if(pd=='a'){
nx1=nx1;
ny1=ny1-l;
nx2=nx1+b;
ny2=ny1+l;
pd=cd;
over=snakebnao(nx2,ny2,nx1,ny1,head,pd);
if(over==1)
return;
delay(de);
snakemitao(head);
}
else if(pd==cd){
if(ny1<1){
ny1=400-l;
nx1=nx1;
nx2=nx2;
ny2=400;
over=snakebnao(nx2,ny2,nx1,ny1,head,cd);
if(over==1)
return;
delay(de);
snakemitao(head);
}
else{
nx1=nx1;
nx2=nx2;
ny1=ny1-l;
ny2=ny2-l;
over=snakebnao(nx2,ny2,nx1,ny1,head,cd);
if(over==1)
return;
delay(de);
snakemitao(head);
}
}}
if(kbhit()){
ch=getch();
if(ch=='x'){
sound(1000);
delay(50);
nosound();
exit(0);
}
else if(ch==cd||ch==opcr(cd))   {
sound(800);
delay(30);
nosound();
}
else if(ch!=cd){
if(ch=='a'||ch=='s'||ch=='d'||ch=='w'){
sound(475);
delay(30);
nosound();
nd=ch;
cd=nd;  }
else
{sound(100);
delay(30);
nosound(); }
}}
}
}
void designGame(){ int hs,r=0,i=0;char cr1[8]={'\0'},cr2[8]={'\0'};
//showing game screen and displaying high score
setbkcolor(14);
setlinestyle(0,0,0);
setcolor(14);
setfillstyle(1,8);
pieslice(105,155,0,360,5);
setfillstyle(3,4);
bar(0,401,640,405);
setcolor(8);
settextstyle(1,0,3);
outtextxy(50,403,"Score");
outtextxy(250,403,"Speed")    ;
outtextxy(450,403,"High Score");
setfillstyle(1,14);
bar(40,430,120,470);
outtextxy(40,430,"00000");
bar(250,430,330,470);
outtextxy(250,430," Min ");
hs=highscore(hs,'o');
if(hs!=0){
while(hs!=0){
cr1[i]=(hs%10)+48;
hs=hs/10;
i++;
}
i=i-1;
while(i>=0){
cr2[r]=cr1[i];
i--;
r++;
} }
else{
for(i=0;i<5;i++)
cr2[i]=48;
}
bar(450,430,550,470);
outtextxy(450,430,cr2);
}
void select(){   //selection of particular box eg. start
setfillstyle(1,12);
bar(root->x-5,root->y-5,root->x+205,root->y+55);
setcolor(9);
setlinestyle(0,0,3);
rectangle(root->x-7,root->y-7,root->x+207,root->y+57);
setcolor(7);
settextstyle(0,0,4);
outtextxy(root->x+5,root->y+8,root->key);
}
void deselect(){   //deselection of particular box eg. start
setfillstyle(1,10);
bar(root->x-8,root->y-8,root->x+208,root->y+58) ;
setfillstyle(1,4);
bar(root->x,root->y,root->x+200,root->y+50);
setcolor(7);
settextstyle(0,0,4);
outtextxy(root->x+5,root->y+8,root->key);
sound(600);
delay(100);
nosound();
}
int maincontrol(){char k; int r;      //control of start window and select
setbkcolor(10);
setfillstyle(1,4);
bar(100,100,300,150);
setcolor(7);
settextstyle(0,0,4);
outtextxy(115,108,"start");
bar(100,170,300,220);
outtextxy(115,178,"About");
bar(100,240,300,290);
outtextxy(115,248,"exit");
select();
while(1){
kbhit();
k=getch();
if(k=='w')
{ deselect();
root=root->u;
select();
}
else if(k=='s'){
deselect();
root=root->d;
select();
}
else if(k=='a'){
sound(400);
delay(200);
nosound();
}
else if(k=='d'){
sound(400);
delay(200);
nosound();
}
else if(k==13){
if(root->p=='d')
exit(0);
else if(root->p=='a'){
sound(250);
delay(30);
nosound();
r= 1; break;
}
else if(root->p=='s'){
sound(250);
delay(30);
nosound();
r= 2; break;}
}
else{
sound(80);
delay(30);
nosound();}}
return r;
}
void destroykeys(struct keys *ptr1){
   struct keys *ptr2=ptr1->u;
   struct keys *ptr3=ptr1->d;
   root=NULL;
   ptr1->u=NULL;
   ptr1->d=NULL;
   ptr2->u=NULL;
   ptr2->d=NULL;
   ptr3->u=NULL;
   ptr3->d=NULL;
}
void about(){ char d;
setbkcolor(4);
printf(" a -> left\n d -> right \n w -> up \n s -> down\n");
printf("Eat the apple and earn points and length of snake will increase\n");
printf("After eating some apples speed will increase\n\n");
printf("press Esc for returning at start window");
while(1){
kbhit();
d=getch();
if(d==27){
sound(350);
delay(30);
nosound();
gotoxy(1,1);
cleardevice();
break;}
else{
sound(90);
delay(30);
nosound();}
}
}
int declarekeys(){  int r;
struct keys *ptr=NULL ,p1,p2,p3;
root=&p1;
p1.L=NULL;
p1.R=NULL;
p1.u=&p3; p1.x= 100;
p1.d=&p2; p1.y= 100;
p1.key="start"; p1.p='a';
p2.L=NULL;
p2.R=NULL;
p2.u=&p1;  p2.x=100;
p2.d=&p3;  p2.y=170;
p2.key="About";  p2.p='s';
p3.L=NULL;
p3.R=NULL;
p3.u=&p2;  p3.x= 100;
p3.d=&p1;  p3.y= 240;
p3.key="exit";   p3.p='d';
r=maincontrol(); //design of start window and select/deselect control
destroykeys(ptr);
return r;
}
void declarenodes(){
struct node s1,s2,s3,s4,s5,s6,s7;  //declaration of for initial snake
head=&s1;
s1.ag=&s2;
s2.ag=&s3;
s3.ag=&s4;
s4.ag=&s5;
s5.ag=&s6;
s6.ag=&s7;
s7.ag=NULL;
s1.x1=300      ; s1.y1=300      ;s1.x2= 300-l     ; s1.y2=300+b  ;  s1.cd='d';
s2.x1=300-l    ; s2.y1=300      ;s2.x2=300-2*l    ; s2.y2=300+b ;   s2.cd='d';
s3.x1=300-2*l  ; s3.y1=300      ;s3.x2= 300-3*l   ; s3.y2=300+b  ;  s3.cd='d';
s4.x1=300-3*l  ; s4.y1=300      ;s4.x2= 300-4*l   ; s4.y2=300+b  ;  s4.cd='d';
s5.x1=300-4*l  ; s5.y1=300      ;s5.x2= 300-5*l   ; s5.y2=300+b  ;  s5.cd='d';
s6.x1=300-5*l  ; s6.y1=300      ;s6.x2= 300-6*l   ; s6.y2=300+b  ;  s6.cd='d';
s7.x1=300-6*l  ; s7.y1=300      ;s7.x2= 300-7*l   ; s7.y2=300+b  ;  s7.cd='d';
designGame(); //design of game
snakecontrol(); //start game and returned only when game over
}
void interface(int x){
if(x==0){//for start window
x=declarekeys(); //design of start window and return a no. of next window
cleardevice();  //for reseting all graphics setting
interface(x); // call for next window
}
else if(x==1){  //for new game
l=10,b=10,de=100,kk=0 ;
arr[10][15]=3;
I=10,J=12;  //for starting pieslice
declarenodes(); //starting game
cleardevice();
interface(0);//again call for start window
}
else if(x==2){
cleardevice();
about();
interface(0);
}
}
void main(){
int gd=DETECT,gm;
clrscr();
initgraph(&gd,&gm,"");
interface(0);
getch();
closegraph();
}