#include "Volume.h"
int main()
{
    Volume <int> v1;
    v1.setvalues(5, 5, 5);
    int volume1 = v1.Calvolume();
    Volume <int> v2;
    v2.setvalues(10, 10, 10);
    int volume2 = v2.Calvolume();
    v2.cmpVolume(v1.Calvolume(), v2.Calvolume());
    return 0;
}