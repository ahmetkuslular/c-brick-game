#include <stdio.h>
#include <iostream>
#include <time.h>
#include <graphics.h>
#include <windows.h>

int bx = 50, by = 50;       /* Oyunun oynand��� k�sm�n minumum x ve y de�erleri */
int MaxX = 750, MaxY = 850; /* Oyunun oynand��� k�sm�n maximum x ve y de�erleri */
int puan = 0;
int StartX = (MaxX - bx) / 2, StartY = MaxY - 110; /* Kaykay�n ilk bulundu�u konumun x ve y de�erleri */
int x = StartX, y = StartY - 25, i, j;             /*Topun ilk bulundu�u k�sm�n x ve y de�erleri */
int a, b, can, say;
int level;
static int ekx = 1, eky = 1; /* Topun ad�m miktar� */

struct tugla
{
     int ID;
     int mix;
     int miy;
     int max;
     int may;
     int renk;
} tugla[500];

using namespace std;

void ekran(void);
void blok(int);
void canlar(int);
void kaykay_sekli(int);
void kaykay(void);
void top(void);
void parcala(int);
void dosya(int);
void puanlama(void);
void zaman(void);
void bekle(int);
void baslangic_deger(void);
void oyun_bitti(void);
void oyun_kontrol(int);

int main()
{

     ekran();

     blok(1);

     can = 3;
     canlar(can);

     setcolor(13);
     setfillstyle(11, 11);
     fillellipse(x, y, 10, 10);

     while (1)
     {
          kaykay();
          top();
     }
     return (0);
}

/* Ekran g�r�nt�s�n�n oldu�u b�l�m*/
void ekran()
{
     char bas;
     initwindow(950, 900, "WinBGIm");
     readimagefile("bolum1.jpg", 0, 0, getmaxx(), getmaxy());
     delay(1000);
     outtextxy(550, 800, "BIR TUSA BASINIZ");
     bas = getch();
     cleardevice();
     /* Oyun'un Oynand��� K�sm�n S�n�rlar�n �izilmesi */
     setcolor(14);
     line(bx - 5, by - 5, MaxX, by - 5); /* �st S�n�r */
     line(MaxX, by - 5, MaxX, MaxY);     /* Sa� S�n�r */
     line(bx - 5, MaxY, MaxX, MaxY);     /* Alt S�n�r */
     line(bx - 5, by - 5, bx - 5, MaxY); /* Sol S�n�r */

     /* Sa� Panel (S�re, Can, Puan, En �yi Skor)*/
     rectangle(MaxX + 5, by - 5, getmaxx() - 30, by + 200);
     readimagefile("zaman.jpg", MaxX + 10, by + 5, getmaxx() - 40, by + 50);

     rectangle(MaxX + 5, by + 210, getmaxx() - 30, by + 410);
     readimagefile("can.jpg", MaxX + 10, by + 215, getmaxx() - 40, by + 260);

     rectangle(MaxX + 5, by + 420, getmaxx() - 30, by + 620);
     readimagefile("puan.jpg", MaxX + 10, by + 425, getmaxx() - 40, by + 470);

     rectangle(MaxX + 5, by + 630, getmaxx() - 30, MaxY);
     readimagefile("en_iyi.jpg", MaxX + 10, by + 635, getmaxx() - 40, by + 680);
}

void kaykay_sekli(int renk1, int renk2)
{
     setfillstyle(1, renk1);
     bar(StartX - 50, StartY - 10, StartX + 50, StartY + 10);

     setcolor(renk2);
     setfillstyle(2, renk2);
     fillellipse(StartX - 50, StartY, 10, 10);
     fillellipse(StartX + 50, StartY, 10, 10);
}
void kaykay()
{

     int k_ek = 20; /*Kaykay'�n Ad�m Miktar� */
     char tus;

     /* Kaykay�n �eklini �izilmesi (2 Daire 1 Bar) */
     kaykay_sekli(7, 3);

     tus = getch();

     kaykay_sekli(0, 0);

     if (tus == 77 && StartX + 70 < MaxX)
          StartX += k_ek;
     else if (tus == 75 && StartX - 70 > bx)
          StartX -= k_ek;

     kaykay_sekli(7, 3);
}
void top()
{
     int s, test;

     setcolor(13);
     setfillstyle(11, 11);
     fillellipse(x, y, 10, 10);

     while (1)
     {

          while (kbhit())
               kaykay();

          setcolor(BLACK);
          setfillstyle(11, BLACK);
          fillellipse(x, y, 10, 10);

          x = x - ekx;
          y = y - eky;
          int l = 10;
          int u = 5;
          if (x + 14 > MaxX || x - 14 < bx)
          {
               ekx = ekx * (-1);
               PlaySoundA("1.wav", NULL, SND_ASYNC);
          }
          if (y - 14 < by)
          {
               eky = eky * (-1);
               PlaySoundA("1.wav", NULL, SND_ASYNC);
          }
          else if (y + 14 > MaxY)
          {
               can -= 1;
               PlaySoundA("3.wav", NULL, SND_ASYNC);
               canlar(can);
               baslangic_deger();
               kaykay();
          }

          //yanlara �arpma//
          test = 0;
          for (s = 0; s < a; s++)
          {
               if (y + 8 > tugla[s].miy && y - 8 < tugla[s].may)
               {
                    if ((x + 8 > tugla[s].mix && x + 8 < tugla[s].mix + 5) || (x - 8 < tugla[s].max && x - 8 > tugla[s].max - 5))
                    {
                         ekx = ekx * (-1);
                         PlaySoundA("1.wav", NULL, SND_ASYNC);
                         test = 1;
                         parcala(s);
                    }
               }
          }
          //�st ve alta �arpma

          for (s = 0; s < a; s++)
          {
               if (x + 10 > tugla[s].mix && x - 10 < tugla[s].max)
               {
                    if ((y + 10 > tugla[s].miy && y + 10 < tugla[s].miy + 5) || (y - 10 < tugla[s].may && y - 10 > tugla[s].may - 5))
                    {
                         eky = eky * (-1);
                         PlaySoundA("1.wav", NULL, SND_ASYNC);
                         if (test != 1)
                              parcala(s);
                    }
               }
          }
          test = 0;
          for (s = 0; s < a; s++)
          {
               if ((x + 1 > tugla[s].mix - 1 && x - 1 < tugla[s].max + 1))
               {
                    if (y + 10 == tugla[s].miy - 1 || y - l == tugla[s].may + 1)
                    {
                         eky = eky * (-1);
                         PlaySoundA("1.wav", NULL, SND_ASYNC);
                         test = 1;
                         parcala(s);
                    }
               }
          }
          for (s = 0; s < a; s++)
          {
               if (y + 1 > tugla[s].miy - 1 && y - 1 < tugla[s].may + 1)
               {
                    if (x + 10 == tugla[s].mix - 1 || x - 10 == tugla[s].max + 1)
                    {
                         ekx = ekx * (-1);
                         PlaySoundA("1.wav", NULL, SND_ASYNC);
                         parcala(s);
                    }
               }
          }

          if (y + 11 > StartY - 10 && y - 11 < StartY + 10)
          {
               if (x + 11 > StartX - 65 && x - 11 < StartX + 65)
               {
                    eky = eky * (-1);
                    PlaySoundA("1.wav", NULL, SND_ASYNC);
               }
          }

          setcolor(13);
          setfillstyle(11, 11);
          fillellipse(x, y, 10, 10);
          delay(3);
     }
}

void blok(int level)
{
     dosya(1);

     for (i = 0; i < a; i++)
     {
          if (level == 1 && i < 76)
          {
               setcolor(tugla[i].renk);
               rectangle(tugla[i].mix, tugla[i].miy, tugla[i].mix + 60, tugla[i].miy + 30);
               tugla[i].max = tugla[i].mix + 60;
               tugla[i].may = tugla[i].miy + 30;
               delay(100);
          }
          else if (level == 2 && i < 156 && i > 75)
          {
               setcolor(tugla[i].renk);
               rectangle(tugla[i].mix, tugla[i].miy, tugla[i].mix + 60, tugla[i].miy + 30);
               tugla[i].max = tugla[i].mix + 60;
               tugla[i].may = tugla[i].miy + 30;
               delay(100);
          }
          if ((tugla[i].ID == 991 && level == 2))
          {
               setfillstyle(8, tugla[i].renk);
               bar(tugla[i].mix, tugla[i].miy, tugla[i].mix + 60, tugla[i].miy + 30);
               tugla[i].max = tugla[i].mix + 60;
               tugla[i].may = tugla[i].miy + 30;
               delay(100);
          }
     }
}
void dosya(int komut)
{
     FILE *dosya;

     if (komut == 1)
     {
          dosya = fopen("leveller.txt", "r");
          if (dosya == NULL)
               puts("leveller dosyasi acilmadi. !\n"), exit(1);
          a = 0;

          while (!feof(dosya))
          {
               fscanf(dosya, "%d %d %d %d", &tugla[a].ID, &tugla[a].mix, &tugla[a].miy, &tugla[a].renk);
               a++;
          }
     }
     else if (komut == 2)
     {
          dosya = fopen("en_iyi.txt", "w");
          if (dosya == NULL)
               puts("en_iyi dosyasi acilmadi. !\n"), exit(1);
     }

     fclose(dosya);
}
void parcala(int r)
{

     if (tugla[r].renk == 13)
     {
          setcolor(10);
          rectangle(tugla[r].mix, tugla[r].miy, tugla[r].max, tugla[r].may);
          tugla[r].renk = 10;
          puan = puan + 5;
     }

     else if (tugla[r].renk == 10)
     {
          setcolor(9);
          rectangle(tugla[r].mix, tugla[r].miy, tugla[r].max, tugla[r].may);
          tugla[r].renk = 9;
          puan = puan + 3;
     }
     else if (tugla[r].renk == 9)
     {
          setcolor(12);
          rectangle(tugla[r].mix, tugla[r].miy, tugla[r].max, tugla[r].may);
          tugla[r].renk = 12;
          puan = puan + 2;
     }
     else if (tugla[r].renk == 12)
     {
          setcolor(0);
          rectangle(tugla[r].mix, tugla[r].miy, tugla[r].max, tugla[r].may);
          tugla[r].renk = 0;
          tugla[r].mix = 0;
          tugla[r].miy = 0;
          tugla[r].max = 0;
          tugla[r].may = 0;
          puan = puan + 1;
          say++;
          oyun_kontrol(say);
     }
     puanlama();
}
void puanlama()
{
     char p[500];
     int p_x; /* Puan�n x Koordinatlar� */

     p_x = MaxX + 70;

     sprintf(p, "%d", puan);
     setcolor(11);
     settextstyle(1, 0, 5);
     if (puan < 10)
          outtextxy(p_x, 550, p);
     else if (puan < 100)
          outtextxy(p_x - 10, 550, p);
     else
          outtextxy(p_x - 20, 550, p);
}
void zaman()
{
     int n;
     char say[100];
     for (n = 10; n >= 0; n--)
     {

          sprintf(say, "%d", n);
          if (n > 99)
               settextstyle(1, 0, 5);
          else if (n > 9)
               settextstyle(1, 0, 7);
          else
               settextstyle(1, 0, 10);
          outtextxy((MaxX + 35), 120, say);
          bekle(1);
     }
}
void bekle(int zaman)
{
     clock_t son;

     son = clock() + zaman * CLK_TCK;

     while (clock() < son)
     {
     }
}

void canlar(int can)
{

     setcolor(13);
     setfillstyle(11, 11);
     fillellipse(MaxX + 45, 350, 20, 20);
     fillellipse(MaxX + 90, 350, 20, 20);
     fillellipse(MaxX + 135, 350, 20, 20);
     if (can > 3)
          fillellipse(MaxX + 90, 410, 20, 20);

     setcolor(0);
     setfillstyle(1, 0);
     if (can < 1)
     {
          fillellipse(MaxX + 45, 350, 20, 20);
          oyun_bitti();
     }
     if (can < 2)
          fillellipse(MaxX + 90, 350, 20, 20);
     if (can < 3)
          fillellipse(MaxX + 135, 350, 20, 20);
     if (can < 4)
          fillellipse(MaxX + 90, 410, 20, 20);
}

void baslangic_deger()
{
     setfillstyle(1, 0);
     bar(StartX - 50, StartY - 10, StartX + 50, StartY + 10);

     setcolor(0);
     setfillstyle(2, 0);
     fillellipse(StartX - 50, StartY, 10, 10);
     fillellipse(StartX + 50, StartY, 10, 10);

     StartX = (MaxX - bx) / 2;
     StartY = MaxY - 110;

     x = StartX;
     y = StartY - 25;
}
void oyun_bitti()
{

     readimagefile("son.jpg", 0, 0, getmaxx(), getmaxy());

     char p[500];
     sprintf(p, "%d", puan);
     setcolor(13);
     settextstyle(1, 0, 5);
     outtextxy(300, 425, p);

     while (!kbhit())
          ;
     closegraph();
}
void oyun_kontrol(int kutu)
{
     char bas;

     if (kutu == 76)
     {
          baslangic_deger();
          if (level = 1)
          {
               delay(100);
               readimagefile("bolum2.jpg", 0, 0, getmaxx(), getmaxy());
               delay(1000);
               outtextxy(550, 800, "BIR TUSA BASINIZ");
               bas = getch();
               cleardevice();
               ekran();
               blok(2);
          }
          else if (level = 2)
          {
               blok(3);
          }
     }
}
