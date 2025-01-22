#include "tweet.h"

int binarySearch(const std::vector<Tweet> &tweets, long long key, const std::string &sortBy)
{

    int left = 0;
    int right = tweets.size() - 1;
    if (sortBy == "tweetID")
    {
        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (key == tweets[mid].tweetID)
            {
                return mid;
            }
            else if (key < tweets[mid].tweetID)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
    }
    else if (sortBy == "retweetCount")
    {
        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (key == tweets[mid].retweetCount)
            {
                return mid;
            }
            else if (key < tweets[mid].retweetCount)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
    }
    else if (sortBy == "favoriteCount")
    {
        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (key == tweets[mid].favoriteCount)
            {
                return mid;
            }
            else if (key < tweets[mid].favoriteCount)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
    }
    else
    {
        return -1;
    }
    return -1;
}

int countAboveThreshold(const std::vector<Tweet> &tweets, const std::string &metric, int threshold)
{
    int result = 0;
    if (metric == "retweetCount")
    {
        for (int i = 0; i < tweets.size(); i++)
        {
            if (tweets[i].retweetCount > threshold)
            {
                result++;
            }
        }
    }
    else if (metric == "favoriteCount")
    {
        for (int i = 0; i < tweets.size(); i++)
        {
            if (tweets[i].favoriteCount > threshold)
            {
                result++;
            }
        }
    }
    else
    {

        return 0;
    }
    return result;
}
