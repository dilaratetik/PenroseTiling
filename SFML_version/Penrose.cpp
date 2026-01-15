#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <cmath>
#include <optional> 
#include <ctime>
#include <algorithm>

using namespace std;
using namespace sf;

float pi = 3.14159f;
float altinOran = 1.618f;
int adimSayisi = 0;
//float zoom = 1.0f;


struct Nokta {
    float x;
    float y;

    //Nokta() : x(0), y(0) {}

    /* Nokta(float _x, float _y) {
         x = _x;
         y = _y;
     } */

    Nokta operator+(Nokta diger) {
        Nokta sonuc;
        sonuc.x = x + diger.x;
        sonuc.y = y + diger.y;
        return sonuc;
    }

    Nokta operator-(Nokta diger) {
        Nokta sonuc;
        sonuc.x = x - diger.x;
        sonuc.y = y - diger.y;
        return sonuc;
    }

    Nokta operator*(float sayi) {
        Nokta sonuc;
        sonuc.x = x * sayi;
        sonuc.y = y * sayi;
        return sonuc;
    }

    Nokta operator/(float sayi) {
        Nokta sonuc;
        sonuc.x = x / sayi;
        sonuc.y = y / sayi;
        return sonuc;
    }
};

    /*float mesafe(Nokta diger) {
        float dx = x - diger.x;
        float dy = y - diger.y;
        return sqrt(dx*dx + dy*dy);
    }*/

struct Triangle {
    int tip; //0 buyuk, 1 kucuk
    Nokta A;
    Nokta B;
    Nokta C;
    //Color renk;
    //int id;
    //bool secili;

    Triangle() {
        tip = 0;
        //id = 0;
        //secili = false;
    }

    Triangle(int t, Nokta a, Nokta b, Nokta c) {
        tip = t;
        A = a;
        B = b;
        C = c;
    }

};

struct Rhombus {
    int tip;
    Nokta A;
    Nokta B;
    Nokta C;
    Nokta D;

    Rhombus() {}
    //Rhombus(int t) : tip(t) {}

};

//ucgeni dortgene cevir
Rhombus cevir(Triangle u) {
    Rhombus d;
    d.tip = u.tip;
    d.A = u.A;
    d.B = u.B;
    d.C = u.C;
    d.D = u.B + u.C - u.A;

    return d;
}

/*bool ucgenKontrol(Triangle u) {
    return (u.tip == 0 || u.tip == 1);
}*/

vector<Triangle> parcala(vector<Triangle> ucgenler) {
    vector<Triangle> yeniListe;

    //int sayac = 0;
    int toplam = 0;

    for (int i = 0; i < ucgenler.size(); i++) {
        Triangle u = ucgenler[i];

        if (u.tip == 0) { //buyuk ucgen ise

            Nokta p;
            p = u.A + (u.B - u.A) / altinOran;

            Triangle u1;
            u1.tip = 0;
            u1.A = u.C;
            u1.B = p;
            u1.C = u.B;
            yeniListe.push_back(u1);

            Triangle u2;
            u2.tip = 1;
            u2.A = p;
            u2.B = u.C;
            u2.C = u.A;
            yeniListe.push_back(u2);

            //sayac++;
            toplam += 2;

        }

        else { //kucuk ucgen ise
            Nokta q, r;

            q = u.B + (u.A - u.B) / altinOran;
            r = u.B + (u.C - u.B) / altinOran;

            Triangle u1;
            u1.tip = 1;
            u1.A = r;
            u1.B = u.C;
            u1.C = u.A;
            yeniListe.push_back(u1);

            Triangle u2;
            u2.tip = 1;
            u2.A = q;
            u2.B = r;
            u2.C = u.B;
            yeniListe.push_back(u2);

            Triangle u3;
            u3.tip = 0;
            u3.A = r;
            u3.B = q;
            u3.C = u.A;
            yeniListe.push_back(u3);

            toplam += 3;

        }
    }
    adimSayisi++;

    return yeniListe;
}

vector<Triangle> baslangic() {
    vector<Triangle> liste;

    float yaricap = 400;
    Nokta merkez;
    merkez.x = 500;
    merkez.y = 500;

    for (int i = 0; i < 10; i++) {
        float derece1 = (2 * i - 1) * 18.0f;
        float derece2 = (2 * i + 1) * 18.0f;

        float aci1 = derece1 * pi / 180.0f;
        float aci2 = derece2 * pi / 180.0f;

        Nokta B, C;
        B.x = merkez.x + yaricap * cos(aci1);
        B.y = merkez.y + yaricap * sin(aci1);

        C.x = merkez.x + yaricap * cos(aci2);
        C.y = merkez.y + yaricap * sin(aci2);

        Triangle yeni;
        yeni.tip = 0;
        yeni.A = merkez;

        // ayna
        if (i % 2 == 0) {
            yeni.B = C;
            yeni.C = B;
        }
        else {
            yeni.B = B;
            yeni.C = C;
        }

        liste.push_back(yeni);
    }
    return liste;
}

int main() {

    int secim;
    bool devam = true;
    //int pencereWidth = 1000;
    //int pencereHeight = 1000;

    cout << "--Penrose Tiling Project--\n\n";
    cout << "1 - Robinson's Triangle mode (Pink)\n";
    cout << "2 - Robinson's Triangle mode (B&W)\n";
    cout << "3 - Rhombus mode (Blue)\n";
    cout << "4 - Rhombus mode (B&W)\n";

    cout << "\n-Controllers-\n";
    cout << "Space: Subdivide for next steps\n";
    cout << "R: Reset\n";
    cout << "S: Switch mode\n\n";

    cout << "Choose (1, 2, 3 or 4): ";

    cin >> secim;

    if (secim < 1 || secim > 4) {
        cout << "The wrong choice!\n";
        return 0;
    }

    RenderWindow pencere(VideoMode({ 1000, 1000 }), "Penrose Tiling");
    pencere.setFramerateLimit(60);

    //Clock saat;
    //float deltaTime = 0;
    //float zamanSayaci = 0;

    vector<Triangle> ucgenler = baslangic();
    //int oncekiSecim = secim;

    while (pencere.isOpen()) {
        while (const optional olay = pencere.pollEvent()) {
            if (olay->is<Event::Closed>()) {
                pencere.close();
            }

            else if (const auto* tus = olay->getIf<Event::KeyPressed>()) {
                if (tus->code == Keyboard::Key::Space) {
                    ucgenler = parcala(ucgenler);
                    //cout << "Triangle count: " << ucgenler.size() << endl;
                }

                else if (tus->code == Keyboard::Key::Num1) {
                    secim = 1; 
                }

                else if (tus->code == Keyboard::Key::Num2) {
                    secim = 2; 
                }

                else if (tus->code == Keyboard::Key::R) {
                    ucgenler = baslangic(); 
                }

                else if (tus->code == Keyboard::Key::S) {
                    if (secim == 1) secim = 2;
                    else if (secim == 2) secim = 3;
                    else if (secim == 3) secim = 4;
                    else if (secim == 4) secim = 1;
                }
            }
        }

        pencere.clear(Color(30, 30, 30));

        if (secim == 1) { //ucgen sb 

            for (int i = 0; i < ucgenler.size(); i++) {
                Triangle u = ucgenler[i];

                ConvexShape sekil;
                sekil.setPointCount(3);
                sekil.setPoint(0, Vector2f(u.A.x, u.A.y));
                sekil.setPoint(1, Vector2f(u.B.x, u.B.y));
                sekil.setPoint(2, Vector2f(u.C.x, u.C.y));

                if (u.tip == 0)
                    sekil.setFillColor(Color::White);
                else
                    sekil.setFillColor(Color::Black);

                sekil.setOutlineThickness(0.8f);
                sekil.setOutlineColor(Color::Red);
                pencere.draw(sekil);
            }
        }

        else if (secim == 2) { //ucgen pembe

            for (int i = 0; i < ucgenler.size(); i++) {
                Triangle u = ucgenler[i];

                ConvexShape sekil;
                sekil.setPointCount(3);
                sekil.setPoint(0, Vector2f(u.A.x, u.A.y));
                sekil.setPoint(1, Vector2f(u.B.x, u.B.y));
                sekil.setPoint(2, Vector2f(u.C.x, u.C.y));

                if (u.tip == 0)
                    sekil.setFillColor(Color(255, 200, 220, 200));
                else
                    sekil.setFillColor(Color(255, 150, 180, 200));

                sekil.setOutlineThickness(0.8f);
                sekil.setOutlineColor(Color::Black);
                pencere.draw(sekil);
            }
        }

        else if (secim == 3) { //dortgen sb

            for (int i = 0; i < ucgenler.size(); i++) {
                Rhombus d = cevir(ucgenler[i]);

                ConvexShape sekil;
                sekil.setPointCount(4);
                sekil.setPoint(0, Vector2f(d.A.x, d.A.y));
                sekil.setPoint(1, Vector2f(d.B.x, d.B.y));
                sekil.setPoint(2, Vector2f(d.D.x, d.D.y));
                sekil.setPoint(3, Vector2f(d.C.x, d.C.y));

                if (d.tip == 0)
                    sekil.setFillColor(Color::White);
                else
                    sekil.setFillColor(Color::Black);

                sekil.setOutlineThickness(0.8f);
                sekil.setOutlineColor(Color::Red);
                pencere.draw(sekil);
            }
        }

        else if (secim == 4) { //dortgen mavi

            for (int i = 0; i < ucgenler.size(); i++) {
                Rhombus d = cevir(ucgenler[i]);

                ConvexShape sekil;
                sekil.setPointCount(4);
                sekil.setPoint(0, Vector2f(d.A.x, d.A.y));
                sekil.setPoint(1, Vector2f(d.B.x, d.B.y));
                sekil.setPoint(2, Vector2f(d.D.x, d.D.y));
                sekil.setPoint(3, Vector2f(d.C.x, d.C.y));

                if (d.tip == 0)
                    sekil.setFillColor(Color(120, 180, 255, 200));
                else
                    sekil.setFillColor(Color(70, 100, 200, 200));

                sekil.setOutlineThickness(0.8f);
                sekil.setOutlineColor(Color::White);
                pencere.draw(sekil);
            }
        }

        pencere.display();

        //deltaTime = saat.restart().asSeconds();
        //zamanSayaci += deltaTime;
    }

    return 0;
}