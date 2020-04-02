#include <iostream>

#include "bimap.h"


int main()

{


    

   
   
    {
        using namespace std;
        using namespace container;
        

        bimap_second<int, string> b;
        bimap_first<int, string> b1;


        b1.emplace(5, "SnopDpg");
        b1.emplace(4, "Mama");
        b1.emplace(6, "Dad");

        b1.insert(7, "snopDpg");
        b1.insert(1, "mama");
        b1.insert(11, "dad");



        cout << b1.isEmpty() << endl;
        int k, p;
        string v;


        while (true)
        {
            cin >> p;
            switch (p)
            {
            case 1: { cin >> k >> v; b1.insert(k, v); break; } //insert


            case 2: {cin >> k >> v;  b1.emplace(std::move(k), std::move(v)); break; } //emplace
                  
            case 3: {cin >> k; auto a = b1.keyGet(k);  cout << "{ " << a.first << " ; " << a.second.get() << " }" ; break; }

            case 4: {cin >> v; auto a = b1.valGet(v);  cout << "{ " << a.first << " ; "  << a.second.get() << " }";  break; }

            case 5: {cin >> k; b1.keyErase(k); break; }

            case 6: {cin >> v; b1.valErase(v); break; }

            default: break;
            }





            cout << "size = " << b1.size() << endl;

        }

        

        
        
        
        
    }
}