#include <vector>
#include "node.h"
#include "../fs/file.h"

using std::vector;

vector<node*>* charDistribution(file* _file);

void saveCharDistributionToFile(file* _file, vector<node*>* char_distribution);

vector<node*>* readCharDistributionFromFile(file* _file);