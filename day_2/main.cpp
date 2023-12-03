#include <iostream>
#include <istream>
#include <sstream>
#include <vector>
#include <map>

class Game {
    private:
        bool valid = true;

        int get_game_id(std::string &game_buffer) {
            int game_id = -1;
            std::size_t tkn_pos = game_buffer.find(":");

            if (tkn_pos != std::string::npos) {
                game_id = std::stoi(game_buffer.substr(game_buffer.find(" "), tkn_pos));
            }
            
            return game_id;
        }

        void check_number_of_cubes(std::map<std::string, int> &map) {
            std::map<std::string, int> constraints{{"red",12}, {"blue",14}, {"green", 13}};
            for (const auto& [key, value] : map) {
                if (value > constraints[key]) {
                    this->valid = false;
                }
            }
        }


        void parse_saved_results(std::string &saved_results) {
            std::istringstream linestream(saved_results);
            std::vector<std::string> tokens;
            for(std::string each; std::getline(linestream, each, ';'); tokens.push_back(each)); 
            
            for (const std::string &draw : tokens) {
                std::istringstream drawstream(draw);
                std::map<std::string, int> result_map;
                for (std::string cube_tokens; std::getline(drawstream, cube_tokens, ',');) {
                    std::istringstream cubestream(cube_tokens.erase(0, cube_tokens.find_first_not_of(" ")));
                    std::string cube_color; 
                    std::string number_of_cubes;
                    
                    std::getline(cubestream, number_of_cubes, ' ');
                    std::getline(cubestream, cube_color, ' ');
                    
                    if (cube_color == "red" || cube_color == "blue" || cube_color == "green") {
                        result_map[cube_color] = std::stoi(number_of_cubes);
                    }
                }
                if (!result_map.empty()) {
                    this->check_number_of_cubes(result_map);
                    this->results.push_back(result_map);
                }
            }
        }
 
    public:
        std::size_t id;
        std::vector<std::map<std::string, int>> results;
        
        Game(std::string save_data) {
            id = this->get_game_id(save_data);
            std::string saved_results = save_data.substr(save_data.find(":")+1, save_data.size());
            parse_saved_results(saved_results);
        }

        bool is_valid() {
            return this->valid;
        }
};

int main(int argc, char **argv) {
    std::string game_buffer;
    int flag = 0;

    while (getline(std::cin, game_buffer) && game_buffer.size() > 0) {
        Game g = Game(game_buffer);
        if (g.is_valid()) {
            flag += g.id;
        }
    }

    std::cout << "Flag: " << flag << std::endl;

    return 0;
}

