#include <iostream>

#include "bimap.h"


int main()

{


    //std::map <int, std::string, std::less<int>, std::allocator<

   
   
    {
        using namespace std;
        using namespace container;
        

        bimap_second<int, string> b;
        cout << b.isEmpty() << endl;
        b.emplace(1, "����");
       // a.checkKey(0);
        cout << "vfvf";
        //cout << bimap2x.isEmpty();
        //bimap2x.insert(1, "����");
        //bimap2x.emplace(1, "����");
    }
}