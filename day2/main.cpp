#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>

struct Balls
{
  std::string color = "";
  int count = 0;
};

struct Round
{
  std::vector<Balls> balls;
};

struct Game
{
  std::vector<Round> rounds;
};

void read_game(std::string game_raw, Round& round) {
  const std::regex raund_regex("(\\d+ \\w+)");
  std::smatch matches;
  while (std::regex_search(game_raw, matches, raund_regex)) {
    std::string raw_balls = matches[0].str();
    std::smatch match;
    Balls balls;
    std::regex_search(raw_balls, match, std::regex("([a-z]+)"));
    balls.color = match[0].str();
    std::regex_search(raw_balls, match, std::regex("(\\d+)"));
    balls.count = stoi(match[0].str());
    round.balls.push_back(balls);
    game_raw = matches.suffix();
  }
}

std::vector<Game> read_games()
{
  std::vector<Game> games;
  std::string s; // сюда будем класть считанные строки
  std::ifstream file("/home/user/CLionProjects/aoc2023/day2/input.txt"); // файл из которого читаем (для линукс путь будет выглядеть по другому)
  while(getline(file, s)) {
    Game game;
    const std::regex raund_regex("((\\d+ \\w+),* *)+");
    std::smatch matches;
    while (std::regex_search(s, matches, raund_regex)) {
      Round round;
      read_game(matches[0].str(), round);
      s = matches.suffix();
      game.rounds.push_back(round);
    }
    games.push_back(game);
  }
  file.close();
  return games;
}

void solve_part_1(const std::vector<Game>& games) {
  int result = 0;
  std::map<std::string, int> map_max_count = {{"red", 12}, {"green", 13}, {"blue", 14}};
  int id = 1;
  for (const auto&[rounds] : games) {
    bool imposible_game = false;
    for (const auto&[balls] : rounds) {
      std::map<std::string, int> map_count;
      for (const auto&[color, count] : balls) {
        if (auto search = map_count.find(color); search != map_count.end()) {
          map_count[color] += count;
        } else {
          map_count[color] = count;
        }
      }
      for (const auto&[color, count]:map_count) {
        if (map_max_count[color] < count) {
          imposible_game = true;
        }
      }
    }
    result += imposible_game ? 0 : id;
    id++;
  }
  std::cout << "Answer 1 part: " << result << std::endl;
}

void solve_part_2(const std::vector<Game>& games) {
  int result = 0;
  for (const auto&[rounds] : games) {
    std::map<std::string, int> map_count;
    for (const auto&[balls] : rounds) {
      for (const auto&[color, count] : balls) {
        if (auto search = map_count.find(color); search != map_count.end()) {
          map_count[color] = (map_count[color] > count) ? map_count[color] : count;
        } else {
          map_count[color] = count;
        }
      }
    }
    int power_game = 1;
    for (const auto& [color, count] : map_count) {
      power_game *= count;
    }
    result += power_game;
  }
  std::cout << "Answer 2 part: " << result << std::endl;
}

int main()
{
  const auto games = read_games();
  solve_part_1(games);
  solve_part_2(games);
  return 0;
}
