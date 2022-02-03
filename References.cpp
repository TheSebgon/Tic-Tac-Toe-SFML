/*
   SAMPLES and SFML REFERENCE


sf::RectangleShape     //square


sf::RectangleShape line(sf::Vector2f(150, 5));  //line
line.rotate(45);


 sf::CircleShape shape(50);                     //line
shape.setFillColor(sf::Color(150, 50, 250));

    // set a 10-pixel wide orange outline
    shape.setOutlineThickness(10);
    shape.setOutlineColor(sf::Color(250, 150, 100));


    //Create not resizable window with Close buttons
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tic-Tac-Toe", sf::Style::Titlebar | sf::Style::Close);
    sf::Event ev_1;

    //Load a music to play
    sf::Music music;
    if (!music.openFromFile("sound.ogg"))
        return EXIT_FAILURE;
    music.setVolume(20);

    // Play the music
    music.play();

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (window.pollEvent(ev_1))
        {
            // Close window: exit
            if (ev_1.type == sf::Event::Closed)
               window.close();
        }

        //RENDER phase
        window.clear();     //clear odl frame

        //Draw here

        window.display();   // Update the window  (end of drawing phase ^_^ )
    }

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        return EXIT_FAILURE;
    sf::Text text("Hello SFML", font, 50);


    // Declare and load a texture
       sf::Texture texture;
       texture.loadFromFile("texture.png");

    // Create a sprite
       sf::Sprite sprite;
       sprite.setTexture(texture);

       sprite.setTextureRect(sf::IntRect(10, 10, 50, 30));
       sprite.setColor(sf::Color(255, 255, 255, 200));
       sprite.setPosition(100, 25);

    // Draw it
    window.draw(sprite)

    //get mouse position
    {
        //relative to screen
        sf::Mouse::getPosition().x

        //relative to window
         sf::Mouse::getPosition(window).x
*/