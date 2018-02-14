#include "Fraction.hxx"
#include <iostream>
#include <string>
using namespace std;


int main(){

  Fraction<int> f1 = Fraction<int>(4,6);
  cout << "The fraction is: "<<f1.num()<<"/"<<f1.den()<<"\n"<<endl;
  Fraction<int> f2 = Fraction<int>(3,9);
  cout << "The fraction is: "<<f2.num()<<"/"<<f2.den()<<"\n"<<endl;
  Fraction<int> f3 = f1 * f2;
  cout << "The fraction is: "<<f3.num()<<"/"<<f3.den()<<"\n"<<endl;
  Fraction<int> f4 = f1 + f2;
  cout << "The fraction is: "<<f4.num()<<"/"<<f4.den()<<"\n"<<endl;

}
