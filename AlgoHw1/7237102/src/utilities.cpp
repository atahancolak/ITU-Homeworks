#include "tweet.h"
using namespace std;
std::vector<Tweet> readTweetsFromFile(const std::string &filename)
{
    std::vector<Tweet> tweets;
    std::ifstream file(filename);

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        Tweet tweet;

        char comma;
        if (ss >> tweet.tweetID >> comma >> tweet.retweetCount >> comma >> tweet.favoriteCount)
        {
            tweets.push_back(tweet);
        }
    }

    file.close();
    return tweets;
}
void writeTweetsToFile(const std::string &filename, const std::vector<Tweet> &tweets)
{
    std::ofstream output(filename);
    output << "tweetID,retweetCount,favoriteCount\n";
    int size = tweets.size();
    int i = 0;
    while (i < size)
    {
        output << tweets[i].tweetID << "," << tweets[i].retweetCount << "," << tweets[i].favoriteCount << "\n";
        i++;
    }
    output.close();
}