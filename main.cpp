#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <dirent.h>

using namespace cv;
using namespace std;

int main()
{
    Mat imageSrc;
    int maxWidth =0, maxHeight =0;
    string dirStr = "F:\\noweFotyZiaren\\NormaOdmiany\\JOVincenta\\";
    const char * dirSrc = dirStr.c_str();

    DIR* katalog = opendir(dirSrc); //<sciezka> zamieniamy na œcie¿kê do katalogu
    struct dirent* pozycja=0;
    vector<string> nazwa;
    string plik;
    while (pozycja=readdir(katalog))
    {
        plik=(*pozycja).d_name;
        if (plik.find(".tif")==(plik.length()-4))   //.txt mozna zamienic na dowolne 4 znaki znajdujace sie na koncu nazwy
        {
            imageSrc= imread(dirStr + plik);
            if(maxWidth < imageSrc.cols) maxWidth=imageSrc.cols;
            if(maxHeight < imageSrc.rows) maxHeight=imageSrc.rows;
            //plik.erase(plik.length()-4); //usuwanie .txt
            //cout<<plik<<endl;
            cout<<".";
        }

    }
    cout<<endl<<"MAX width: "<<maxWidth<<endl<<"MAX heigth: "<<maxHeight<<endl;

    closedir(katalog);
    return 0;
}
