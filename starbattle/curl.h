#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <curl\curl.h>

struct MemoryStruct {
    char* memory;
    size_t size;
};

size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct* mem = (struct MemoryStruct*)userp;

    char* ptr = (char*)(std::realloc(mem->memory, mem->size + realsize + 1));
    if (ptr == NULL) {
        printf("error: not enough memory\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}