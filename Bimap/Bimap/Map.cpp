#include <iostream>

#include "bimap.h"


int main()

{


    

   
   
    {
        using namespace std;
        using namespace container;
        

        bimap_second<int, string> b;
        cout << b.isEmpty() << endl;
        int k, p;
        string v;


        b.emplace(1, "mom");
        b.emplace(2, "dad");
        b.emplace(3, "dog");
        while (true)
        {
            cin >> p;
            switch (p)
            {
            case 1: { cin >> k >> v; b.insert(k, v); break; } //insert


            case 2: {cin >> k >> v;  b.emplace(std::move(k), std::move(v)); break; } //emplace

            case 3: {cin >> k; auto a = b.keyGet(k);  cout << "{ " << a.first << " ; " << a.second.get() << " }" ; break; }

            case 4: {cin >> v; auto a = b.valGet(v);  cout << "{ " << a.first << " ; "  << a.second.get() << " }";  break; }

            case 5: {cin >> k; b.keyErase(k); break; }

            case 6: {cin >> v; b.valErase(v); break; }

            default: break;
            }





            cout << "size = " << b.size() << endl;

        }

        

        
        
        
        
    }
}