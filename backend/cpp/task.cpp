#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

struct File {
    int id;
    std::string name;
    std::vector<std::string> categories;
    int numCategories;
    int parent;
    int size;
};

/**
 * Task 1
 */
std::vector<std::string> leafFiles(std::vector<File> files) {
	// Mapping from file id to their name, with capacity = # of files
	std::unordered_map<int, std::string> id_mappings(files.size());

	for (File f: files) {
		if (f.parent != -1) {
			// If parent exists, delete
			if(!id_mappings.erase(f.parent)) {
				// Parent may be after however (e.g no items erased, erase returns 0)
				// So we create an entry
				// Id prefer to use std::optional but thas C++17
				id_mappings[f.parent];
			}
		}

		// Normal insert
		if (id_mappings.count(f.id))
			//If our id is already in there, we are a parent - we should just delete
			id_mappings.erase(f.id);
		else
			// Else insert happily
			id_mappings[f.id] = f.name;
	}

	std::vector<std::string> filenames;
	std::transform(id_mappings.begin(), id_mappings.end(), std::back_inserter(filenames), [](std::pair<int, std::string> kv){ return kv.second;} );

	return filenames;
}

/**
 * Task 2
 */
std::vector<std::string> kLargestCategories(std::vector<File> files, int k) {
    return std::vector<std::string>();
}

/**
 * Task 3
 */
int largestFileSize(std::vector<File> files) {
    return 0;
}

int main(void) {
    std::vector<File> testFiles{
        { .id = 1, .name = "Document.txt", .categories = {"Documents"}, .numCategories = 1, .parent = 3, .size = 1024 },
        { .id = 2, .name = "Image.jpg", .categories = {"Media", "Photos"}, .numCategories = 2, .parent = 34, .size = 2048 },
        { .id = 3, .name = "Folder", .categories = {"Folder"}, .numCategories = 1, .parent = -1, .size = 0 },
        { .id = 5, .name = "Spreadsheet.xlsx", .categories = {"Documents", "Excel"}, .numCategories = 2, .parent = 3, .size = 4096 },
        { .id = 8, .name = "Backup.zip", .categories = {"Backup"}, .numCategories = 1, .parent = 233, .size = 8192 },
        { .id = 13, .name = "Presentation.pptx", .categories = {"Documents", "Presentation"}, .numCategories = 2, .parent = 3, .size = 3072 },
        { .id = 21, .name = "Video.mp4", .categories = {"Media", "Videos"}, .numCategories = 2, .parent = 34, .size = 6144 },
        { .id = 34, .name = "Folder2", .categories = {"Folder"}, .numCategories = 1, .parent = 3, .size = 0 },
        { .id = 55, .name = "Code.py", .categories = {"Programming"}, .numCategories = 1, .parent = -1, .size = 1536 },
        { .id = 89, .name = "Audio.mp3", .categories = {"Media", "Audio"}, .numCategories = 2, .parent = 34, .size = 2560 },
        { .id = 144, .name = "Spreadsheet2.xlsx", .categories = {"Documents", "Excel"}, .numCategories = 2, .parent = 3, .size = 2048 },
        { .id = 233, .name = "Folder3", .categories = {"Folder"}, .numCategories = 1, .parent = -1, .size = 4096 },
    };

    std::vector<std::string> expectedLeafFiles{
        "Audio.mp3",
        "Backup.zip",
        "Code.py",
        "Document.txt",
        "Image.jpg",
        "Presentation.pptx",
        "Spreadsheet.xlsx",
        "Spreadsheet2.xlsx",
        "Video.mp4"
    };
    std::vector<std::string> returnedLeafFiles = leafFiles(testFiles);
    std::sort(returnedLeafFiles.begin(), returnedLeafFiles.end());
    assert(expectedLeafFiles == returnedLeafFiles);

    std::vector<std::string> expectedCategories{"Documents", "Folder", "Media"};
    std::vector<std::string> returnedCategories = kLargestCategories(testFiles, 3);
    assert(expectedCategories == returnedCategories);

    assert(largestFileSize(testFiles) == 20992);

}
