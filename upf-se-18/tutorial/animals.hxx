#ifndef animals_hxx
#define animals_hxx

#include <iostream>
#include <string>
#include <list>
class Animal;
typedef std::list<Animal*> Animals;



class Animal
{
	Animals _siblings;

public:
	virtual void escriuEspecie() const
	{
		std::cout << "...indefinida..." << std::endl;
	}
	void nom(std::string elNom)
	{
		_nom = elNom;
	}
	std::string& nom()
	{
		return _nom;
	}

	void sibling(Animal *animal)
	{
		_siblings.push_back(animal);
	}

	void enclosure(){

		for(Animals::iterator it=_siblings.begin(); it!=_siblings.end(); it++)
		{
			std::cout << (*it)->nom()<<"\n\n";
		}
	}
private:
	std::string _nom;

};

class Elefant : public Animal
{
public:
	virtual void escriuEspecie() const
	{
		std::cout << "elefant" << std::endl;
	}
};

class Granota : public Animal
{
public:
	virtual void escriuEspecie() const
	{
		std::cout << "granota" << std::endl;
	}
};

class Gat : public Animal
{
public:
	virtual void escriuEspecie() const
	{
		std::cout << "gat" << std::endl;
	}
};

#endif
