#include "methods.h"

std::vector<Item> countingSort(std::vector<Item> &items, const std::string &attribute, bool ascending)
{
    if (attribute == "age")
    {
        int max = getMax(items, "age");

        std::vector<int> locationVector(max + 1, 0);

        for (int i = 0; i < items.size(); i++)
        { // now locationVector holds the number of occurences of the ages in the equal index
            locationVector[items[i].age]++;
        }

        for (int i = 1; i < locationVector.size(); i++)
        { // now locationVector has the starting indexes for the age occurenses
            locationVector[i] = locationVector[i] + locationVector[i - 1];
        }

        std::vector<Item> sorted(items.size());

        if (ascending)
        {

            for (int i = items.size() - 1; i >= 0; i--)
            {
                sorted[locationVector[items[i].age] - 1] = items[i];
                locationVector[items[i].age]--;
            }
        }
        else
        {
            for (int i = 0; i < items.size(); i++)
            {
                sorted[items.size() - locationVector[items[i].age]] = items[i];
                locationVector[items[i].age]--;
            }
        }

        return sorted;
    }
}

// Function to heapify a subtree rooted with node i in the array of items
void heapify(std::vector<Item> &items, int n, int i, bool descending)
{
    int k = (descending) ? -1 : 1; 
    
    int max = i; 
    int lchild = 2 * i + 1; 
    int rchild = 2 * i + 2; 

    
    if (lchild < n && items[lchild].rarityScore * k > items[max].rarityScore * k) {
        max = lchild;
    }

    
    if (rchild < n && items[rchild].rarityScore * k > items[max].rarityScore * k) {
        max = rchild;
    }

    // if the largest is not the root swapp and recursively heapify
    if (max != i) {
        
        Item temp = items[i];
        items[i] = items[max];
        items[max] = temp;
        heapify(items, n, max, descending);
    }
}
// Function to perform heap sort on rarityScore scores of items
std::vector<Item> heapSortByRarity(std::vector<Item> &items, bool descending)
{
    int n = items.size();
    for (int i = (n / 2) - 1; i >= 0; i--)
    {
        heapify(items, n, i, descending);
    }

    for (int i = n - 1; i >= 0; i--)
    {
        Item temp = items[i];
        items[i] = items[0];
        items[0] = temp;

        heapify(items, i, 0, descending);
    }
    return items;
}
