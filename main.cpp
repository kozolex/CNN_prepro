#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <windows.h>

using namespace cv;
using namespace std;

int main()
{
    string tabDir[20];
    string _dir = "I:/ziarno2/TIFF/uszkodzenia/"; // I:\ziarno2\TIFF\odmiany

    const char * _dir_cch = _dir.c_str();
    struct dirent * plik;
    DIR * sciezka;
    int i=0;
    if(( sciezka = opendir( _dir_cch ) ) )
    {

        while(( plik = readdir( sciezka ) ) )
        {
            tabDir[i]=plik->d_name;
            i++;
        }
        closedir( sciezka );
    }
    else
        cout <<" blad otwarcia strumienia dla danej sciezki\n";

    string _filtr = "log1";

    //for (int j=2; j<i; j++) cout<<tabDir[j]<<endl;

    Mat imageSrc,imageRSize;
    int maxWidth =0, maxHeight =0;
    for (int j=2; j<i; j++)
    {


        string dirStr = _dir+tabDir[j]+"\\";
        //cout<<dirStr<<endl<<endl;
        const char * dirSrc = dirStr.c_str();

        DIR* katalog = opendir(dirSrc); //<sciezka> zamieniamy na sciezke do katalogu
        struct dirent* pozycja=0;
        vector<string> nazwa;
        string plik;
        while (pozycja=readdir(katalog))
        {

            plik=(*pozycja).d_name;

            if (plik.find(_filtr)==(plik.length()-8))   //.txt mozna zamienic na dowolne 4 znaki znajdujace sie na koncu nazwy
            {
                imageSrc= imread(dirStr + plik);
                //cout<<dirStr + plik<<endl;
                resize(imageSrc, imageRSize, cv::Size(), 0.33, 0.33);
                //dirStr.insert( 10, "/PNG" );
                //CreateDirectory(dirStr.c_str()),NULL);
                imwrite(dirStr+plik+".png",imageRSize);
                //cout<<dirStr + plik+".png"<<endl;
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
        cout<<endl<<tabDir[j]<<"->"<<"MAX width: "<<maxWidth<<" MAX heigth: "<<maxHeight<<endl;
        maxWidth=0;
        maxHeight=0;
        closedir(katalog);
    }
    //cout<<endl<<"MAX width: "<<maxWidth<<" MAX heigth: "<<maxHeight<<endl;




    return 0;
}
