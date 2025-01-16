#include "methods.h"

int getMax(std::vector<Item> &items, const std::string &attribute)
{
    int max = 0;
    if (attribute == "age")
    {
        for (int i = 0; i < items.size(); i++)
        { // finding the biggest age amongst the items
            if (items[i].age > max)
            {
                max = items[i].age;
            }
        }
        return max;
    }

    if (attribute == "rarityScore")
    {
        for (int i = 0; i < items.size(); i++)
        { // finding the biggest rarity amongst the items
            if (items[i].rarityScore > max)
            {
                max = items[i].rarityScore;
            }
        }
        return max;
    }
}

// min = age - ageWindow
// max = age + ageWindow
// rarityScore = (1 - probability) * (1 + item.age/ageMax)
void calculateRarityScores(std::vector<Item> &items, int ageWindow)
{
    for (int i = 0; i < items.size(); i++)
    {
        double countSimilar = 1;
        double countTotal = 1;
        int j = i - 1;
        double ageMax = getMax(items, "age");
        while (j >= 0)
        {
            if (items[i].age - items[j].age <= ageWindow)
            {
                countTotal++;
                if (items[j].type == items[i].type && items[j].origin == items[i].origin)
                {
                    countSimilar++;
                }
                j--;
            }
            else
            {
                break;
            }
        }
        j = i + 1;
        while (j < items.size())
        {
            if (items[j].age - items[i].age <= ageWindow)
            {
                countTotal++;
                if (items[j].type == items[i].type && items[j].origin == items[i].origin)
                {
                    countSimilar++;
                }
                j++;
            }
            else
            {

                break;
            }
        }

        double prob = countSimilar / countTotal;
        items[i].rarityScore = (1 - prob) * (1 + ((double)items[i].age / ageMax));
    }
}
