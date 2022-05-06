#include "assignment/insertion_sort.hpp"

#include <utility>  // move, swap

#include "assignment/partitioning.hpp"  // middle_of

namespace assignment {

  int linear_search(const std::vector<int>& arr, int index) {

    // итерация всех предыдущих элементов [0, index - 1] (они находятся в отсортированном порядке)
    for (int curr_pos = index - 1; curr_pos >= 0; curr_pos--) {
      if (arr[curr_pos] <= arr[index]) {
        return curr_pos + 1;
      }
      // если текущий элемент меньше или равен вставляемому, позиция для вставки найдена ...
    }
    return 0;
  }

  int binary_search(const std::vector<int>& arr, int index) {

    // начало, конец и середина области поиска места для вставки [0, index - 1]
    int start = 0;
    int stop = index - 1;
    int middle;
    int num = arr[index];

    while (start <= stop) {

      if (arr[start] == num) return start;
      if (arr[stop] == num) return stop;

      middle = middle_of(start, stop);

      if (arr[middle] == num) return middle;
      if (arr[middle] > num) stop = middle - 1;
      if (arr[middle] < num) start = middle + 1;

    }

    return stop + 1;
  }

  void InsertionSort::Sort(std::vector<int>& arr) const {

    // - проходимся по элементам, начиная со второго
    // - после каждой итерации, слева от index будет формироваться отсортированный массив
    // - первый элемент слева считается отсортированным
    for (int index = 1; index < static_cast<int>(arr.size()); index++) {

      // поиск индекса для вставки элемента с индексом index в область [0, index - 1]
      const int ins_index = searcher_(arr, index);
      if (ins_index != index) {
        int num = arr[index];
        for (int i = index; i > ins_index; i--) {
          if (i > ins_index) {
            arr[i] = arr[i - 1];
          }
        }
        arr[ins_index] = num;
      }

      // если индекс вставки не совпадает с текущей позицией элемента,
      // производим вставку элемента на вычисленную позицию (std::copy или цикл for) ...
    }
  }

  InsertionSort::InsertionSort(Searcher searcher) : searcher_{std::move(searcher)} {}

}  // namespace assignment