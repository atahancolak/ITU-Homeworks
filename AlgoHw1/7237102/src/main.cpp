#include "tweet.h"

int main() 
{
    std::vector<Tweet> tweets = readTweetsFromFile("/workspaces/BLG335E_HW1/Code/data/sizes/tweets50K.csv");
    clock_t now = clock();
    //insertionSort(tweets,"retweetCount",1);
    //bubbleSort(tweets,"retweetCount",1);
    //mergeSort(tweets,0,tweets.size()-1,"retweetCount",1);
    //binarySearch(tweets, 1773335, "tweetID");
    //countAboveThreshold(tweets,"favoriteCount", 250 );
    clock_t dur = clock()-now;
    std::cout<<(float)dur/CLOCKS_PER_SEC<<"\n";
    writeTweetsToFile("sorted",tweets);
}
