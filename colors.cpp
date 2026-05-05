#include "colors.h"

const Color darkGray = {26, 31, 10, 255};
const Color green  = {47, 230, 23, 255};

std::vector<Color> GetCellColors()
{
    return {darkGray, green};
}