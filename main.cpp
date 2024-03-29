#include <iostream>
#include <fstream>
#include "perceptron.h"
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

void distort(vector<vector<float> > &input,float dis_percent)
 {
                                        // karakterleri verilen yuzdede
                                        // bozan fonksiyon

    srand(time(NULL));

    for(int i=0;i<input.size();i++)
        for(int j=0;j<input[i].size();j++)
        {
            if(rand()%100 < dis_percent)
            {
                if(input[i][j]==1)
                    input[i][j]=0;
                else
                    input[i][j]=1;
            }
        }
}

int main()
{
    char* file_names[21]={
        "input/Font_1_A.txt",
        "input/Font_1_B.txt",
        "input/Font_1_C.txt",
        "input/Font_1_D.txt",
        "input/Font_1_E.txt",
        "input/Font_1_J.txt",
        "input/Font_1_K.txt",

        "input/Font_2_A.txt",
        "input/Font_2_B.txt",
        "input/Font_2_C.txt",
        "input/Font_2_D.txt",
        "input/Font_2_E.txt",
        "input/Font_2_J.txt",
        "input/Font_2_K.txt",

        "input/Font_3_A.txt",
        "input/Font_3_B.txt",
        "input/Font_3_C.txt",
        "input/Font_3_D.txt",
        "input/Font_3_E.txt",
        "input/Font_3_J.txt",
        "input/Font_3_K.txt"
    };

    vector<vector<float> > ins;
    vector<int> outs;

    string input_str;

    for(int i=0;i<21;i++)
    {
        ifstream file(file_names[i]);
        int k=0;

        vector<float> x;

        while(getline(file,input_str,',')) // read till ','
        {
            int neg =  input_str.find("-");

            if(neg == string::npos) // stringin icinde - isareti yoksa degeri 1'dir.
                x.push_back(1);
            else
                x.push_back(0); // -1 : bipolar
                                 //  0 : binary
        }

        ins.push_back(x);
        outs.push_back(i%7);

        file.close();
    }

    perceptron p1(63,7); // 63 girisi ve 7 adet cikisi
                         // bulunan bir perceptron olusturulur.
                         // ilk agirliklar 0 a esitlenir.

    int train_time = p1.train(ins,outs,100,0.01,1);
                        // ins vektorunu giris, outs vektorunu
                        // ise cikis kabul ederek
                        // max epoch 100, learning rate 0.01
                        // delta rule = 0 yani perceptron rule
                        // kullanilacak sekilde perceptron egitilir.
                        // egitim tamamlandigi epoch sayisi return edilir.

    cout << train_time << ". epochta egitim tamamlandi" << endl;
    cout << "Egitimden sonraki dogruluk: " << p1.test(ins,outs) << endl;
                        // egitilmis perceptron uzerinde
                        // bozulmamis veri ile test yapilir.
                        // ve sonucta dogrulugun 1(%100) oldugu gorulur.

    int dis_percent = 10; // karakterleri bozma yuzdesi

    distort(ins,dis_percent);
    cout << "%" << dis_percent << " bozma isleminde sonra dogruluk: " << p1.test(ins,outs) << endl;
                        // karakter bozma islemi tamamlandiktan sonra
                        // bozulmus karakterler ile ayni perceptron uzerinde
                        // test yapilir ve dogrulugun dustugu gozlenir.

    //p1.print_weights(); // son agirliklar ekrana yazdirilir.

    return 0;
}

/*
// karakterlerin bozuldugu gorsel olarak
// gostermek  icin hazirlanan fonksiyon.

void printFirstFont(vector<vector<float> > input)
{
    for(int q=0;q<1;q++)
    {
        for(int j=0;j<9;j++)
        {
            for(int i=7*q;i<7*q+7;i++)
            {
                for(int k=0;k<7;k++)
                {
                    if(input[i][j*7+k] == 1)
                        std::cout << '#';
                    else
                        std::cout << ' ';
                    std::cout << " ";
                }
                std::cout << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}
*/
