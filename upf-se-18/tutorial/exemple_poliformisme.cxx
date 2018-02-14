/*
   - usem els accessors d'escriptura i de lectura de l'atribut _nom

   En resum hem après:
   - com escriure per consola fent servir <iostream>
   - simbols de la libreria localitzats al namespace std::
   - les classes acaben en ;
   - el mètodes i atributs per defecte són private
   - com fer subclasses: "Sub : public Super"
   - perquè serveixen els mètodes virtuals
   - polimorfisme
   - usar #ifndef als headers per evitar redefinicions
   - pas de paràmetres per referència
   - col.leccions estàndars vector i list
   - typdefs
   - iteradors
   - std::string
   - ús d'accessors
 */

#include <list>
#include "animals.hxx"

typedef std::list<Animal*> Animals; //creamos una lista llamada animals

int main(void)
{
	Animals animals; //la lista Animals tendra nombre animals

	// introduïm un de cada tipus
	Animal unAnimal; //unAnimal de tipo Animal
	unAnimal.nom("Pikatxu"); // Este unAnimal se llama pikatxu
	animals.push_back(&unAnimal);// ponemos a pikatxu en la lista animals

	Elefant unElefant; // unElefant de tipo elefant
	unElefant.nom("Jumbo l'Orellut");
	animals.push_back(&unElefant);

	Granota unaGranota;
	unaGranota.nom("Gustavo el Reporter");
	animals.push_back(&unaGranota);

	Gat unGat;
	unGat.nom("Gat Amb Botes");
	animals.push_back(&unGat);

	Elefant segElefant;
	segElefant.nom("Phanpy");
	Granota segGranota;
	segGranota.nom("Bulbasaur");
	Gat segGat;
	segGat.nom("Meowth");


	unElefant.sibling(&segElefant);
	unaGranota.sibling(&segGranota);
	unGat.sibling(&segGat);


	// iterem fent servir iteradors
	for (Animals::iterator it=animals.begin(); it!=animals.end(); it++)
	{
		std::cout << "\nEnclosure of  ";
		(*it)->escriuEspecie();
		std::cout << (*it)->nom()<< " \n";
		(*it)->enclosure();
	}

	return 0;
}
