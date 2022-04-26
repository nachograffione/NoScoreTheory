
//	
////	FOR RENDERING TESTS
//	//init
//	Note n1("do", "", 3);
//	Note n2("la", "", 3);
//	Key k1(60);
//	
//	k1.setPosition(300,300);
//	sf::RectangleShape r(sf::Vector2f(50,50));
//	r.setPosition(k1.getButtonGlobalBounds(0).left, k1.getButtonGlobalBounds(0).top);
//	std::cout << k1.getButtonGlobalBounds(0).left << " " << k1.getButtonGlobalBounds(0).top << std::endl;
//
////	draw inits
//	sf::RenderWindow window(sf::VideoMode(1200, 900), "NoScoreTheory", sf::Style::Titlebar|sf::Style::Close, 
//		   sf::ContextSettings(0, 0, 7, 1, 1, sf::ContextSettings::Attribute::Default, false));
//	window.setFramerateLimit(60);
//	sf::Event event;
//	while (window.isOpen()){
//		while (window.pollEvent(event)){
//			switch (event.type){
//			case sf::Event::Closed:
//				window.close();
//			case sf::Event::MouseButtonPressed:
////				sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
//					sf::Vector2f mousePosition(mainV.window.mapPixelToCoords({mainV.event.mouseButton.x, mainV.event.mouseButton.y}));
//				if (k1.contains(mousePosition)){
//					if(k1.getPressed()){
//						bool buttonPressed = false;
//						for(size_t i=0;i<k1.getNoteButtons()->size();i++) { 					
//							if(k1.getButtonGlobalBounds(i).contains(mousePosition)){
//								k1.setActiveNote(*k1.getNotes()[i]);
//								buttonPressed = true;
//								break;
//							}
//						}
//						if (!buttonPressed){
//							k1.switchPressed();
//						}
//					}
//					else{
//						k1.switchPressed();
//					}
//				}
//				break;
//			}
//		}
//
//		//draw and display
//		window.clear(sf::Color(200,220,255));
//		
//		window.draw(k1);
//		
//		window.display();
//	}
