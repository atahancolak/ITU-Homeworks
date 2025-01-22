#include "tweet.h"

void bubbleSort(std::vector<Tweet> &tweets, const std::string &sortBy, bool ascending)
{
    if (sortBy == "tweetId")
    {
        bool isSwpOccured = false;
        for (int i = 0; i < tweets.size() - 1; i++)
        {
            for (int j = 0; j < tweets.size() - i - 1; j++)
            {

                if (ascending ? tweets[j].tweetID > tweets[j + 1].tweetID
                              : tweets[j].tweetID < tweets[j + 1].tweetID)
                {
                    Tweet key = tweets[j + 1];
                    tweets[j + 1] = tweets[j];
                    tweets[j] = key;
                    isSwpOccured = 1;
                }
            }
            if (!isSwpOccured)
                break;
        }
    }

    if (sortBy == "retweetCount")
    {
        bool isSwpOccured = false;
        for (int i = 0; i < tweets.size() - 1; i++)
        {
            for (int j = 0; j < tweets.size() - i - 1; j++)
            {

                if (ascending ? tweets[j].retweetCount > tweets[j + 1].retweetCount
                              : tweets[j].retweetCount < tweets[j + 1].retweetCount)
                {
                    Tweet key = tweets[j + 1];
                    tweets[j + 1] = tweets[j];
                    tweets[j] = key;
                    isSwpOccured = 1;
                }
            }
            if (!isSwpOccured)
                break;
        }
    }

    if (sortBy == "favoriteCount")
    {
        bool isSwpOccured = false;
        for (int i = 0; i < tweets.size() - 1; i++)
        {
            for (int j = 0; j < tweets.size() - i - 1; j++)
            {

                if (ascending ? tweets[j].favoriteCount > tweets[j + 1].favoriteCount
                              : tweets[j].favoriteCount < tweets[j + 1].favoriteCount)
                {
                    Tweet key = tweets[j + 1];
                    tweets[j + 1] = tweets[j];
                    tweets[j] = key;
                    isSwpOccured = 1;
                }
            }
            if (!isSwpOccured)
                break;
        }
    }
}

void insertionSort(std::vector<Tweet> &tweets, const std::string &sortBy, bool ascending)
{
    if (sortBy == "tweetID")
    {
        for (int i = 1; i < tweets.size(); ++i)
        {
            Tweet key = tweets[i];
            int k = i - 1;

            while (k >= 0 && (ascending ? (tweets[k].tweetID > key.tweetID)
                                        : (tweets[k].tweetID < key.tweetID)))
            {
                tweets[k + 1] = tweets[k];
                k = k - 1;
            }
            tweets[k + 1] = key;
        }
    }

    if (sortBy == "retweetCount")
    {
        for (int i = 1; i < tweets.size(); ++i)
        {
            Tweet key = tweets[i];
            int k = i - 1;

            while (k >= 0 && (ascending ? (tweets[k].retweetCount > key.retweetCount)
                                        : (tweets[k].retweetCount < key.retweetCount)))
            {
                tweets[k + 1] = tweets[k];
                k = k - 1;
            }
            tweets[k + 1] = key;
        }
    }

    if (sortBy == "favoriteCount")
    {
        for (int i = 1; i < tweets.size(); ++i)
        {
            Tweet key = tweets[i];
            int k = i - 1;

            while (k >= 0 && (ascending ? (tweets[k].favoriteCount > key.favoriteCount)
                                        : (tweets[k].favoriteCount < key.favoriteCount)))
            {
                tweets[k + 1] = tweets[k];
                k = k - 1;
            }
            tweets[k + 1] = key;
        }
    }
}

void merge(std::vector<Tweet> &tweets, int left, int mid, int right, const std::string &sortBy, bool ascending)
{
    int lSize = mid - left + 1;
    int rSize = right - mid;

    std::vector<Tweet> tempLeft(lSize);
    std::vector<Tweet> tempRight(rSize);

    for (int i = 0; i < lSize; i++)
    {
        tempLeft[i] = tweets[left + i];
    }
    for (int j = 0; j < rSize; j++)
    {
        tempRight[j] = tweets[mid + 1 + j];
    }

    int a = 0, b = 0;
    int c = left;

    if (sortBy == "tweetID")
    {
        while (a < lSize && b < rSize)
        {
            if (ascending ? tempLeft[a].tweetID <= tempRight[b].tweetID
                          : tempLeft[a].tweetID >= tempRight[b].tweetID)
            {
                tweets[c] = tempLeft[a];
                a++;
            }
            else
            {
                tweets[c] = tempRight[b];
                b++;
            }
            c++;
        }
    }

    if (sortBy == "retweetCount")
    {
        while (a < lSize && b < rSize)
        {
            if (ascending ? tempLeft[a].retweetCount <= tempRight[b].retweetCount
                          : tempLeft[a].retweetCount >= tempRight[b].retweetCount)
            {
                tweets[c] = tempLeft[a];
                a++;
            }
            else
            {
                tweets[c] = tempRight[b];
                b++;
            }
            c++;
        }
    }

    if (sortBy == "favoriteCount")
    {
        while (a < lSize && b < rSize)
        {
            if (ascending ? tempLeft[a].favoriteCount <= tempRight[b].favoriteCount
                          : tempLeft[a].favoriteCount >= tempRight[b].favoriteCount)
            {
                tweets[c] = tempLeft[a];
                a++;
            }
            else
            {
                tweets[c] = tempRight[b];
                b++;
            }
            c++;
        }
    }

    while (a < lSize)
    {
        tweets[c] = tempLeft[a];
        a++;
        c++;
    }

    while (b < rSize)
    {
        tweets[c] = tempRight[b];
        b++;
        c++;
    }
}

void mergeSort(std::vector<Tweet> &tweets, int left, int right, const std::string &sortBy, bool ascending)
{

    if (left < right)
    {

        int mid = left + (right - left) / 2;
        mergeSort(tweets, left, mid, sortBy, ascending);
        mergeSort(tweets, mid + 1, right, sortBy, ascending);
        merge(tweets, left, mid, right, sortBy, ascending);
    }
    else
    {
        return;
    }
}