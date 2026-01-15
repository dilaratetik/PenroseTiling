#include "Image.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

const float pi = 3.14f;
float altinOran = 1.61f;
float temp = altinOran * 2;

struct Point {
    float x;
    float y;

    Point operator+(Point diger) {
        Point sonuc;
        sonuc.x = x + diger.x;
        sonuc.y = y + diger.y;
        return sonuc;
    }

    Point operator-(Point diger)
    {
        Point sonuc;
        sonuc.x = x - diger.x;
        sonuc.y = y - diger.y;
        return sonuc;
    }

    Point operator*(float sayi) {
        Point sonuc;
        sonuc.x = x * sayi;
        sonuc.y = y * sayi;
        return sonuc;
    }

    Point operator/(float sayi)
    {
        Point sonuc;
        sonuc.x = x / sayi;
        sonuc.y = y / sayi;
        return sonuc;
    }

    Point() {
        x = 0;
        y = 0;
    }
};

struct Color {
    int r, g, b;

    Color() {
        r = 0;
        g = 0;
        b = 0;
    }
};

/*Color gradyan(Color c1, Color c2, float t) {
    Color sonuc;
    sonuc.r = c1.r * t + c2.r * (1 - t);
    sonuc.g = c1.g * t + c2.g * (1 - t);
    sonuc.b = c1.b * t + c2.b * (1 - t);
    return sonuc;
} */

struct Triangle {
    int tip; //0 buyuk, 1 kucuk
    Point A, B, C, D;

    Triangle() {
        tip = 0;
    }

    Triangle(int t) {
        tip = t;
    }
};

struct Rhombus {
    int tip;
    Point A, B, C, D;

    Rhombus() {
        tip = 0;
    }

    Rhombus(int t) {
        tip = t;
    }
};

struct Edge {
    int y_min;
    int y_max;
    float x;
    float m;

    Edge() {
        y_min = 0;
        y_max = 0;
        x = 0;
        m = 0;
    }
};

Rhombus cevir(Triangle u) {
    Rhombus d;
    d.tip = u.tip;
    d.A = u.A;
    d.B = u.B;
    d.C = u.C;
    d.D = u.B + u.C - u.A; //paralelkenar formulu
    return d;
}

//buyuk ucgenleri 1 buyuk 1 kucuk ucgene bolucez
//kucuk ucgenleri 1 buyuk 2 kucuk ucgene bolucez
vector<Triangle> parcala(vector<Triangle> ucgenler) {
    vector<Triangle> yeniListem;
    int sayac = 0;

    for (int i = 0; i < ucgenler.size(); i++) {
        Triangle u = ucgenler[i];
        sayac++;

        if (u.tip == 0) { //buyuk ucgen bolumu: 1 buyuk 1 kucuk ucgen
            Point p = u.A + (u.B - u.A) / altinOran;

            //1. parca buyuk ucgen
            Triangle t1; //c,p,b
            t1.tip = 0;
            t1.A = u.C;
            t1.B = p;
            t1.C = u.B;

            //2. parca kucuk ucgen
            Triangle t2; //p,c,a
            t2.tip = 1;
            t2.A = p;
            t2.B = u.C;
            t2.C = u.A;

            yeniListem.push_back(t1);
            yeniListem.push_back(t2);
        }
        else { //kucuk ucgen bolumu: 1 buyuk 2 kucuk ucgen
            Point q = u.B + (u.A - u.B) / altinOran;
            Point r = u.B + (u.C - u.B) / altinOran;

            //1. parca kucuk ucgen
            Triangle t1; //r,c,a
            t1.tip = 1;
            t1.A = r;
            t1.B = u.C;
            t1.C = u.A;

            //2. parca kucuk ucgen
            Triangle t2; //q,r,b
            t2.tip = 1;
            t2.A = q;
            t2.B = r;
            t2.C = u.B;

            //3. parca buyuk ucgen 
            Triangle t3; //r,q,a
            t3.tip = 0;
            t3.A = r;
            t3.B = q;
            t3.C = u.A;

            yeniListem.push_back(t1);
            yeniListem.push_back(t2);
            yeniListem.push_back(t3);
        }
    }
    return yeniListem;
}

vector<Triangle> baslangic(float g, float y, float r) {
    vector<Triangle> liste;
    float yaricap = r;
    Point merkez;
    merkez.x = g / 2.0f;
    merkez.y = y / 2.0f;

    for (int i = 0; i < 10; i++) { //10 üçgen oluþturuyorum, 36 derece
       
        float aci1 = (2 * i - 1) * 18.0f;
        float aci2 = (2 * i + 1) * 18.0f;

        float radyan1 = aci1 * (3.14f / 180.0f);
        float radyan2 = aci2 * (3.14f / 180.0f);

        Point B, C;
        B.x = merkez.x + yaricap * cos(radyan1);
        B.y = merkez.y + yaricap * sin(radyan1);

        C.x = merkez.x + yaricap * cos(radyan2);
        C.y = merkez.y + yaricap * sin(radyan2);

        Triangle yeni;
        yeni.tip = 0;
        yeni.A = merkez;
        yeni.B = B;
        yeni.C = C;

        if (i % 2 == 0)
        {
            yeni.B = C;
            yeni.C = B;
        }

        liste.push_back(yeni);
    }
    return liste;
}

void putPixel(ColorImage& img, int x, int y, Color c) {
    int w = img.GetWidth();
    int h = img.GetHeight();

    if (x >= 0 && x < w) {
        if (y >= 0 && y < h) {
            img(x, y).r = c.r;
            img(x, y).g = c.g;
            img(x, y).b = c.b;
        }
    }
}

void dda(ColorImage& img, Point p1, Point p2, Color c) {

    int x1 = (int)p1.x;
    int y1 = (int)p1.y;
    int x2 = (int)p2.x;
    int y2 = (int)p2.y;

    float dx = x2 - x1;
    float dy = y2 - y1;

    float adim;

    if (abs(dx) > abs(dy)) {
        adim = abs(dx);
    }
    else {
        adim = abs(dy);
    }

    float xartis = dx / adim;
    float yartis = dy / adim;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= (int)adim; i++) {
        putPixel(img, (int)x, (int)y, c);
        x = x + xartis;
        y = y + yartis;
    }
}

vector<Edge> activeList(vector<Point> points) {
    vector<Edge> edgeTablo;
    int n = points.size();

    for (int i = 0; i < n; i++) {
        Point p1 = points[i];
        Point p2 = points[(i + 1) % n];

        if ((int)p1.y == (int)p2.y) {
            continue;
        }

        Edge e;
        float dx;
        float dy;

        if (p1.y < p2.y) {
            dx = p2.x - p1.x;
            dy = p2.y - p1.y;

            e.x = p1.x;
            e.y_min = (int)p1.y;
            e.y_max = (int)p2.y;
        }
        else {
            dx = p1.x - p2.x;
            dy = p1.y - p2.y;

            e.x = p2.x;
            e.y_min = (int)p2.y;
            e.y_max = (int)p1.y;
        }

        e.m = dx / dy;
        edgeTablo.push_back(e);
    }

    return edgeTablo;
}

void ucgenBoya(ColorImage& img, Point v1, Point v2, Point v3, Color c) {
    vector<Point> noktalar;
    noktalar.push_back(v1);
    noktalar.push_back(v2);
    noktalar.push_back(v3);

    vector<Edge> kenarlar = activeList(noktalar);

    int minY = v1.y;
    if (v2.y < minY) {
        minY = v2.y;
    }
    if (v3.y < minY) {
        minY = v3.y;
    }

    int maxY = v1.y;
    if (v2.y > maxY) {
        maxY = v2.y;
    }
    if (v3.y > maxY) {
        maxY = v3.y;
    }

    for (int y = minY; y < maxY; y++) {
        float x_kesisimi[2];
        int kesisimSayisi = 0;

        for (int i = 0; i < kenarlar.size(); i++) {
             if (y >= kenarlar[i].y_min && y < kenarlar[i].y_max) {
                 x_kesisimi[kesisimSayisi] = kenarlar[i].x;
                 kesisimSayisi++;

                 if (kesisimSayisi >= 2) break;
            }
        }

        if (kesisimSayisi == 2) {
            float baslangic = x_kesisimi[0];
            float bitis = x_kesisimi[1];

            if (baslangic > bitis) {
                float gecici = baslangic;
                baslangic = bitis;
                bitis = gecici;
            }

            for (int x = baslangic; x <= bitis; x++) {
                putPixel(img, x, y, c);
            }
        }

        for (int i = 0; i < kenarlar.size(); i++) {
            if (y >= kenarlar[i].y_min && y < kenarlar[i].y_max) {
                kenarlar[i].x = kenarlar[i].x + kenarlar[i].m;
            }
        }
    }
}

void dortgenBoya(ColorImage& img, Point p1, Point p2, Point p3, Point p4, Color c) {
    ucgenBoya(img, p1, p2, p3, c);
    ucgenBoya(img, p3, p4, p1, c);
}

int main() {

    srand(time(0));

    int secim;
    int adim_limiti;

    cout << "--Penrose Tiling Project--\n";
    cout << "1 - Robinson's Triangle mode (Pink)\n";
    cout << "2 - Robinson's Triangle mode (B&W)\n";
    cout << "3 - Rhombus mode (Blue)\n";
    cout << "4 - Rhombus mode (B&W)\n";
    cout << "5 - Phone wallpaper mode with surprise color! \n";
    cout << "Choose: ";
    cin >> secim;

    if (secim < 1 || secim > 5) {
        cout << "False choice!" << endl;
        return 0;
    }

    cout << "Step count (0-10): ";
    cin >> adim_limiti;

    if (adim_limiti > 10) {
        cout << "Maximum step is 10." << endl;
        adim_limiti = 10;
    }

    cout << "\nThis process may take time, please wait.\n" << endl;

    for (int i = 0; i < 15; i++) {
        string gorseller = "penrose_" + to_string(i) + ".png";
        remove(gorseller.c_str());
    }

    int genislik = 1000;
    int yukseklik = 1000;
    float yaricapBoyut = 400.0f;

    if (secim == 5) {
        genislik = 1080;
        yukseklik = 2160;
        yaricapBoyut = 885.0f;
    }

    vector<Triangle> ucgenler = baslangic(genislik, yukseklik, yaricapBoyut);

    Color renk1, renk2, kenar;

    if (secim == 1) {
        renk1.r = 255; renk1.g = 200; renk1.b = 220;
        renk2.r = 255; renk2.g = 150; renk2.b = 180;
        kenar.r = 255; kenar.g = 0; kenar.b = 0;
    }

    else if (secim == 2) {
        renk1.r = 255; renk1.g = 255; renk1.b = 255;
        renk2.r = 0;   renk2.g = 0;   renk2.b = 0;
        kenar.r = 255; kenar.g = 0;   kenar.b = 0;
    }

    else if (secim == 3) {
        renk1.r = 120; renk1.g = 180; renk1.b = 255;
        renk2.r = 70;  renk2.g = 100; renk2.b = 200;
        kenar.r = 255; kenar.g = 255; kenar.b = 255;
    }

    else if (secim == 5) {

        int sans = rand() % 5;

        if (sans == 0) {
            renk1.r = 160; renk1.g = 210; renk1.b = 160; //acik fistik yesili
            renk2.r = 80;  renk2.g = 10;  renk2.b = 30; //bordo
            kenar.r = 0; kenar.g = 0;   kenar.b = 0;
        }
        else if (sans == 1) {
            renk1.r = 255; renk1.g = 140; renk1.b = 40; //turuncu
            renk2.r = 10;  renk2.g = 60;  renk2.b = 75; //petrol mavisi
            kenar.r = 0; kenar.g = 0;   kenar.b = 0;
        }
        else if (sans == 2) {
            renk1.r = 200; renk1.g = 160; renk1.b = 255; //lila
            renk2.r = 40;  renk2.g = 20;  renk2.b = 60; //mor
            kenar.r = 0; kenar.g = 0;   kenar.b = 0;
        }
        else if (sans == 3) {
            renk1.r = 255; renk1.g = 245; renk1.b = 150; //sarimsi
            renk2.r = 0;   renk2.g = 90;  renk2.b = 100; //turkuaz
            kenar.r = 0; kenar.g = 0;   kenar.b = 0;
        }
        else if (sans == 4) {
            renk1.r = 255; renk1.g = 192; renk1.b = 203; //tpz pembe
            renk2.r = 130; renk2.g = 30;  renk2.b = 40; //kiremitim
            kenar.r = 0; kenar.g = 0;   kenar.b = 0;
        }
        
    }

    else { //4
        renk1.r = 255; renk1.g = 255; renk1.b = 255;
        renk2.r = 0;   renk2.g = 0;   renk2.b = 0;
        kenar.r = 255; kenar.g = 0;   kenar.b = 0;
    }

    for (int adim = 0; adim <= adim_limiti; adim++) {

        ColorImage img(genislik, yukseklik);

        if (secim == 1 || secim == 2) {

            //ucgen modu
            for (int i = 0; i < ucgenler.size(); i++) {

                Triangle u = ucgenler[i];
                Color dolgu;

                if (u.tip == 0)
                    dolgu = renk1;

                else
                    dolgu = renk2;

                ucgenBoya(img, u.A, u.B, u.C, dolgu);
                dda(img, u.A, u.B, kenar);
                dda(img, u.B, u.C, kenar);
                dda(img, u.C, u.A, kenar);
            }
        }

        if (secim == 3 || secim == 4 || secim == 5) {
            //rhombus modu
            for (int i = 0; i < ucgenler.size(); i++) {

                Rhombus d = cevir(ucgenler[i]);
                Color boya;

                if (d.tip == 0)
                    boya = renk1;

                else
                    boya = renk2;

                dortgenBoya(img, d.A, d.B, d.D, d.C, boya);
                dda(img, d.A, d.B, kenar);
                dda(img, d.B, d.D, kenar);
                dda(img, d.D, d.C, kenar);
                dda(img, d.C, d.A, kenar);
            }
        }

        string s = to_string(adim);
        string dosya = "penrose_" + s + ".png";
        img.Save(dosya.c_str());

        if (adim < adim_limiti) {
            ucgenler = parcala(ucgenler);
        }
    }
    
    cout << "\nComplated!" << endl;
    return 0;
}