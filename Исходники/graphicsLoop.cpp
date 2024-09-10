///Transforms the map into a sfml image for rendering.
sf::Image renderMap(const terrain* map, sf::Image image){
    for (auto y = 0u; y < map->h_map.size(); y++) {
        for (auto x = 0u; x < map->h_map[0].size(); x++) {
            float value = map->h_map[y][x] * 127 + 128;
            float red = value;
            float blue = value;
            float green = value;
            if (map->features->is_ocean[y][x] || map->features->is_lake[y][x] || map->features->is_river[y][x]) {
                red = 0;
                blue = value * 0.75f;
                green = value * 0.55f;
            } 
            else {
                red = 0.50f * value;
                blue = blue*blue*blue*blue / (255 * 255 * 255);
                green = value;
            }
            
            sf::Color pixel(sf::Color(red, green, blue));
            image.setPixel(x , y, pixel);
        }
    }
    return image;
}