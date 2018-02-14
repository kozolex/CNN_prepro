#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <dirent.h>

using namespace cv;
using namespace std;

int main()
{
    DIR* katalog = opendir( "F:\\noweFotyZiaren\\NormaOdmiany\\Bordo2016" ); //<sciezka> zamieniamy na œcie¿kê do katalogu
    struct dirent* pozycja=0;
    vector<string> nazwa;
    string plik;
    while (pozycja=readdir(katalog))
    {
        plik=(*pozycja).d_name;
        if (plik.find(".tif")==(plik.length()-4))   //.txt mozna zamienic na dowolne 4 znaki znajdujace sie na koncu nazwy
        {
            //plik.erase(plik.length()-4); //usuwanie .txt
            cout<<plik<<endl;
        }
    }

    closedir(katalog);
    return 0;
}
