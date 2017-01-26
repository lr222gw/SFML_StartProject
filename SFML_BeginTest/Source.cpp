#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Export.hpp>
#include <SFML\Graphics\Transform.hpp>

#include <iostream>
#include <string>

using namespace std;

sf::RenderWindow *getWindow(int height, int width, string NameOfWindow);
sf::Shape *getShape(string type, float num = 100.f); //Vi säger att Num har som standard värde "100.f", Detta görs bara i deklarationen, ej definitionen!

int main() {
	//sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::RenderWindow *window = getWindow(1920,1080, "Mitt Program"); 
	
	//När vi skapar ett window så får vi Pekaren till denna, därför tar vi emot den med stjärnan! 
	//När vi har ett pekarobject ska vi alltid "Peka", alltså använda "->" istället för ".", vet inte varför men det funkar! :)


	//sf::CircleShape shape(100.f);
	sf::Shape *shape = getShape("circle", 100.f); // Vi hämtar en circle, den ärver av "shape". 
	//För att göra det möjligt att hämta vilken shape som helst så används alltså "förälder klassen" så att eventuella "barn klasser" kan returneras till den!


	shape->setFillColor(sf::Color::Blue);// Här ändrar vi färgen på vår shape...

	sf::Mouse *mouse = new sf::Mouse();

	
	bool mouseB = false;
	while (window->isOpen())// Loopen pågår så länge fönstret är öppet
	{
		sf::Event event; //Vi skapar en "event" objekt, med den kan man märka skillnadet
		if (window->pollEvent(event))// Vi säger, utför loopen för varje event som sker (?) (Verkar fungera med "if" också, men det var såhär koden såg ut från början...
		{
			if (event.type == sf::Event::Closed)  // Om eventet som skedde var att Användaren tryckte på "Close" så stänger vi fönstret
				window->close(); // Fönstret strängs och loopen går ur
		}

		shape->setPosition((float)mouse->getPosition().x - (float)shape->getLocalBounds().width/2, //hämtar muspositionen och subtraherar bredden 
						   (float)mouse->getPosition().y - (float)shape->getLocalBounds().height/2); //och höjden med hälften av bredden och höjden på det aktuella objektet
		// Vi ändrar vår "shapes" position så att den har samma kordinater som min muspekare!

				// Ta bort allt gammalt
		if (event.type == sf::Event::MouseButtonPressed) { //event.type kan jämföras med andra event, så om en musknapp trycks ner så kommer det returnera true
			
			mouseB = true;
		}
		 
		if (event.type == sf::Event::MouseButtonReleased) { // När musknappen släpps, ta bort allt som ritats
			window->clear();
			mouseB = false;
		}
		

		if (event.type == sf::Event::MouseMoved) {
			if (mouseB == true) {
				window->draw(*shape);	// Rita ut formen på nytt
			}			
			
		}

		if (event.type == sf::Event::MouseWheelScrolled) {

			float penSizer = 0.006;// För att bestämma med hur mycket storleken ska sjunka eller höjjas per scroll
			
			sf::Vector2f shappe  = shape->getScale(); // Vi behöver skapa denna, för att getShape returnerar den
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

sf::Shape *getShape(string type, float num) { // Låter oss returnera allt som ärver av Shape
	sf::Shape *shape;

	if (type == "circle") { // Kan inte använda stringbaserad switch... så blir if-satser
		shape = new sf::CircleShape(num);
	}
	else if (type == "rectangle") {

		sf::Vector2f *vekt = new sf::Vector2f(num, num); //För att skapa en rektangel behöver vi skapa en vektor! 

		shape = new sf::RectangleShape(*vekt); // Vektorns pekare tas emot av rektangelkonstruktorn! 
	}
	else if (type == "triangle") {


		shape = new sf::CircleShape(num, 3); // Första parametern berättar storleken, andra antal hörn
		//En cirkel med många hörn ser rundare ut... 
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
	// "&"-tecknet innebär referens
	// man kan också använda en "Smart pointer": "std::unique_ptr<className> function(string something)"

	// v här skapar vi pekaren 
	sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(height, width), NameOfWindow);
	//typ			 *namn	   new	   typ				parametrar
	return window;
}