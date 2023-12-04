#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <cmath>

struct Card {
  std::vector<int> winner_cart;
  std::vector<int> your_cards;
};

void read_winner_cards(const std::string& s, Card& card)
{
  const std::regex raund_regex(": *(\\d+ *)+\\|");
  std::smatch matches;
  std::regex_search(s, matches, raund_regex);
  std::string winner_cards = matches[0].str();
  while (std::regex_search(winner_cards, matches, std::regex("(\\d+)")))
  {
    card.winner_cart.push_back(stoi(matches[0].str()));
    winner_cards = matches.suffix();
  }
  std::sort(card.winner_cart.begin(), card.winner_cart.end());
}

void read_your_cards(const std::string& s, Card& card)
{
  const std::regex raund_regex("\\| *(\\d+ *)+");
  std::smatch matches;
  std::regex_search(s, matches, raund_regex);
  std::string winner_cards = matches[0].str();
  while (std::regex_search(winner_cards, matches, std::regex("(\\d+)")))
  {
    card.your_cards.push_back(stoi(matches[0].str()));
    winner_cards = matches.suffix();
  }
  std::sort(card.your_cards.begin(), card.your_cards.end());
}

std::vector<Card> read_games()
{
  std::vector<Card> cards;
  std::string s; // сюда будем класть считанные строки
  std::ifstream file("/home/user/CLionProjects/aoc2023/day4/input.txt"); // файл из которого читаем (для линукс путь будет выглядеть по другому)
  while(getline(file, s)) {
    Card card;
    read_winner_cards(s, card);
    read_your_cards(s, card);
    cards.push_back(card);
  }
  file.close();
  return cards;
}

void solve_part_1(const std::vector<Card>& cards) {
  int result = 0;
  for (const auto& [winner_cart, your_cards] : cards)
  {
    int count_winner_cards = 0;
    for (const auto your_card : your_cards)
    {
      if (std::find(winner_cart.begin(), winner_cart.end(), your_card) != winner_cart.end())
      {
        count_winner_cards++;
      }
    }
    result += (count_winner_cards == 0) ? 0 : pow(2, count_winner_cards - 1);
  }
  std::cout << "Answer 1 part: " << result << std::endl;
}

void solve_part_2(const std::vector<Card>& cards) {

  std::vector<int> count_cards;
  count_cards.resize(cards.size(), 1);
  int i_game = 0;
  for (const auto& [winner_cart, your_cards] : cards)
  {
    int count_winner_cards = 0;
    for (const auto your_card : your_cards)
    {
      if (std::find(winner_cart.begin(), winner_cart.end(), your_card) != winner_cart.end())
      {
        count_winner_cards++;
      }
    }
    for (int i = i_game + 1; i <= i_game + count_winner_cards; i++)
    {
      count_cards[i] += count_cards[i_game];
    }
    i_game++;
  }
  int result = 0;
  for (const auto cout_card: count_cards)
  {
    result += cout_card;
  }
  std::cout << "Answer 1 part: " << result << std::endl;
}

int main()
{
  const auto cards = read_games();
  solve_part_1(cards);
  solve_part_2(cards);
  return 0;
}
