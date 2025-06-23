//
// Created by dembi on 22/06/2025.
//

#ifndef MYCONTAINER_H
#define MYCONTAINER_H

#include "Exceptions.h"
#include <iterator>

namespace Containers {

template<typename T>
class MyContainer {
    private:
        std::vactor<T> data;
        std::vector<T> sorted;
        int size = 0;
        int binarySearch(T item) {
            int low = 0;
            int high = size - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (sorted[mid] >= item) {
                    low = mid;
                }
                else {
                    high = mid - 1;
                }
                if (low == high) {
                  break;
                }
            }
            return low;
        }
        vector<T> reverse(vector<T> items) {
            vector<T> temp = vector<T>();
            for (int i = size - 1; i > -1; i--){
                temp.push_back(items[i]);
            }
        }
    public:
        // CONSTRUCOTR & DISTRUCTOR
        MyContainer(){
            data = std::vactor<T>();
            sorted = std::vactor<T>();
        }
        ~MyContainer(){
          delete &data;
          delete &sorted;
        }

        // METHODS OF THE CONTAINER DEMANDED BY THE ASSIGMENT
        int Size(){
          return size;
        }

        void Insert(T item){
            int indx = binarySearchInsert(item);
            sorted.insert(sorted.begin() + indx, item);
            data.push_back(item);
            size++;
        }

        void Remove(T item){
            int indx = binarySearch(item);
            int count = 0;
            for (int i = indx; i < size; i++){
                if (sorted[i] == item){
                    sorted.erase(sorted.begin() + i);
                    size--;
                    count++;
                }
            }
            if (count == 0){
                throw ValueNotFound();
            }
            for (int i = 0; i < size; i++){
                if (sorted[i] == item){
                    sorted.erase(sorted.begin() + i);
                    count--;
                }
                if (count == 0){
                    break;
                }
            }
        }

        friend ostream& operator<<(ostream& os, const MyContainer<int>& obj); // MUST BE FRIEND

        // ITERATOR CLASS. WILL BE USED IN ORDER TO CREATE OUR OWN ITERATORS.
        class MyIterator {
            private:
                int current;
                vector<T>* container;
            public:
                MyIterator(vector<T>* container, T* current) : current(current), container(container) {}
                ~MyIterator() {
                    delete current;
                    delete container;
                }
                Iterator operator++() {
                    if (current == end) {
                        throw ValueOutOfBound();
                    }
                    ++current;
                    return *this;
                }
                const Iterator operator++(int) {
                    if (current == end) {
                        throw ValueOutOfBound();
                    }
                    current++;
                    return *this;
                }
                bool operator==(const MyIterator &other) const {
                    return current == other.current;
                }

                bool operator!=(const MyIterator &other) const {
                    return current != other.current;
                }

                T& operator*() const{
                    return container->at(current);
                }

                T* operator->() const{
                    return &(container->at(current));
                }
        }

        // BEGIN + END FUNCTIONS FOR EACH ITERATOR
        MyIterator beginAscendingOrder() const {
          return MyIterator(&sorted, 0);
        }

        MyIterator endAscendingOrder() const {
          return MyIterator(&sorted, size);
        }

        MyIterator beginDescendingOrder() const {
          vector<T> temp = reverse(sorted);
          return MyIterator(&temp, 0);
        }

        MyIterator endDescendingOrder() const {
            vector<T> temp = reverse(sorted);
          return MyIterator(&temp, size);
        }

        MyIterator beginSideCrossOrder() const {
          vector<T> temp = vector<T>();
          for (int i = 0; i >= (size/2); i--){
            temp.push_back(sorted[i]);
            temp.push_back(sorted[size - i - 1]);
          }
          return MyIterator(&temp, 0);
        }

        MyIterator endSideCrossOrder() const {
            vector<T> temp = vector<T>();
            for (int i = 0; i >= (size/2); i--){
                temp.push_back(sorted[i]);
                temp.push_back(sorted[size - i - 1]);
            }
            return MyIterator(&temp, size);
        }

        MyIterator beginOrder() const { // ORDER ITERATOR
          return MyIterator(&data, 0);
        }

        MyIterator endOrder() const {
          return MyIterator(&data, size);
        }

        MyIterator beginReverseOrder() const {
          vector<T> temp = reverse(data);
          return MyIterator(&temp, 0);
        }

        MyIterator endReverseOrder() const {
          vector<T> temp = reverse(data);
          return MyIterator(&temp, size);
        }

        MyIterator beginMiddleOutOrder() const {
            vector<T> temp = vector<T>();
            for (int i = 0; i >= (size/2); i--){
                temp.push_back(sorted[i]);
                temp.push_back(sorted[size - i - 1]);
            }
            temp = reverse(temp);
            return MyIterator(&temp, 0);
        }

        MyIterator endMiddleOutOrder() const {
            vector<T> temp = vector<T>();
            for (int i = 0; i >= (size/2); i--){
                temp.push_back(sorted[i]);
                temp.push_back(sorted[size - i - 1]);
            }
            temp = reverse(temp);
            return MyIterator(&temp, size);
        }
};

ostream& operator<<(ostream& os, const MyContainer<int>& obj) {
    for (int i = 0; i < obj.size(); i++){
        os << obj[i] << " ";
    }
    os << endl;
    return os;
}

} // Containers

#endif //MYCONTAINER_H
