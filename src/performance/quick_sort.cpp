#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <stdint.h>
#include <stdio.h>
#include <vector>
#include <windows.h>

#include "vxlang/vxlib.h"

#ifndef _WIN64
#pragma comment(lib, "vxlib32.lib")
#else
#pragma comment(lib, "vxlib64.lib")
#endif

// Function to generate random vector of specified size
std::vector<int> generateRandomVector(size_t size) {
  std::vector<int> vec(size);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dis(1, 1000000);

  for (size_t i = 0; i < size; ++i) {
    vec[i] = dis(gen);
  }
  return vec;
}

// Function to calculate standard deviation
double calculateStdDev(const std::vector<double> &times, double mean) {
  double sum = 0.0;
  for (double time : times) {
    sum += std::pow(time - mean, 2);
  }
  return std::sqrt(sum / (times.size() - 1));
}

// Partition function modified for vectors
int partition(std::vector<int> &arr, int low, int high) {
  int pivot = arr[high];
  int i = low - 1;

  for (int j = low; j < high; j++) {
    if (arr[j] <= pivot) {
      i++;
      std::swap(arr[i], arr[j]);
    }
  }
  std::swap(arr[i + 1], arr[high]);
  return i + 1;
}

// QuickSort modified for vectors
void quickSort(std::vector<int> &arr, int low, int high) {
  VL_VIRTUALIZATION_BEGIN;
  if (low < high) {
    int pivot_index = partition(arr, low, high);
    quickSort(arr, low, pivot_index - 1);
    quickSort(arr, pivot_index + 1, high);
  }
  VL_VIRTUALIZATION_END;
}

// Function to measure sorting time for a given size
std::pair<double, double> measureSortingTime(size_t size, int runs = 10) {
  std::vector<double> times;

  for (int i = 0; i < runs; ++i) {
    std::vector<int> data = generateRandomVector(size);

    auto start = std::chrono::high_resolution_clock::now();
    quickSort(data, 0, data.size() - 1);
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = stop - start;
    times.push_back(duration.count());
  }

  // Calculate average
  double sum = 0;
  for (double time : times) {
    sum += time;
  }
  double average = sum / times.size();

  // Calculate standard deviation
  double stdDev = calculateStdDev(times, average);

  return {average, stdDev};
}

int main() {
  std::vector<size_t> sizes = {100,       1000,      5000,      10'000,
                               50'000,    100'000,   500'000,   1'000'000,
                               1'500'000, 2'000'000, 2'500'000, 3'000'000};

  std::cout << std::fixed; // Set fixed decimal precision
  std::cout.precision(2);

  std::cout << "\nSize\t\tAvg Time (ms)\tStd Dev (ms)\n";
  std::cout << "----------------------------------------\n";

  for (size_t size : sizes) {
    auto [avgTime, stdDev] = measureSortingTime(size, 100);
    std::cout << size << "\t\t" << avgTime << "\t\t" << stdDev << std::endl;
  }

  return 0;
}
