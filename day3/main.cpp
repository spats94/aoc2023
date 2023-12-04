#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>

std::map<std::pair<int,int>, std::string> create_map()
{
  std::map<std::pair<int,int>, std::string> map_symbols;
  std::string s;
  std::ifstream file("/home/user/CLionProjects/aoc2023/day3/input.txt"); // файл из которого читаем (для линукс путь будет выглядеть по другому)
  int row = 0;
  while(getline(file, s)) {
    for (int col = 0; col < s.length(); col++)
    {
      map_symbols[std::make_pair(row,col)] = s[col];
    }
    row++;
  }
  file.close();
  return map_symbols;
}

std::pair<int,int> get_max_row_and_col(const std::map<std::pair<int,int>, std::string>& map)
{
  int max_row = 0;
  int max_col = 0;
  for (const auto& [coord, value] : map)
  {
    max_row = (coord.first > max_row) ? coord.first : max_row;
    max_col = (coord.second > max_col) ? coord.second : max_col;
  }
  return {max_row, max_col};
}

bool check_number_engine(const int row, const int col, const std::map<std::pair<int,int>, std::string>& map_symbols)
{
  std::vector<std::pair<int, int>> additional_coords;
  additional_coords.emplace_back(1,1);
  additional_coords.emplace_back(1,0);
  additional_coords.emplace_back(1,-1);
  additional_coords.emplace_back(0,-1);
  additional_coords.emplace_back(-1,-1);
  additional_coords.emplace_back(-1,0);
  additional_coords.emplace_back(-1,1);
  additional_coords.emplace_back(0,1);
  for (const auto& [add_row, add_col] : additional_coords)
  {
    const auto new_row = row + add_row;
    const auto new_col = col + add_col;
    if (auto search = map_symbols.find(std::make_pair(new_row, new_col)); search == map_symbols.end())
    {
      continue;
    }
    std::string symb = map_symbols[std::make_pair(new_row, new_col)];
    if (auto symb = map_symbols[std::make_pair(new_row, new_col)]; symb != "." && !std::isdigit(symb[0]))
    {
      return true;
    }
  }
  return false;
}

void solve_part1(std::map<std::pair<int,int>, std::string>& map_symbols)
{
  const auto [max_row, max_col] = get_max_row_and_col(map_symbols);
  std::vector<int> numbers_engine;
  bool is_number_engine = false;
  std::string number_engine = "";
  for (int row = 0; row <= max_row+2; row++)
  {
    for (int col = 0; col <= max_col+2; col++)
    {
      auto el = map_symbols[std::make_pair(row,col)];
      if (!std::isdigit(el[0]) && number_engine != "")
      {
        numbers_engine.emplace_back(stoi(number_engine));
        is_number_engine = false;
        number_engine = "";
      }
      if (std::isdigit(el[0]))
      {
        number_engine += el;
        is_number_engine |= check_number_engine(row, col, map_symbols);
      }
    }
    if (number_engine != "")
    {
      numbers_engine.emplace_back(stoi(number_engine));
      is_number_engine = false;
      number_engine = "";
    }
  }
  int result = 0;
  for (const auto& number: numbers_engine)
  {
    result += number;
  }
  std::cout << "Answer 1 part: " << result << std::endl;
}

int main()
{
  auto map_symbols = create_map();
  solve_part1(map_symbols);
  return 0;
}
