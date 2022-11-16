#include <SFML/System/Sleep.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>

using namespace std;

class visualizer {
public:
    sf::RenderWindow window;
    vector<double> list;
    int n;
    double max_val;
    double win_w;
    double win_h;
    double win_pad;
    double gap;
    double bar_w;
    double max_bar_h;
    double min_x;
    double min_y;
    double fps;

    // Constructor
    visualizer(vector<double> vec, int win_width, int win_height, double framerate) {
        // Get window height and width as parameters
        win_w = win_width;
        win_h = win_height;

        window.create(sf::VideoMode(win_w, win_h), "Visualizer");
        list = vec;
        n = vec.size();
        fps = framerate;
        
        // Find maximum in list
        for (int i = 0; i < n; i++) {
            max_val = max(max_val, list[i]);
        }

        // Calculate window padding and gap between bars
        win_pad = 0.05 * win_w;
        gap = 0.01 * win_w;

        // Calculate width of each bar and maximum height based on win_w,
        // win_h, padding, and gap
        bar_w = (win_w - 2 * win_pad - (n - 1) * gap) / n;
        max_bar_h = win_h - 2 * win_pad;
    }

    // Draw all elemnents
    void draw_all() {
        for (int i = 0; i < n; i++) {
            draw_bar(list[i], win_pad + i * (bar_w + gap));
        }

        window.display();
        sf::Time wait = sf::seconds(2);
        sf::sleep(wait);
        window.clear();
        sf::sleep(wait);
    }
    
    // Moves elemnt list[i] to position newpositions[i]
    void move(vector<double> new_positions) {
        for (int f = 0; f <= 60; f++) {
            for (int i = 0; i < n; i++) {
                draw_bar(list[i], win_pad + i * (bar_w + gap));
            }
        }
    }

    // Draws bar using SFML Rectangle
    void draw_bar(double val, int x_pos) {
        sf::RectangleShape bar;
        double bar_h = max_bar_h * val / max_val;
        double bar_x = win_pad + x_pos;
        double bar_y = win_h - win_pad - bar_h;
        // std::cout << val << " " << bar_w << " " << bar_h << " " << bar_x << " " << bar_y;
        bar.setSize(sf::Vector2f(bar_w, bar_h));
        bar.setPosition(bar_x, bar_y);
        bar.setFillColor(sf::Color::Red);
        window.draw(bar);
    }

    void quit() {
        window.close();
    }
    
};
