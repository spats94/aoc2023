#include <iostream>
#include <string> // подключаем строки
#include <fstream> // подключаем файлы
#include <limits>
#include <vector>
#include <map>

void day1_part1()
{
    std::string s; // сюда будем класть считанные строки
    std::ifstream file("/home/user/CLionProjects/aoc2023/input.txt"); // файл из которого читаем (для линукс путь будет выглядеть по другому)
    std::vector<int> output;
    while(getline(file, s)){ // пока не достигнут конец файла класть очередную строку в переменную (s)
        std::string value = "";
        for (const auto c : s)
        {
            if (isdigit(c))
            {
                value += c;
            }
        }
        const auto value_temp = value;
        auto test = value_temp[value_temp.length() - 1];
        value = "";
        value += value_temp[0];
        value += value_temp[value_temp.length() - 1];
        if (value.length() == 1)
        {
            value += value;
        }
        output.emplace_back(stoi(value));
    }
    file.close();
    int result = 0;
    for (const auto value : output)
    {
        result += value;
    }
    std::cout << "Answer 1 part: " << result << std::endl;
}

void day1_part2()
{
    std::string s; // сюда будем класть считанные строки
    std::ifstream file("/home/user/CLionProjects/aoc2023/day1/input.txt"); // файл из которого читаем (для линукс путь будет выглядеть по другому)
    std::vector<int> output;
    std::map<int, std::string> map_digits =
      { {1 , "one"},
        {2 , "two"},
        {3 , "three"},
        {4 , "four"},
        {5 , "five"},
        {6 , "six"},
        {7 , "seven"},
        {8 , "eight"},
        {9 , "nine"},};
    std::map<int, std::string> map_digits1 =
  { {1 , "1"},
    {2 , "2"},
    {3 , "3"},
    {4 , "4"},
    {5 , "5"},
    {6 , "6"},
    {7 , "7"},
    {8 , "8"},
    {9 , "9"},};
    while(getline(file, s)) // пока не достигнут конец файла класть очередную строку в переменную (s)
    {
        std::map<int, std::string> pos_digits;
        for (const auto& serach_number : map_digits)
        {
            int pos_start = 0;
            while (pos_start != std::string::npos)
            {
                const auto pos = s.find(serach_number.second, pos_start);
                if (pos != std::string::npos)
                {
                    pos_digits[pos] = std::to_string(serach_number.first);
                    pos_start = pos + 1;
                } else {
                    break;
                }

            }
        }
        for (const auto& serach_number : map_digits1)
        {
            int pos_start = 0;
            while (pos_start != std::string::npos)
            {
                const auto pos = s.find(serach_number.second, pos_start);
                if (pos != std::string::npos)
                {
                    pos_digits[pos] = std::to_string(serach_number.first);
                    pos_start = pos + 1;
                } else {
                    break;
                }

            }
        }
        output.emplace_back(std::stoi(pos_digits.begin()->second + std::prev(pos_digits.end())->second));

    }
    file.close();
    int result = 0;
    for (const auto value : output)
    {
        result += value;
    }
    std::cout << "Answer 1 part: " << result << std::endl;
}


int main()
{
    day1_part2();
    return 0;
}
