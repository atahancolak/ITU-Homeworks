#include "methods.h"

std::vector<Item> readItemsFromFile(const std::string &filename)
{
    std::vector<Item> items;
    std::ifstream file(filename);

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        Item item;

        char comma;
        if (ss >> item.age >> comma >> item.type >> comma >> item.origin >> comma >> item.rarityScore)
        {
            items.push_back(item);
        }
    }

    file.close();
    return items;
}

void writeItemsToFile(const std::string &filename, const std::vector<Item> &items)
{
    std::ofstream output(filename);
    output << "age,type,origin,rarity\n";
    int size = items.size();
    int i = 0;
    while (i < size)
    {
        output << items[i].age << "," << items[i].type << "," << items[i].origin << "," << items[i].rarityScore <<"\n";
        i++;
    }
    output.close();
}
