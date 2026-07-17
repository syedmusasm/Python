#include <iostream>
using namespace std;
template <class T>
class Volume {
private:
    T length;
    T width;
    T height;
public:
    void setvalues(T l, T w, T h)
    {
        length = l;
        width = w;
        height = h;
    }

    T Calvolume()
    {
        
        T volume = length* width* height;
        cout << "Volume: " << volume << endl;
        return volume;
    }

    void cmpVolume(T v1, T v2)
    {
        if(v1 > v2)
        {
            cout<<"Volume 1 has greater volume"<<endl;
        }
        else if(v1 < v2)
        {
            cout<<"Volume 2 has greater volume"<<endl;
        }
        else
        {
            cout<<"Both volumes are equal"<<endl;
        }
    }


};
