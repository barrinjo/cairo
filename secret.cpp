#include <iostream>
#include<string>

using namespace std;

void fire_main_blasters(string f) {
  cout << "you no take " << f << endl;
}

int main(void) {
  string cannon_1 = "candle";
  fire_main_blasters(cannon_1);

  return 0;
}
