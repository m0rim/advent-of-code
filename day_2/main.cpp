#include <iostream>
#include <sstream>
#include <vector>
#include <map>

class Game {
    private:
        std::size_t id;
        std::vector<std::map<std::string, int>> results;
        bool valid = true;

        void parse_game_id(std::string &game_buffer) {
            std::size_t tkn_pos = game_buffer.find(":");

            if (tkn_pos != std::string::npos) {
                this->id = std::stoi(game_buffer.substr(game_buffer.find(" "), tkn_pos));
            }
        }

        void check_number_of_cubes(std::map<std::string, int> &map) {
            std::map<std::string, int> constraints{{"red",12}, {"green", 13}, {"blue",14}};
            for (const auto& [key, value] : map) {
                if (value > constraints[key]) {
                    this->valid = false;
                }
            }
        }


        void parse_saved_results(std::string saved_results) {
            std::istringstream linestream(saved_results);
            
            for (std::string draw; std::getline(linestream, draw, ';'); ) {
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
        Game(std::string save_data) {
            this->parse_game_id(save_data);
            this->parse_saved_results(save_data.substr(save_data.find(":")+1, save_data.size()));
        }

        std::size_t get_id() {
            return this->id
        }

        bool is_valid() {
            return this->valid;
        }
};

int main(int argc, char **argv) {
    std::string game_buffer;
    int flag = 0;

    while (getline(std::cin, game_buffer) && game_buffer.size() > 0) {
        Game game = Game(game_buffer);
        if (game.is_valid()) {
            flag += game.id;
        }
    }

    std::cout << "Flag: " << flag << std::endl;

    return 0;
}

