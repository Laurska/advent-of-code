#include "fileutility.hh"

void FileUtility::resetInputFileState(std::ifstream& file) {
	file.clear();
	file.seekg(0, std::ios::beg);
}
