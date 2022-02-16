#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <map>
#include <fstream>

auto cmp = [](std::pair<std::string, int> const & a, std::pair<std::string, int> const & b)
{
    return a.second != b.second?  a.second > b.second : a.first < b.first;
};

std::string prepare(std::string in, const std::vector<char>& signs) {
    for(int i = 0; i < in.length(); i++) if (in[i] <= 'Z' && in[i] >= 'A') in[i] = in[i] - ('Z' - 'z');

    for(char s : signs) in.erase(std::remove(in.begin(), in.end(), s), in.end());
    return in;
}

int main(){
    std::vector<char> signs = {'.', ',', '!', '?'};
    std::fstream file(R"(C:\Users\Egorchan\Documents\GitHub\Cpp Homeworks\TextFinder\exampleOfText.txt)");
    std::string text;
    std::map<std::string, int> words;
    if (file.is_open()){
        std::string word;
        while (!file.eof()){
            file >> word;
            words[prepare(word, signs)]++;
        }
    }
    file.close();

    int N;
    std::cin >> N;

    std::vector<std::pair<std::string, int>> result;

    result.reserve(words.size());
    for(const auto& item : words) result.emplace_back(item);

    std::sort(result.begin(), result.end(), cmp);

    for(int i = 0; i < N; i++) std::cout << result[i].first << ": " << result[i].second << std::endl;
}