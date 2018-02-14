#ifndef Fraction_hxx
#define Fraction_hxx
#include <iostream>

template <class type>

type mcd( type  num, type  den){
    if(num%den == 0){
      return den;
    }else{
      return mcd(den,num%den);
    }
}

template <class type>

  class Fraction{

  private:
     type _num;
     type _den;

  public:

    Fraction( type num, type den){
      _num = num;
      _den = den;
      simplify();
    }
    //getter num
    type &  num(){
      return _num;
    }
    //setter num
    void num( type & numerador){
      _num = numerador;
    }

    //getter den
    type & den(){
      return _den;
    }
    //setter num
    void den( type & denominador){
      _den = denominador;
    }

     Fraction operator *(Fraction & f)const{
       return  Fraction(_num*f.num(), _den*f.den());
    }

    Fraction operator +(Fraction & f)const{
      return  Fraction((_num*f.den()+_den*f.num()), _den*f.den());
    }

    void simplify(){
       type maxd = mcd<int>(_num , _den);
      _num = _num/maxd;
      _den = _den/maxd;

    }

};
#endif
