#include <SDL2/SDL.h>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#ifndef __ANDROID__
// #include "bits/stdc++.h"
#endif
#define RED 0x00e03200     // R:224	G:50	B:0
#define ORANGE 0x00e0c000  // R:224	G:192	B:0
#define YELLOW 0x00f0f000  // R:224	G:224	B:0
#define GREEN 0x0000c000   // R:0		G:192	B:0
#define AQUA 0x0000c0c0    // R:0 		G:192 	B:192
#define BLUE 0x000000c0    // R:0 		G:0 	B:192
#define PURPLE 0x00c000c0  // R:192 	G:0 	B:192

#define MAXN 10000  // for array declaration

#ifndef SDL_SRCCOLORKEY
#define SDL_SRCCOLORKEY 1
#endif

using namespace std;

int MAXWIDTH = 1280;
int MAXHEIGHT = 960;
int height, width;
int block = 20;
int kb = 150;
int mouseon = 0;
bool mouseonanybutton = false;
int lr = 0;
int leftcolor = 5;
int rightcolor = 6;
int canchoosecolors[5];
int keyonwhichccc = 0;
int step = 0;
int mapsize = 0;
bool ai = false;
bool startlog = true;
bool cross = false;
bool pouring = false;
#ifdef __ANDROID__
bool os = true;
#else
bool os = false;  // 0=not android 1=android
#endif
bool anysave = false;
int COLOR[7] = {RED, ORANGE, YELLOW, GREEN, AQUA, BLUE, PURPLE};

// bool end=false;

Uint8 gamemap[MAXN][MAXN];
Uint8 poured[MAXN][MAXN];

fstream fout("./log.txt", ios::out | ios::trunc);
fstream fpout("./piclog.txt", ios::out | ios::trunc);

SDL_Rect rect;
SDL_Surface* surf;
SDL_Window* wind;
SDL_Surface* pic[2][7];
SDL_Surface* ico;
SDL_Surface* menu[2][3];
SDL_Surface* end0;
SDL_Surface* end1;
SDL_Surface* start;
SDL_Surface* contn;
SDL_Surface* home;
/*
int resizesurface(SDL_Surface* surf,int w,int h){
                SDL_Surface surf1= *surf;
                SDL_FreeSurface(surf);

}
*/



void varout() {
    if (startlog) {
        fout << "varout:" << endl;
        fout << "height:" << height << endl;
        fout << "width:" << width << endl;
        fout << "block:" << block << endl;
        fout << "kb:" << kb << endl;
        fout << "mouseon:" << mouseon << endl;
        fout << "lr:" << lr << endl;
        fout << "leftcolor:" << leftcolor << endl;
        fout << "rightcolor:" << rightcolor << endl;
        fout << "ai:" << ai << endl;
        fout << "mapsize:" << mapsize << endl;
        fout << "step:" << step << endl;
        fout << "gamemap:" << endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) fout << (int)gamemap[i][j] << ' ';
            fout << endl;
        }
        fout << endl;

        fout << "poured:" << endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) fout << (int)poured[i][j] << ' ';
            fout << endl;
        }
        fout << endl;
    }
}




void flashmap(SDL_Surface* surf, bool turn = false) {
    if (startlog) fout << endl << "do flashmap:" << endl;
    varout();
    // SDL_Surface*
    // ntsuf=SDL_CreateRGBSurfaceWithFormat(0,max(surf->w,surf->h),min(surf->w,surf->h),8,surf->format);
    SDL_Rect* rec = new SDL_Rect;
    switch (step) {
        case 0:
            SDL_FillRect(surf, NULL, 0x00ffffff);
            *rec = {MAXWIDTH / 2 - 150, MAXHEIGHT / 5 - 20, 300, 40};
            SDL_UpperBlit(menu[0][ai ? 1 : 0], NULL, surf, rec);
            *rec = {MAXWIDTH / 2 - 150, MAXHEIGHT / 5 * 2 - 20, 300, 40};
            SDL_UpperBlit(menu[1][mapsize], NULL, surf, rec);
            *rec = {MAXWIDTH / 2 - 150, MAXHEIGHT / 5 * 3 - 50, 300, 100};
            SDL_UpperBlit(start, NULL, surf, rec);
            if (anysave) {
                *rec = {MAXWIDTH / 2 - 150, MAXHEIGHT / 5 * 4 - 50, 300, 100};
                SDL_UpperBlit(contn, NULL, surf, rec);
            }
            break;
        case 1:
            SDL_FillRect(surf, NULL, 0x00ffffff);
            rec->w = block;
            rec->h = block;
            for (int yy = 0; yy < height; yy++) {
                for (int xx = 0; xx < width; xx++) {
                    rec->x = xx * block +
                             (MAXWIDTH - width * block - kb * 2) / 2 + kb;
                    rec->y =
                        yy * block + (MAXHEIGHT - 50 - block * height) / 2 + 50;
                    SDL_FillRect(surf, rec, (Uint32)COLOR[gamemap[yy][xx]]);
                }
            }
            rec->w = kb;
            rec->h = kb;
            for (int o = 0; o < 2; o++) {
                if (lr != o) continue;
                for (int i = 0; i < 7; i++) {
                    rec->x =
                        (((MAXWIDTH - width * block) / 2 - kb) / 2 < 0
                             ? 0
                             : ((MAXWIDTH - width * block) / 2 - kb) / 2) +
                        ((o == 1)
                             ? ((MAXWIDTH - width * block) / 2 + width * block)
                             : 0);

                    rec->y = ((MAXHEIGHT - 50) / 7 - kb) / 2 +
                             (MAXHEIGHT - 50) / 7 * i + 50;
                    if (i != leftcolor && i != rightcolor)
                        if (SDL_UpperBlit(
                                pic[(mouseon == i && mouseonanybutton) ? 1 : 0]
                                   [i],
                                NULL, surf, rec) < 0)
                            if (startlog)
                                fpout << "Blit bucket " << o << i
                                      << ((mouseon == i && lr == o) ? " big"
                                                                    : " small")
                                      << " error!" << endl
                                      << SDL_GetError() << endl;
                }
            }
            rec->w = 50;
            rec->h = 50;
            rec->x = MAXWIDTH / 2 - 25;
            rec->y = 0;
            if (SDL_UpperBlit(home, NULL, surf, rec) < 0)
                if (startlog)
                    fpout << "Blit home "
                          << " error!" << endl
                          << SDL_GetError() << endl;
            break;
    }

    SDL_UpdateWindowSurface(wind);
    varout();

    if (startlog) fout << "end flashmap" << endl;
}



void pour() {
    if (startlog) fout << endl << "do pour:" << endl << endl;
    varout();
    int bfsarray[MAXN][2];
    int l = 0, r = 0, num = 1;
    int fromcolor;
    if (lr == 0) {
        fromcolor = gamemap[height - 1][0];
        leftcolor = mouseon;
        bfsarray[0][0] = 0;
        bfsarray[0][1] = height - 1;
    } else {
        fromcolor = gamemap[0][width - 1];
        rightcolor = mouseon;
        bfsarray[0][0] = width - 1;
        bfsarray[0][1] = 0;
    }
    int pourcolor = mouseon;
    bool stopbfs = false;
    while (!stopbfs) {
        stopbfs = true;
        for (int i = l; i <= r; i++) {
            gamemap[bfsarray[i][1]][bfsarray[i][0]] = pourcolor;

            if (bfsarray[i][1] < height - 1) {
                if (gamemap[bfsarray[i][1] + 1][bfsarray[i][0]] == fromcolor) {
                    bfsarray[num][0] = bfsarray[i][0];
                    bfsarray[num][1] = bfsarray[i][1] + 1;
                    gamemap[bfsarray[num][1]][bfsarray[num][0]] = pourcolor;
                    if ((bfsarray[num][0] == 1 || bfsarray[num][0] == 0) &&
                        (bfsarray[num][1] == 1 || bfsarray[num][1] == 0)) {
                        cout << "catch error!!!at:  " << bfsarray[i][0] << '_'
                             << bfsarray[i][1] << endl;
                    }
                    num++;
                    stopbfs = false;
                }
            }
            if (bfsarray[i][1] > 0) {
                if (gamemap[bfsarray[i][1] - 1][bfsarray[i][0]] == fromcolor) {
                    bfsarray[num][0] = bfsarray[i][0];
                    bfsarray[num][1] = bfsarray[i][1] - 1;
                    gamemap[bfsarray[num][1]][bfsarray[num][0]] = pourcolor;
                    if ((bfsarray[num][0] == 1 || bfsarray[num][0] == 0) &&
                        (bfsarray[num][1] == 1 || bfsarray[num][1] == 0)) {
                        cout << "catch error!!!at:  " << bfsarray[i][0] << '_'
                             << bfsarray[i][1] << endl;
                    }
                    num++;
                    stopbfs = false;
                }
            }
            if (bfsarray[i][0] < width - 1) {
                if (gamemap[bfsarray[i][1]][bfsarray[i][0] + 1] == fromcolor) {
                    bfsarray[num][0] = bfsarray[i][0] + 1;
                    bfsarray[num][1] = bfsarray[i][1];
                    gamemap[bfsarray[num][1]][bfsarray[num][0]] = pourcolor;
                    if ((bfsarray[num][0] == 1 || bfsarray[num][0] == 0) &&
                        (bfsarray[num][1] == 1 || bfsarray[num][1] == 0)) {
                        cout << "catch error!!!at:  " << bfsarray[i][0] << '_'
                             << bfsarray[i][1] << endl;
                    }
                    num++;
                    stopbfs = false;
                }
            }
            if (bfsarray[i][0] > 0) {
                if (gamemap[bfsarray[i][1]][bfsarray[i][0] - 1] == fromcolor) {
                    bfsarray[num][0] = bfsarray[i][0] - 1;
                    bfsarray[num][1] = bfsarray[i][1];
                    gamemap[bfsarray[num][1]][bfsarray[num][0]] = pourcolor;
                    if ((bfsarray[num][0] == 1 || bfsarray[num][0] == 0) &&
                        (bfsarray[num][1] == 1 || bfsarray[num][1] == 0)) {
                        cout << "catch error!!!at:  " << bfsarray[i][0] << '_'
                             << bfsarray[i][1] << endl;
                    }
                    num++;
                    stopbfs = false;
                }
            }

            if (startlog)
                fout << (int)bfsarray[i][0] << '_' << (int)bfsarray[i][1]
                     << endl;
        }

        if (startlog)
            fout << endl << l << "__" << r << "  " << fromcolor << endl << endl;

        if (!stopbfs) {
            flashmap(surf);
            SDL_Delay(0x00000032);
        }

        l = r + 1;
        r = num - 1;
        /*
        for(int i=0;i<height;i++){           //for test
                        for(int j=0;j<width;j++)
                                        cout<<(int)gamemap[i][j];
                        cout<<endl;
        }
        */
    }

    if (startlog) fout << endl << "end pour" << endl << endl;
}
int aiplay() {
    int pourget[7];
    for (int c = 0; c < 7; c++) {
        if (c == leftcolor || c == rightcolor) continue;
        Uint8 map[MAXN][MAXN];
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++) map[i][j] = gamemap[i][j];

        int bfsarray[MAXN][2];
        int l = 0, r = 0, num = 1;
        int fromcolor = map[0][width - 1];
        int pourcolor = c;
        bfsarray[0][0] = width - 1;
        bfsarray[0][1] = 0;
        bool stopbfs = false;
        while (!stopbfs) {
            stopbfs = true;
            for (int i = l; i <= r; i++) {
                map[bfsarray[i][1]][bfsarray[i][0]] = pourcolor;

                if (bfsarray[i][1] < height - 1) {
                    if (map[bfsarray[i][1] + 1][bfsarray[i][0]] == fromcolor) {
                        bfsarray[num][0] = bfsarray[i][0];
                        bfsarray[num][1] = bfsarray[i][1] + 1;
                        map[bfsarray[num][1]][bfsarray[num][0]] = pourcolor;
                        if ((bfsarray[num][0] == 1 || bfsarray[num][0] == 0) &&
                            (bfsarray[num][1] == 1 || bfsarray[num][1] == 0)) {
                            cout << "catch error!!!at:  " << bfsarray[i][0]
                                 << '_' << bfsarray[i][1] << endl;
                        }
                        num++;
                        stopbfs = false;
                    }
                }
                if (bfsarray[i][1] > 0) {
                    if (map[bfsarray[i][1] - 1][bfsarray[i][0]] == fromcolor) {
                        bfsarray[num][0] = bfsarray[i][0];
                        bfsarray[num][1] = bfsarray[i][1] - 1;
                        map[bfsarray[num][1]][bfsarray[num][0]] = pourcolor;
                        if ((bfsarray[num][0] == 1 || bfsarray[num][0] == 0) &&
                            (bfsarray[num][1] == 1 || bfsarray[num][1] == 0)) {
                            cout << "catch error!!!at:  " << bfsarray[i][0]
                                 << '_' << bfsarray[i][1] << endl;
                        }
                        num++;
                        stopbfs = false;
                    }
                }
                if (bfsarray[i][0] < width - 1) {
                    if (map[bfsarray[i][1]][bfsarray[i][0] + 1] == fromcolor) {
                        bfsarray[num][0] = bfsarray[i][0] + 1;
                        bfsarray[num][1] = bfsarray[i][1];
                        map[bfsarray[num][1]][bfsarray[num][0]] = pourcolor;
                        if ((bfsarray[num][0] == 1 || bfsarray[num][0] == 0) &&
                            (bfsarray[num][1] == 1 || bfsarray[num][1] == 0)) {
                            cout << "catch error!!!at:  " << bfsarray[i][0]
                                 << '_' << bfsarray[i][1] << endl;
                        }
                        num++;
                        stopbfs = false;
                    }
                }
                if (bfsarray[i][0] > 0) {
                    if (map[bfsarray[i][1]][bfsarray[i][0] - 1] == fromcolor) {
                        bfsarray[num][0] = bfsarray[i][0] - 1;
                        bfsarray[num][1] = bfsarray[i][1];
                        map[bfsarray[num][1]][bfsarray[num][0]] = pourcolor;
                        if ((bfsarray[num][0] == 1 || bfsarray[num][0] == 0) &&
                            (bfsarray[num][1] == 1 || bfsarray[num][1] == 0)) {
                            cout << "catch error!!!at:  " << bfsarray[i][0]
                                 << '_' << bfsarray[i][1] << endl;
                        }
                        num++;
                        stopbfs = false;
                    }
                }
            }
            l = r + 1;
            r = num - 1;
        }

        l = 0, r = 0, num = 1;
        bfsarray[0][0] = width - 1;
        bfsarray[0][1] = 0;
        fromcolor = map[0][width - 1];
        pourcolor = 7;
        stopbfs = false;
        while (!stopbfs) {
            stopbfs = true;
            for (int i = l; i <= r; i++) {
                map[bfsarray[i][1]][bfsarray[i][0]] = pourcolor;

                if (bfsarray[i][1] < height - 1) {
                    if (map[bfsarray[i][1] + 1][bfsarray[i][0]] == fromcolor) {
                        bfsarray[num][0] = bfsarray[i][0];
                        bfsarray[num][1] = bfsarray[i][1] + 1;
                        map[bfsarray[num][1]][bfsarray[num][0]] = pourcolor;
                        if ((bfsarray[num][0] == 1 || bfsarray[num][0] == 0) &&
                            (bfsarray[num][1] == 1 || bfsarray[num][1] == 0)) {
                            cout << "catch error!!!at:  " << bfsarray[i][0]
                                 << '_' << bfsarray[i][1] << endl;
                        }
                        num++;
                        stopbfs = false;
                    }
                }
                if (bfsarray[i][1] > 0) {
                    if (map[bfsarray[i][1] - 1][bfsarray[i][0]] == fromcolor) {
                        bfsarray[num][0] = bfsarray[i][0];
                        bfsarray[num][1] = bfsarray[i][1] - 1;
                        map[bfsarray[num][1]][bfsarray[num][0]] = pourcolor;
                        if ((bfsarray[num][0] == 1 || bfsarray[num][0] == 0) &&
                            (bfsarray[num][1] == 1 || bfsarray[num][1] == 0)) {
                            cout << "catch error!!!at:  " << bfsarray[i][0]
                                 << '_' << bfsarray[i][1] << endl;
                        }
                        num++;
                        stopbfs = false;
                    }
                }
                if (bfsarray[i][0] < width - 1) {
                    if (map[bfsarray[i][1]][bfsarray[i][0] + 1] == fromcolor) {
                        bfsarray[num][0] = bfsarray[i][0] + 1;
                        bfsarray[num][1] = bfsarray[i][1];
                        map[bfsarray[num][1]][bfsarray[num][0]] = pourcolor;
                        if ((bfsarray[num][0] == 1 || bfsarray[num][0] == 0) &&
                            (bfsarray[num][1] == 1 || bfsarray[num][1] == 0)) {
                            cout << "catch error!!!at:  " << bfsarray[i][0]
                                 << '_' << bfsarray[i][1] << endl;
                        }
                        num++;
                        stopbfs = false;
                    }
                }
                if (bfsarray[i][0] > 0) {
                    if (map[bfsarray[i][1]][bfsarray[i][0] - 1] == fromcolor) {
                        bfsarray[num][0] = bfsarray[i][0] - 1;
                        bfsarray[num][1] = bfsarray[i][1];
                        map[bfsarray[num][1]][bfsarray[num][0]] = pourcolor;
                        if ((bfsarray[num][0] == 1 || bfsarray[num][0] == 0) &&
                            (bfsarray[num][1] == 1 || bfsarray[num][1] == 0)) {
                            cout << "catch error!!!at:  " << bfsarray[i][0]
                                 << '_' << bfsarray[i][1] << endl;
                        }
                        num++;
                        stopbfs = false;
                    }
                }
            }

            // fout<<endl<<l<<"__"<<r<<"  "<<fromcolor<<endl<<endl;
            l = r + 1;
            r = num - 1;
            /*
            for(int i=0;i<height;i++){           //for test
                            for(int j=0;j<width;j++)
                                            cout<<(int)map[i][j];
                            cout<<endl;
            }
            */
        }
        pourget[c] = num;
    }
    int res = 0;
    while (res == leftcolor || res == rightcolor) res++;
    for (int i = 1; i < 7; i++) {
        if (i == leftcolor || i == rightcolor) continue;
        if (pourget[i] > pourget[res]) res = i;
    } /*
     int res1=0;
     while(res1==leftcolor||res1==rightcolor||res1==res)res1++;
     for(int i=0;i<7;i++){
                     if(i==leftcolor||i==rightcolor||i==res)continue;
                     if(pourget[i]>pourget[res1])res1=i;
     }*/
    return res;
}
// bfspoured计算哪些方块是被左边玩家倒了油漆的，哪些是被右边到过油漆的，哪些没有被到过油漆
void bfspoured() {
    int fromcolor;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) poured[i][j] = 0;
    }
    for (int LR = 0; LR <= 1; LR++) {
        int l = 0, r = 0, num = 1;
        int bfsarray[MAXN][2];
        // cout<<LR<<endl;	//for test
        if (LR == 0) {
            fromcolor = gamemap[height - 1][0];
            bfsarray[0][0] = 0;
            bfsarray[0][1] = height - 1;
        } else {
            fromcolor = gamemap[0][width - 1];
            bfsarray[0][0] = width - 1;
            bfsarray[0][1] = 0;
        }
        bool stopbfs = false;
        while (!stopbfs) {
            stopbfs = true;
            for (int i = l; i <= r; i++) {
                if (LR == 0) {
                    poured[bfsarray[i][1]][bfsarray[i][0]] = 1;
                } else {
                    poured[bfsarray[i][1]][bfsarray[i][0]] = 2;
                }

                if (bfsarray[i][1] < height - 1) {
                    if (gamemap[bfsarray[i][1] + 1][bfsarray[i][0]] ==
                            fromcolor &&
                        poured[bfsarray[i][1] + 1][bfsarray[i][0]] == 0) {
                        bfsarray[num][0] = bfsarray[i][0];
                        bfsarray[num][1] = bfsarray[i][1] + 1;
                        if ((bfsarray[num][0] == 1 || bfsarray[num][0] == 0) &&
                            (bfsarray[num][1] == 1 || bfsarray[num][1] == 0)) {
                            cout << "catch error!!!at:  " << bfsarray[i][0]
                                 << '_' << bfsarray[i][1] << endl;
                        }
                        num++;
                        stopbfs = false;
                    }
                }
                if (bfsarray[i][1] > 0) {
                    if (gamemap[bfsarray[i][1] - 1][bfsarray[i][0]] ==
                            fromcolor &&
                        poured[bfsarray[i][1] - 1][bfsarray[i][0]] == 0) {
                        bfsarray[num][0] = bfsarray[i][0];
                        bfsarray[num][1] = bfsarray[i][1] - 1;
                        if ((bfsarray[num][0] == 1 || bfsarray[num][0] == 0) &&
                            (bfsarray[num][1] == 1 || bfsarray[num][1] == 0)) {
                            cout << "catch error!!!at:  " << bfsarray[i][0]
                                 << '_' << bfsarray[i][1] << endl;
                        }
                        num++;
                        stopbfs = false;
                    }
                }
                if (bfsarray[i][0] < width - 1) {
                    if (gamemap[bfsarray[i][1]][bfsarray[i][0] + 1] ==
                            fromcolor &&
                        poured[bfsarray[i][1]][bfsarray[i][0] + 1] == 0) {
                        bfsarray[num][0] = bfsarray[i][0] + 1;
                        bfsarray[num][1] = bfsarray[i][1];
                        if ((bfsarray[num][0] == 1 || bfsarray[num][0] == 0) &&
                            (bfsarray[num][1] == 1 || bfsarray[num][1] == 0)) {
                            cout << "catch error!!!at:  " << bfsarray[i][0]
                                 << '_' << bfsarray[i][1] << endl;
                        }
                        num++;
                        stopbfs = false;
                    }
                }
                if (bfsarray[i][0] > 0) {
                    if (gamemap[bfsarray[i][1]][bfsarray[i][0] - 1] ==
                            fromcolor &&
                        poured[bfsarray[i][1]][bfsarray[i][0] - 1] == 0) {
                        bfsarray[num][0] = bfsarray[i][0] - 1;
                        bfsarray[num][1] = bfsarray[i][1];
                        if ((bfsarray[num][0] == 1 || bfsarray[num][0] == 0) &&
                            (bfsarray[num][1] == 1 || bfsarray[num][1] == 0)) {
                            cout << "catch error!!!at:  " << bfsarray[i][0]
                                 << '_' << bfsarray[i][1] << endl;
                        }
                        num++;
                        stopbfs = false;
                    }
                }
            }
            l = r + 1;
            r = num - 1;
        }
    }
}
long sum() {
    if (startlog) fout << "do sum:" << endl;
    varout();
    long a = 0, b = 0;
    bfspoured();
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (poured[i][j] == 1) {
                a++;
            } else if (poured[i][j] == 2) {
                b++;
            }
        }
    }
    a = a * 1000;
    a += b;
    varout();
    if (startlog) fout << endl << "result:" << a << endl;
    return a;
}
bool decidetoend() {
    if (startlog) fout << "do decidetoend:" << endl;
    varout();
    long a, b;
    bool res;
    long area = height * width;
    a = sum();
    b = a % 1000;
    a = a / 1000;
    res = (a >= area / 2 || b >= area / 2);
    varout();
    if (startlog) fout << endl << "result:" << res << endl;
    return res;
}
/*�浵��ʽһ��Ϊ��
                anysave(��
                ai(�Ƿ��˻���ս��1��0��
                height(��ͼ�߶ȣ�
                width����ͼ���ȣ�
                leftcolor��������ɫ��
                rightcolor��������ɫ��
                lr(�ֵ���߻����ұߣ�0��ߣ�1�ұߣ�
                pouring(�Ƿ����ڵ����ᣬ1��0��
*/
// （此段已变为锟斤拷）
void save() {
    ofstream s("./save.txt", ios::out | ios::trunc);
    s << anysave;
    s << ' ' << ai << ' ' << height << ' ' << width << ' ' << leftcolor << ' '
      << rightcolor << ' ' << lr << ' ' << pouring << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            s << (int)gamemap[i][j] << ' ';
        }
        s << endl;
    }
    s.close();
}
int load() {
    fout.open("./log.txt", ios::in);
    int a;
    fout >> a;
    startlog = (a == 1);
    cout << startlog << ' ' << a << endl;
    fout.close();
    fout.open("./log.txt", ios::out | ios::trunc);
    fout << a << endl;
    int b;
    ifstream s("./save.txt", ios::in);
    s >> anysave;
    if (anysave == 0) return 0;
    s >> ai >> height >> width >> leftcolor >> rightcolor >> lr >> pouring;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            s >> b;
            gamemap[i][j] = b;
        }
    }
    s.close();
    return 1;
}
int spreadmap() {
    lr = 0;
    switch (mapsize) {
        case 0:
            height = 20;
            break;
        case 1:
            height = 40;
            break;
        case 2:
            height = 70;
            break;
    }

    block = (MAXHEIGHT - 50) / height;
    width = (MAXWIDTH - (kb * 2)) / block;

    srand((int)time(NULL));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            gamemap[i][j] = rand() % 7;
            poured[i][j] = 0;
            // if(i>=height-2&&i<=height-1&&j>=0&&j<=1)gamemap[i][j]=COLOR[2];
        }
    }
    gamemap[height - 1][0] = leftcolor;
    gamemap[0][width - 1] = rightcolor;
    poured[height - 1][0] = 1;
    poured[0][width - 1] = 2;
    return 0;
}




int main(int argc, char* argv[]) {
    int ch;
    SDL_Init(SDL_INIT_EVERYTHING);
    bool end = false;
    wind = SDL_CreateWindow(
        "POURWAR", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 700,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
    surf = SDL_GetWindowSurface(wind);
    SDL_FillRect(surf, NULL, 0x00ffffff);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 7; j++) {
            string str = "./assets/buckets/bucket";
            str += (char)(i + 48);
            str += (char)(j + 48);
            str += ".bmp";
            constexpr int chlen = 100;
            char ch[chlen];
            for (int o = 0; o < str.length(); o++) {
                ch[o] = str[o];
            }
            ch[str.length()] = '\0';
            pic[i][j] = SDL_LoadBMP(ch);
            SDL_SetColorKey(pic[i][j], 1,
                            SDL_MapRGB(pic[i][j]->format, 0xff, 0xff, 0xff));
            if (pic[i][j] == NULL)
                fpout << "load bucket " << i << j << " error!" << endl
                      << SDL_GetError() << endl;
        }
    }
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++) {
            string str2 = "./assets/menu/";
            str2 += (char)(i + 48);
            str2 += (char)(j + 48);
            str2 += ".bmp";
            char ch2[50];
            for (int o = 0; o < 50; o++) {
                ch2[o] = ' ';
            }
            // cout<<ch2<<endl;
            for (int o = 0; o < str2.length(); o++) {
                ch2[o] = str2[o];
            }
            ch2[str2.length()] = '\0';
            menu[i][j] = SDL_LoadBMP(ch2);
            // cout<<str<<" "<<ch2<<endl;
            SDL_SetColorKey(menu[i][j], 1,
                            SDL_MapRGB(menu[i][j]->format, 0xff, 0xff, 0xff));
            if (menu[i][j] == NULL)
                fpout << "load menu " << i << j << " error!" << endl
                      << SDL_GetError() << endl;
        }
    end0 = SDL_LoadBMP("./assets/end/0.bmp");
    if (end0 == NULL)
        fpout << "load end0 error!" << endl << SDL_GetError() << endl;
    SDL_SetColorKey(end0, SDL_SRCCOLORKEY, 0x00ffffff);

    end1 = SDL_LoadBMP("./assets/end/1.bmp");
    if (end1 == NULL)
        fpout << "load end1 error!" << endl << SDL_GetError() << endl;
    SDL_SetColorKey(end1, SDL_SRCCOLORKEY, 0x00ffffff);

    start = SDL_LoadBMP("./assets/start.bmp");
    if (start == NULL)
        fpout << "load start error!" << endl << SDL_GetError() << endl;
    SDL_SetColorKey(start, SDL_SRCCOLORKEY, 0x00ffffff);

    contn = SDL_LoadBMP("./assets/continue.bmp");
    if (contn == NULL)
        fpout << "load contn error!" << endl << SDL_GetError() << endl;
    SDL_SetColorKey(contn, SDL_SRCCOLORKEY, 0x00ffffff);

    home = SDL_LoadBMP("./assets/home.bmp");
    if (home == NULL)
        fpout << "load home error!" << endl << SDL_GetError() << endl;
    SDL_SetColorKey(home, SDL_SRCCOLORKEY, 0x00ffffff);

    ico = SDL_LoadBMP("./assets/icon3.bmp");
    if (ico == NULL)
        fpout << "load icon error!" << endl << SDL_GetError() << endl;

    SDL_SetWindowIcon(wind, ico);

    SDL_GetWindowSize(wind, &MAXWIDTH, &MAXHEIGHT);

    anysave = load();

S:
    step = 0;
    end = false;
    while (!end) {
        SDL_GetWindowSize(wind, &MAXWIDTH, &MAXHEIGHT);
        SDL_Delay(5);
        SDL_Event menuEvent;
        while (SDL_PollEvent(&menuEvent) != 0) {
            surf = SDL_GetWindowSurface(wind);
            SDL_GetWindowSize(wind, &MAXWIDTH, &MAXHEIGHT);
            SDL_FillRect(surf, NULL, 0x00ffffff);
            flashmap(surf);
            if (menuEvent.type == SDL_MOUSEBUTTONDOWN) {
                if (menuEvent.button.x > (MAXWIDTH - 300) / 2 &&
                    menuEvent.button.x < (MAXWIDTH - 300) / 2 + 300) {
                    if (menuEvent.button.y > MAXHEIGHT / 5 - 20 &&
                        menuEvent.button.y < MAXHEIGHT / 5 + 20) {
                        ai = !ai;
                    }
                    if (menuEvent.button.y > MAXHEIGHT / 5 * 2 - 20 &&
                        menuEvent.button.y < MAXHEIGHT / 5 * 2 + 20) {
                        mapsize = (++mapsize) % 3;
                    }
                    if (menuEvent.button.y > MAXHEIGHT / 5 * 3 - 50 &&
                        menuEvent.button.y < MAXHEIGHT / 5 * 3 + 50) {
                        end = true;
                        spreadmap();
                        save();
                    }
                    if (menuEvent.button.y > MAXHEIGHT / 5 * 4 - 50 &&
                        menuEvent.button.y < MAXHEIGHT / 5 * 4 + 50 &&
                        anysave) {
                        end = true;
                    }
                }
            } else if (menuEvent.type == SDL_QUIT) {
                end = true;
                cross = true;
                // cout<<"exi";
            }
        }
    }
    if (cross) {
        for (int o = 0; o < 2; o++) {
            for (int i = 0; i < 7; i++) {
                SDL_FreeSurface(pic[o][i]);
            }
        }
        for (int o = 0; o < 2; o++) {
            for (int i = 0; i < 3; i++) {
                SDL_FreeSurface(menu[o][i]);
            }
        }
        SDL_FreeSurface(ico);
        SDL_FreeSurface(surf);
        SDL_DestroyWindow(wind);
        SDL_Quit();
        fout.close();
        fpout.close();
        return 0;
    }

maingame:
    step = 1;

    cout << 22 << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            poured[i][j] = 0;
        }
    }
    poured[height - 1][0] = 1;
    poured[0][width - 1] = 2;
    SDL_Rect rec;
    SDL_FillRect(surf, NULL, 0x00ffffff);
    for (int i = 0; i < 2; i++) {
        rec = {MAXWIDTH / 2 - 300 / 2, MAXHEIGHT / 3 * (i + 1)};
    }
    bool over = false;
    save();
    flashmap(surf);
    int mousex, mousey;
    end = false;
    cross = false;
    while (!end) {
        // cout<<ch<<endl;
        bool get = false;
        SDL_Event gameEvent;
        while (SDL_PollEvent(&gameEvent) != 0) {
            surf = SDL_GetWindowSurface(wind);
            SDL_GetWindowSize(wind, &MAXWIDTH, &MAXHEIGHT);
            block = min((MAXHEIGHT - 50) / height, (MAXWIDTH - kb * 2) / width);
            switch (gameEvent.type) {
                case SDL_QUIT:
                    end = true;
                    cross = true;
                    break;
                case SDL_MOUSEMOTION:
                    mousex = gameEvent.motion.x;
                    mousey = gameEvent.motion.y;
                    if ((lr &&
                         mousex > MAXWIDTH - (MAXWIDTH - block * width) / 2 &&
                         !ai) ||
                        (!lr && mousex < (MAXWIDTH - block * width) / 2)) {
                        mouseon = mousey / (MAXHEIGHT / 7);
                        mouseonanybutton = true;
                    } else
                        mouseonanybutton = false;
                    // cout<<"motion:"<<mousex<<" "<<mousey<<" "<<mouseon<<endl;
                    flashmap(surf);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    mousex = gameEvent.button.x;
                    mousey = gameEvent.button.y;

                    if (mousex > (MAXWIDTH / 2) - 25 &&
                        mousex < (MAXWIDTH / 2) + 25 && mousey < 50) {
                        end = true;
                        break;
                    }
                    if (ai) {
                        if (!lr && mousex < (MAXWIDTH - block * width) / 2 &&
                            mousey / (MAXHEIGHT / 7) != leftcolor &&
                            mousey / (MAXHEIGHT / 7) != rightcolor) {
                            mouseon = mousey / (MAXHEIGHT / 7);
                            mouseonanybutton = true;
                            save();
                            pouring = true;
                            over = end = decidetoend();
                            if (end) break;
                        } else
                            mouseonanybutton = false;
                    } else if ((lr &&
                                mousex >
                                    MAXWIDTH - (MAXWIDTH - block * width) / 2 &&
                                mousey / (MAXHEIGHT / 7) != rightcolor &&
                                mousey / (MAXHEIGHT / 7) != leftcolor) ||
                               (!lr &&
                                mousex < (MAXWIDTH - block * width) / 2 &&
                                mousey / (MAXHEIGHT / 7) != leftcolor &&
                                mousey / (MAXHEIGHT / 7) != rightcolor)) {
                        mouseon = mousey / (MAXHEIGHT / 7);
                        mouseonanybutton = true;
                        pouring = true;
                        save();
                        over = end = decidetoend();
                        if (end) break;
                    } else
                        mouseonanybutton = false;
                    break;
            }
        }
        if (pouring) {
            if (ai) {
                if (!lr) {
                    pour();
                    lr = 1;
                } else {
                    flashmap(surf);
                    SDL_Delay(700);
                    mouseon = aiplay();
                    SDL_Delay(700);
                    pour();
                    lr = 0;
                    pouring = false;
                }
            } else {
                pour();
                lr = (lr == 0) ? 1 : 0;
                flashmap(surf);
                pouring = false;
            }
        }
        if (end) break;
        flashmap(surf);
    }
    anysave = true;
    if (cross) goto destructing;
    if (!over) cout << "not over";
    if (!over) goto S;
    long a, b;
    a = sum();
    b = a % 1000;
    a = a / 1000;
    rect = {(MAXWIDTH - 300) / 2, (MAXHEIGHT - 200) / 2, 300, 200};
    if (a > b)
        SDL_UpperBlit(end0, NULL, surf, &rect);
    else
        SDL_UpperBlit(end1, NULL, surf, &rect);
    SDL_UpdateWindowSurface(wind);
    end = false;
    cross = false;
    while (!end) {
        SDL_Event endEvent;
        while (SDL_PollEvent(&endEvent) != 0) {
            if (endEvent.type == SDL_MOUSEBUTTONDOWN) {
                end = true;
            } else if (endEvent.type == SDL_QUIT) {
                end = true;
                cross = true;
                // cout<<"exi";
            }
        }
    }
    anysave = false;
    goto S;
destructing:
    for (int o = 0; o < 2; o++) {
        for (int i = 0; i < 7; i++) {
            SDL_FreeSurface(pic[o][i]);
        }
    }
    for (int o = 0; o < 2; o++) {
        for (int i = 0; i < 3; i++) {
            SDL_FreeSurface(menu[o][i]);
        }
    }
    SDL_FreeSurface(ico);
    SDL_FreeSurface(surf);
    SDL_DestroyWindow(wind);

    // std::string result_text;
    // result_text = "左下方倒了 " + std::to_string(a) + " 格油漆\n";
    // result_text += "右上方倒了 " + std::to_string(b) + " 格油漆\n\n";

    // if (a > b) {
    //     result_text += "左下玩家获胜！";
    // } else if (a < b) {
    //     result_text += "右上玩家获胜!";
    // } else {
    //     result_text += "恭喜你们，打平了！";
    // }
    // // SDL_ShowSimpleMessageBox(flags, title, message, window)
    // SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "游戏结束",
    //                          result_text.c_str(),
    //                          NULL);  // 最后一个参数是父窗口，NULL 即可

    SDL_Quit();
    fout.close();
    fpout.close();
    return 0;
}