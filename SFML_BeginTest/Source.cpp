#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Export.hpp>
#include <SFML\Graphics\Transform.hpp>

#include <iostream>
#include <string>

using namespace std;

sf::RenderWindow *getWindow(int height, int width, string NameOfWindow);
sf::Shape *getShape(string type, float num = 100.f); //Vi s�ger att Num har som standard v�rde "100.f", Detta g�rs bara i deklarationen, ej definitionen!

int main() {
	//sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::RenderWindow *window = getWindow(1920,1080, "Mitt Program"); 
	
	//N�r vi skapar ett window s� f�r vi Pekaren till denna, d�rf�r tar vi emot den med stj�rnan! 
	//N�r vi har ett pekarobject ska vi alltid "Peka", allts� anv�nda "->" ist�llet f�r ".", vet inte varf�r men det funkar! :)


	//sf::CircleShape shape(100.f);
	sf::Shape *shape = getShape("circle", 100.f); // Vi h�mtar en circle, den �rver av "shape". 
	//F�r att g�ra det m�jligt att h�mta vilken shape som helst s� anv�nds allts� "f�r�lder klassen" s� att eventuella "barn klasser" kan returneras till den!


	shape->setFillColor(sf::Color::Blue);// H�r �ndrar vi f�rgen p� v�r shape...

	sf::Mouse *mouse = new sf::Mouse();

	
	bool mouseB = false;
	while (window->isOpen())// Loopen p�g�r s� l�nge f�nstret �r �ppet
	{
		sf::Event event; //Vi skapar en "event" objekt, med den kan man m�rka skillnadet
		if (window->pollEvent(event))// Vi s�ger, utf�r loopen f�r varje event som sker (?) (Verkar fungera med "if" ocks�, men det var s�h�r koden s�g ut fr�n b�rjan...
		{
			if (event.type == sf::Event::Closed)  // Om eventet som skedde var att Anv�ndaren tryckte p� "Close" s� st�nger vi f�nstret
				window->close(); // F�nstret str�ngs och loopen g�r ur
		}

		shape->setPosition((float)mouse->getPosition().x - (float)shape->getLocalBounds().width/2, //h�mtar muspositionen och subtraherar bredden 
						   (float)mouse->getPosition().y - (float)shape->getLocalBounds().height/2); //och h�jden med h�lften av bredden och h�jden p� det aktuella objektet
		// Vi �ndrar v�r "shapes" position s� att den har samma kordinater som min muspekare!

				// Ta bort allt gammalt
		if (event.type == sf::Event::MouseButtonPressed) { //event.type kan j�mf�ras med andra event, s� om en musknapp trycks ner s� kommer det returnera true
			
			mouseB = true;
		}
		 
		if (event.type == sf::Event::MouseButtonReleased) { // N�r musknappen sl�pps, ta bort allt som ritats
			window->clear();
			mouseB = false;
		}
		

		if (event.type == sf::Event::MouseMoved) {
			if (mouseB == true) {
				window->draw(*shape);	// Rita ut formen p� nytt
			}			
			
		}

		if (event.type == sf::Event::MouseWheelScrolled) {

			float penSizer = 0.006;// F�r att best�mma med hur mycket storleken ska sjunka eller h�jjas per scroll
			
			sf::Vector2f shappe  = shape->getScale(); // Vi beh�ver skapa denna, f�r att getShape returnerar den
			if (event.mouseWheelScroll.delta < 0) {

				shape->setScale(shappe.x + penSizer, shappe.y + penSizer);
			}
			else {
				shape->setScale(shappe.x - penSizer, shappe.y - penSizer);
			}
			
			
			
		}


		
		window->display();		// Uppdatera displayen! 
	}

	return 0;

	
}

sf::Shape *getShape(string type, float num) { // L�ter oss returnera allt som �rver av Shape
	sf::Shape *shape;

	if (type == "circle") { // Kan inte anv�nda stringbaserad switch... s� blir if-satser
		shape = new sf::CircleShape(num);
	}
	else if (type == "rectangle") {

		sf::Vector2f *vekt = new sf::Vector2f(num, num); //F�r att skapa en rektangel beh�ver vi skapa en vektor! 

		shape = new sf::RectangleShape(*vekt); // Vektorns pekare tas emot av rektangelkonstruktorn! 
	}
	else if (type == "triangle") {


		shape = new sf::CircleShape(num, 3); // F�rsta parametern ber�ttar storleken, andra antal h�rn
		//En cirkel med m�nga h�rn ser rundare ut... 
	}
	else if (type == "square") {
		shape = new sf::CircleShape(num, 4);
	}
	else if (type == "octagon") {
		shape = new sf::CircleShape(num, 8);
	}
	else if (type == "") {
		shape = new sf::CircleShape(num);
	}

	return shape;
}



///<param name='getWindow'>Creates and return a SFML window "Pointer(?)"</param>
sf::RenderWindow *getWindow(int height, int width, string NameOfWindow) {
	// Returnerar pekare till ett RenderWindow object! 
	// "&"-tecknet inneb�r referens
	// man kan ocks� anv�nda en "Smart pointer": "std::unique_ptr<className> function(string something)"

	// v h�r skapar vi pekaren 
	sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(height, width), NameOfWindow);
	//typ			 *namn	   new	   typ				parametrar
	return window;
}