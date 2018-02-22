#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fstream>

using namespace cv;
using namespace std;

int main()
{
    string tabDir[20];
    unsigned int maxWidthSize = 500;
    unsigned int maxHeightSize = 1300;
    unsigned int tabWidth[maxWidthSize];
    unsigned int tabHeight[maxHeightSize];
    for (int i=0;i<maxWidthSize;i++)tabWidth[i]=0;
    for (int i=0;i<maxHeightSize;i++)tabHeight[i]=0;

    fstream fileResult;
    fileResult.open("results.csv", ios::out | ios::trunc);
    if (fileResult.good()==true)cout<<"Plik wynikowty zostal otwarty"<<endl;
    else cout<<"Blad otwarcia pliku"<<endl;

    string _dir = "J:/ziarno2/TIFF/uszkodzenia/";

    const char * _dir_cch = _dir.c_str();
    struct dirent * plik;
    DIR * sciezka;
    int idKatalog=0;
    if(( sciezka = opendir( _dir_cch ) ) )
    {

        while(( plik = readdir( sciezka ) ) )
        {
            tabDir[idKatalog]=plik->d_name;
            idKatalog++;
        }
        closedir( sciezka );
    }
    else
        cout <<" blad otwarcia katalogu, pliku \n";

    string _filtr = "*log1*.tif";

    //for (int j=2; j<i; j++) cout<<tabDir[j]<<endl;



    Mat imageSrc;
    int maxWidth =0, maxHeight =0;
    for (int j=2; j<idKatalog; j++)
    {
        string dirStr = _dir+tabDir[j]+"\\";
        //cout<<dirStr<<endl<<endl;
        const char * dirSrc = dirStr.c_str();

        DIR* katalog = opendir(dirSrc); //<sciezka> zamieniamy na œcie¿kê do katalogu
        struct dirent* pozycja=0;
        vector<string> nazwa;
        string plik;
        unsigned int ilePlikow=0;
        while (pozycja=readdir(katalog))
        {
            plik=(*pozycja).d_name;
            if (plik.find(".tif")==(plik.length()-4))   //.txt mozna zamienic na dowolne 4 znaki znajdujace sie na koncu nazwy
            {
                ilePlikow++;
                imageSrc= imread(dirStr + plik);
                tabWidth[imageSrc.cols]++;
                tabHeight[imageSrc.rows]++;
                if(maxWidth < imageSrc.cols)
                    maxWidth=imageSrc.cols;
                if(maxHeight < imageSrc.rows)
                    maxHeight=imageSrc.rows;
                //plik.erase(plik.length()-4); //usuwanie .txt
                //cout<<plik<<endl;
                //cout<<".";
            }

        }
        //cout<<dirStr + plik<<"*"<<endl;
        cout<<endl<<tabDir[j]<<"->"<<"MAX width: "<<maxWidth<<" MAX heigth: "<<maxHeight<<" plikow:"<<ilePlikow<<endl;

        maxWidth=0;
        maxHeight=0;
        closedir(katalog);
    }
    for(int i=0; i<maxHeightSize; i++)fileResult<<i<<","<<tabWidth[i]<<","<<tabHeight[i]<<endl;

    fileResult.close();




    return 0;
}
